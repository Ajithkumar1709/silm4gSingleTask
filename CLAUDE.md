# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Working with the user

- Before answering, correct the user's question/sentence if it has grammar or wording issues, and
  show the corrected version first.
- Explain things simply first, then give the detailed/technical answer.

## What this repo is

This is the LYNQ SDK (CAT1, ASR platform, v12.01b02.00) — a vendor firmware SDK for an ASR-based
cellular (CAT1) modem module. It contains the RTOS kernel, bootloader, cross-compilation toolchain,
and an application layer where customer/product code is added. Almost all custom application logic
for this project lives under `app/demo/my_demo/` — everything else (`kernel/`, `bootloader/`,
`cross_tool/`, `app/system/`, `app/3rdparty/`) is vendor-supplied platform code.

## Build

Builds are Windows-only, driven by batch scripts and CMake, and require the ARM GCC toolchain in
`cross_tool/win32` (set up once via `install.bat` from the repo root).

From `app/`:
- `app.bat` — full build. Calls `compile_tools_init.bat`, then `setenv.bat` (configures
  `arm-none-eabi-gcc` toolchain env vars and runs `cmake -G "MinGW Makefiles" -B ./build`), then
  builds with `gnumake` inside `build/`. Output binaries land in `app/release/`
  (`user_app.bin`, `.elf`, `.map`).
- `app.bat clean` — removes `build/` and `release/`.
- `menuconfig.bat` — opens the Kconfig-based menuconfig UI (`config/Kconfig`) to edit feature flags.
  Writes `config/menuconfig/target/target.config(.h/.mk)`, which CMake imports via
  `import_kconfig(...)` in `app/CMakeLists.txt` as `GLOBLE_FEATURE_DEF` compile definitions
  (e.g. `MBTK_SIMCOM_SUPPORT`, `MBTK_AZURE_SUPPORT`, `MBTK_MAAS_SUPPORT`, `MBTK_QCLOUD_SUPPORT`,
  `MBTK_CJSON_SUPPORT`, `MBTK_IS_COMPRESS`, `MBTK_IS_XIP`). Run this before `app.bat` any time the
  build config needs to change — the generated `target.config*` files are build artifacts, not
  hand-edited source.

There is no unit test runner in this repo — this is embedded/on-device firmware; verification is
building successfully and flashing/running on hardware.

## Architecture

### Layout
- `kernel/` — RTOS kernel and platform HAL/driver code (vendor).
- `bootloader/` — second-stage bootloader (vendor).
- `cross_tool/` — bundled Windows toolchain (ARM GCC, CMake, MinGW, DS-5, Perl) used by the build
  scripts; not application code.
- `app/system/` — platform glue library linked into every app build.
- `app/3rdparty/` — optional vendor-integrated third-party stacks (simcom, azure, qcloud, maas,
  cjson), toggled on via the Kconfig flags above.
- `app/demo/my_demo/` — the customer application. This is what you'll be editing for feature/bug
  work in this project.
- `app/lib/` — prebuilt stub objects (`sdk_api_stub.o`, `sdk_api_stub_c.o`) linked into the final
  image; not buildable source.
- `app/build/`, `app/release/` — CMake build tree and build output; generated, do not hand-edit.

### `app/demo/my_demo` structure
- `src/my_demo.c` — entry task (`my_demo()`), the main application loop. Initializes GPIO/LED,
  the lamp monitor, the inter-task message queue (`mainProcessQueue`), and restores persisted
  config (`memoryHandle_readConfigStoreWithBackup()`) before entering its run loop.
- `src/mqttTask.c` / `src/periodicTask.c` — the other two long-running tasks: MQTT connection
  handling and periodic (timer-driven) work. Tasks communicate via `mbtk_msgqref` message queues
  (e.g. `mainProcessQueue`, `mqttQueue_t`, `ilmQueue_t`), not shared globals, so cross-task changes
  usually mean touching a queue struct in a shared header plus both the producer and consumer task.
- `src/modules/` — feature modules used by the tasks above:
  - `lampStatusFinder.*` — lamp/output status detection.
  - `pvcMeasure.*` — PVC (power/voltage/current) sampling.
  - `publish.*` — builds and sends telemetry/JSON packets uplink.
  - `rpcHandler.*` — handles inbound RPC/downlink commands.
  - `otaHandler.*` — OTA/FOTA update handling (see `MBTK_FOTA_SUCCEED` and related status codes).
  - `memoryHandle.*` — persisted configuration read/write with backup.
- Sources are registered explicitly in `app/demo/my_demo/CMakeLists.txt` via `app_source(...)` —
  adding a new `.c` file requires adding it there or it will not be compiled.

### Config vs. code
Feature flags (`MBTK_*`) are set via `menuconfig.bat`, not by editing headers directly — they flow
from Kconfig into generated `target.config.h`/`.mk` files that are consumed at CMake configure time.
When asked to toggle a vendor SDK feature (rather than application behavior), check `config/Kconfig`
and menuconfig first before assuming it's a source-level change.
