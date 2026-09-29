/* ================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : ^HW_PLATFORM hw-platform LDF file.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

ARCHITECTURE(INTEL-MSA)
SEARCH_DIR( $INTEL_DSP\msa\lib )

#if !defined( NO_GS_DATA_INIT_CRT0  ) && defined( PATCH_FILE_NAME )
#define DROM_PATCH ..\OUTPUT_DIR\PATCH_FILE_NAME.doj
#define NO_LOAD_TYPE SHT_NOBITS
#else
#define NO_LOAD_TYPE
#endif

$LIBRARIES = libc.dlb, libevent.dlb, libsftflt.dlb, libcpp_msa.dlb, libcpprt_msa.dlb, libdsp.dlb, librt_fileio.dlb, halt.doj;

$OBJECTS = $COMMAND_LINE_OBJECTS;

// Memory map
MEMORY
{
#if defined( ^UP_HW_PLATFORM_PROTO )
  PROGRAM    { TYPE(RAM) START( MSA_ISROM_START_ADDRESS )      LENGTH( MSA_ISROM_SIZE )          WIDTH(8) }
  BOOT_FLASH { TYPE(RAM) START( FLASH_BOOT_LOADER_ADDR )       LENGTH( FLASH_BOOT_LOADER_SIZE )  WIDTH(8) }
#else
  PROGRAM    { TYPE(RAM) START( MSA_L1_FLASH_START_ADDRESS )   LENGTH( MSA_L1_FLASH_SIZE )       WIDTH(8) }
#endif

#if defined( ^UP_HW_PLATFORM_PROTO )
  // Constant Data
  DATA_ROM    { TYPE(RAM) START( MSA_DROM_START_ADDRESS )      LENGTH( MSA_DROM_SIZE )           WIDTH(8) }
#endif

  // Data Bank A 16K
#define MINIBANK1_START_ADDRESS ( MSA_L1_BANK_A_START_ADDRESS + MSA_L1_BANK_A_SIZE/2 )
#define MINIBANK1_SIZE          ( MSA_L1_BANK_A_SIZE/4 )
#define MINIBANK2_START_ADDRESS ( MINIBANK1_START_ADDRESS + MINIBANK1_SIZE )
#define MINIBANK2_SIZE          ( MSA_L1_BANK_A_SIZE/4 )

  DATA_A      { TYPE(RAM) START( MSA_L1_BANK_A_START_ADDRESS ) LENGTH( MSA_L1_BANK_A_SIZE/2)     WIDTH(8) }
  MINIBANK1   { TYPE(RAM) START( MINIBANK1_START_ADDRESS )     LENGTH( MINIBANK1_SIZE)           WIDTH(8) }
  MINIBANK2   { TYPE(RAM) START( MINIBANK2_START_ADDRESS )     LENGTH( MINIBANK2_SIZE)           WIDTH(8) }
  
  // Data Bank B 16K (Split between data and heap)
#if !defined(USE_FILEIO)
#if !defined(NEED_HEAP)
  DATA_B      { TYPE(RAM) START( MSA_L1_BANK_B_START_ADDRESS )  LENGTH( MSA_L1_BANK_B_SIZE )     WIDTH(8) }
#else
  DATA_B      { TYPE(RAM) START(0xFF100000) LENGTH(0x2A00)   WIDTH(8) }
  HEAP        { TYPE(RAM) START(0xFF102A00) LENGTH(0x1600)  WIDTH(8) }
#endif
#else
  DATA_B      { TYPE(RAM) START(0xFF100000) LENGTH(0x2800)  WIDTH(8) }
  HEAP        { TYPE(RAM) START(0xFF102800) LENGTH(0x1600)  WIDTH(8) }
  ARGV        { TYPE(RAM) START( ARGV_START_ADDRESS ) LENGTH( ARGV_LENGTH )  WIDTH(8) }
#endif
  
  // Scratch SRAM 4K
  SCRATCH     { TYPE(RAM) START( MSA_L1_SCRATCH_START_ADDRESS ) LENGTH( MSA_L1_SCRATCH_SIZE )    WIDTH(8) }
  //EMULATOR    { TYPE(RAM) START(0xFF300FF8) LENGTH(0x0008)  WIDTH(8) }    // Space reserved for use by emulator.


#if defined( ^UP_HW_PLATFORM_PROTO )
  // L2 mirror 8MB
  MIRROR      { TYPE(RAM) START( MSA_PMIRROR_START_ADDRESS )   LENGTH( MSA_PMIRROR_SIZE )        WIDTH(8) }

  // L2 SRAM 8MB
  L2_SRAM     { TYPE(RAM) START( MSA_L2_SRAM_START_ADDRESS )   LENGTH( MSA_L2_SRAM_SIZE )        WIDTH(8) }
  
  // Shared memory 16KB
  SHARED_MEM  { TYPE(RAM) START( MSA_DPR_START_ADDRESS )       LENGTH( MSA_DPR_SIZE )            WIDTH(8) }

  // Instruction SRAM
  ISRAM       { TYPE(RAM) START( MSA_L1_INSTR_START_ADDRESS )  LENGTH( MSA_L1_INSTR_SIZE )       WIDTH(8) }
#endif
}


PROCESSOR p0
{
  OUTPUT( $COMMAND_LINE_OUTPUT_FILE )
	
    SECTIONS
    {
	  /*****************************************************************************
	   *      Code
	   *****************************************************************************/
#if defined( ^UP_HW_PLATFORM_PROTO )
	  bootloader_code { INPUT_SECTIONS( $OBJECTS(CFW_BOOTLOAD_CODE) ) } >BOOT_FLASH
#endif
	  // Start-up code has to be the first
	  startup_code
          { INPUT_SECTIONS( $OBJECTS(CFW_CRT_STARTUP_CODE) $OBJECTS(CFW_CRT_INIT_CODE) ) } >PROGRAM

	  // Other code
      code
      { INPUT_SECTIONS( $OBJECTS(program) ) } >PROGRAM
      lib_code
      { INPUT_SECTIONS( $LIBRARIES(program) ) } >PROGRAM
      /*****************************************************************************
	   *      Data
	   *****************************************************************************/

      // Other global and static data
      gs_data NO_LOAD_TYPE
       { INPUT_SECTIONS( $OBJECTS(data1) ) }   > DATA_A
      gs_lib_data NO_LOAD_TYPE
       { INPUT_SECTIONS( $LIBRARIES(data1) ) } > DATA_A

      stack_default SHT_NOBITS
       {
            ldf_stack_space = .;
            . = . + USER_STACK_BYTE_SIZE;
            ldf_stack_end = .;
            // for using this labels in C code
            _ldf_stack_end = .;
       } >DATA_B

       sysstack SHT_NOBITS
        {
            ldf_sysstack_space = .;
            . = . + SYS_STACK_BYTE_SIZE;
            ldf_sysstack_end   = .;
        } >DATA_B

      // Other constant data
      constdata
      { INPUT_SECTIONS( $OBJECTS(constdata) ) }   > DATA_ROM
      lib_constdata
      { INPUT_SECTIONS( $LIBRARIES(constdata) ) } > DATA_ROM

	TARGET_SECTIONS

#if defined(USE_FILEIO) || defined(NEED_HEAP)
	  // Heap section for Libraries
      heap
      {
		// Allocate a heap for the application
		ldf_heap_space = .;
		ldf_heap_end = ldf_heap_space + MEMORY_SIZEOF(HEAP) - 1;
		ldf_heap_length = ldf_heap_end - ldf_heap_space;
        // for using those labels in C code
        _ldf_heap_space = ldf_heap_space;
        _ldf_heap_end = ldf_heap_end;
	  } >HEAP
#endif

#if defined(USE_FILEIO)
      argv
      {
       // Allocate argv space for the application
       ldf_argv_space = .;
       ldf_argv_end = ldf_argv_space + MEMORY_SIZEOF(ARGV) - 1;
       ldf_argv_length = ldf_argv_end - ldf_argv_space;
      } >ARGV
#endif
#ifdef DROM_PATCH
	  // DROM patch code
	  drom_patch_code
	  { INPUT_SECTIONS( DROM_PATCH(CFW_GSDATACOPY_CODE) ) } > PROGRAM
#else
	  // dummy address definition for first-pass linkage
	  drom_patch_code
	  {
		_CopyGSDataPatch = .;
	  } > PROGRAM

#endif
#ifdef DROM_PATCH
      // Copy of global and static data in DROM
      gs_data_patch
      { INPUT_SECTIONS( DROM_PATCH(GSDATA_PATCH_INFO) DROM_PATCH(GSDATA_PATCH) ) } > DATA_ROM

	  // DROM patch data - dummy section.
	  // Actually, this section is empty, but compiler generates a "data1" section symbol,
	  // so it has to be included here.
      drom_patch_data
	  { INPUT_SECTIONS( DROM_PATCH(data1) ) } > DATA_ROM
#endif
	} // SECTIONS
} // Processor p0


