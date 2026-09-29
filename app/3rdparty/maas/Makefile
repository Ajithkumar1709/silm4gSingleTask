################### makefile ########################
############## common for make app ##################
#####################################################

include ${SOFT_WORKDIR}/build/buildenv.mk


LOCAL_NAME := maas

CUSTOEMR_DEFINE_DIR := customer_define

MAAS_DIR := maas
BOT_ADAPTER_PLATFORM_DIR := ${SOFT_WORKDIR}/maas/adapter/platform/l50x-threadx/l50x-open
ADAPTER_TOPDIR := maas/adapter

BOT_GLOBAL_INCLUDE :=   ${API_PLATFORM_DEPENDS} \
						$(MAAS_DIR)/include \
						$(ADAPTER_TOPDIR)/include \
						$(ADAPTER_TOPDIR)/include/network \
						$(ADAPTER_TOPDIR)/include/peripheral \
						$(ADAPTER_TOPDIR)/include/system \
                        $(ADAPTER_TOPDIR)/platform/l50x-threadx/l50x-open/include

LOCAL_API_DEPENDS :=   ${BOT_GLOBAL_INCLUDE}
			
LOCAL_MODULE_DEPENDS := 

BOT_PLATFORM_SRC 	:=	${wildcard $(BOT_ADAPTER_PLATFORM_DIR)/*.c}
BOT_PLATFORM_SRC 	+=	${wildcard $(BOT_ADAPTER_PLATFORM_DIR)/network/*.c}
BOT_PLATFORM_SRC 	+=	${wildcard $(BOT_ADAPTER_PLATFORM_DIR)/peripheral/*.c}
BOT_PLATFORM_SRC 	+=	${wildcard $(BOT_ADAPTER_PLATFORM_DIR)/system/*.c}

C_SRC 	+=	$(BOT_PLATFORM_SRC)
C_SRC 	+=	${SOFT_WORKDIR}/maas/app/bot_app_entry.c

#####################################################
include ${SOFT_WORKDIR}/build/makerules.mk

