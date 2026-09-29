;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;-----------------------------------------------------------
;               Macro-definitions: do NOT alter
;-----------------------------------------------------------

      IF   :DEF: DLM_JMP_TABLE

; Dlm's Jump table entry macro-definition

 AREA JmpTable, CODE, READONLY

  IF :DEF: NO_BOOT_LOADER
JMP_TABLE    EQU    0xD0800200
  ELSE
JMP_TABLE    EQU    0xD0800200
  ENDIF

         GBLA   offset
offset   SETA   0

 MACRO
    FUNC_ENTRY   $service
    EXPORT       $service
$service  EQU (JMP_TABLE+offset),CODE32
offset   SETA   offset+4
          MEND

 MACRO
    UNIMPLEMENTED $service
offset   SETA   offset+4
          MEND

      ELSE

; Target's Jump table entry macro-definition
		MACRO
    FUNC_ENTRY   $service
		IMPORT       $service
	        B            $service
	        MEND

    MACRO
    UNIMPLEMENTED $service
    IMPORT        dlmUnImplemented
          B            dlmUnImplemented
          MEND


     EXPORT  jmpTable
jmpTable        ; JUMP TABLE

      ENDIF

;-----------------------------------------------------------
;               Jumptable
;-----------------------------------------------------------

  IF :LNOT::DEF: NO_APLP
  GBLL NO_APLP
NO_APLP SETL {FALSE}
  ENDIF

   FUNC_ENTRY     dlmPrintf
   FUNC_ENTRY     dlmControllerSend
   FUNC_ENTRY     IPCCommCommandSend
   FUNC_ENTRY     IPCCommNewOpcodeCommandSend
  ; FUNC_ENTRY     dlmStructPrintf
  ; FUNC_ENTRY     dlmStructExtPrintf
   FUNC_ENTRY     IPCCommDataSend
   FUNC_ENTRY     IPCCommNewOpcodeDataSend
   FUNC_ENTRY     IPCCommFreeDataChannel
   FUNC_ENTRY     IPCCommLegacyCommandSend
  ; UNIMPLEMENTED  IPCCommMessageFlush
  ; UNIMPLEMENTED  IPCCommDataRead
  ; UNIMPLEMENTED  IPCCommFreeDataBuffers
   FUNC_ENTRY     IPCCommRegister
   FUNC_ENTRY     IPCCommUnRegister
   FUNC_ENTRY     OSATaskCreate
   FUNC_ENTRY     OSATaskDelete
   FUNC_ENTRY     OSATaskChangePriority
   FUNC_ENTRY     OSATaskGetPriority
   FUNC_ENTRY     OSATaskSuspend
   FUNC_ENTRY     OSATaskResume
   FUNC_ENTRY     OSATaskSleep
   FUNC_ENTRY     OSATaskGetCurrentRef
   FUNC_ENTRY     OSAFlagCreate
   FUNC_ENTRY     OSAFlagDelete
   FUNC_ENTRY     OSAFlagSet
   FUNC_ENTRY     OSAFlagWait
   FUNC_ENTRY     OSAFlagPeek
   FUNC_ENTRY     OSATimerCreate
   FUNC_ENTRY     OSATimerDelete
   FUNC_ENTRY     OSATimerStart
   FUNC_ENTRY     OSATimerStop
   FUNC_ENTRY     OSATimerGetStatus
   FUNC_ENTRY     OSAMsgQCreate
   FUNC_ENTRY     OSAMsgQDelete
   FUNC_ENTRY     OSAMsgQCreateWithMem
   FUNC_ENTRY     OSAMsgQSend
   FUNC_ENTRY     OSAMsgQRecv
   FUNC_ENTRY     OSAMsgQPoll
   FUNC_ENTRY     OSAMailboxQCreate
   FUNC_ENTRY     OSAMailboxQDelete
   FUNC_ENTRY     OSAMailboxQSend
   FUNC_ENTRY     OSAMailboxQRecv
   FUNC_ENTRY     OSAMailboxQPoll
   FUNC_ENTRY     OSASemaphoreCreate
   FUNC_ENTRY     OSASemaphoreDelete
   FUNC_ENTRY     OSASemaphoreAcquire
   FUNC_ENTRY     OSASemaphoreRelease
   FUNC_ENTRY     OSASemaphorePoll
   FUNC_ENTRY     OSAMutexCreate
   FUNC_ENTRY     OSAMutexDelete
   FUNC_ENTRY     OSAMutexLock
   FUNC_ENTRY     OSAMutexUnlock
   FUNC_ENTRY     OSAIsrCreate
   FUNC_ENTRY     OSAIsrDelete
   FUNC_ENTRY     OSAIsrEnable
   FUNC_ENTRY     OSAIsrDisable
   FUNC_ENTRY     OSAIsrNotify
   FUNC_ENTRY     OSAGetTicks
   FUNC_ENTRY     OSAGetClockRate
   FUNC_ENTRY     OSATick
   FUNC_ENTRY     OSAGetSystemTime
   FUNC_ENTRY     OSAMemPoolCreate
   FUNC_ENTRY     OSAMemPoolDelete
   FUNC_ENTRY     OSAMemPoolAlloc
   FUNC_ENTRY     OSAMemPoolFree
   FUNC_ENTRY     OSAMemPoolFixedFree
   FUNC_ENTRY     IPCCommApplicationIDGet
   FUNC_ENTRY     IPCCommApplicationIDReturn
   FUNC_ENTRY     getTime_us
	 FUNC_ENTRY     Arm946eDisableInterrupts		;FUNC_ENTRY     disableInterrupts
	 FUNC_ENTRY     Arm946eEnableInterrupts			;FUNC_ENTRY     enableInterrupts
	 FUNC_ENTRY     Arm946eRestoreInterrupts		;FUNC_ENTRY     restoreInterrupts
   FUNC_ENTRY     sprintf
   FUNC_ENTRY     sscanf
   FUNC_ENTRY     strcpy
   FUNC_ENTRY     strlen
   FUNC_ENTRY     strcat
   FUNC_ENTRY     strcmp
   FUNC_ENTRY     Arm946eMemcpy   						; FUNC_ENTRY     memcpy
   FUNC_ENTRY     malloc
   FUNC_ENTRY     calloc
   FUNC_ENTRY     free

 ; ARM specific run-time library functions: not available with NDT compiler
 IF   :DEF: |ads$version| :LAND: :LNOT::DEF:NON_ARM_TARGET
   FUNC_ENTRY     _sprintf
   FUNC_ENTRY     _sscanf
   FUNC_ENTRY     __rt_memcpy
   FUNC_ENTRY     __rt_memclr
   FUNC_ENTRY     __rt_memset
   FUNC_ENTRY     __rt_udiv
   FUNC_ENTRY     __rt_sdiv
   FUNC_ENTRY     __rt_memclr_w
   FUNC_ENTRY     __rt_memcpy_w
   FUNC_ENTRY     _memset
   FUNC_ENTRY     _memset_w
 ENDIF

; WCDMA specific: AAAP (IPC) extra features
   FUNC_ENTRY     IPCCommSpyCmd
   FUNC_ENTRY     IPCCommUnSpyCmd
   FUNC_ENTRY     setNoPlpMode

; WCDMA specific: L1 API
 IF   :LNOT:NO_APLP

 ;  FUNC_ENTRY     plwBindCphyFreqScanInd
 ;  FUNC_ENTRY     plwBindCphyIntraFreqCellMeasurementInd
 ;  FUNC_ENTRY     plwCphyIntraFreqCellMeasReq
 ;  FUNC_ENTRY     plwCphyFreqScanReq
 ;  FUNC_ENTRY     plwCphyPccpchSetupReq
 ;  FUNC_ENTRY     plwCphySccpchSetupReq
 ;  FUNC_ENTRY     plwCphySccpchCbsSetupReq
 ;  FUNC_ENTRY     plwCphyPichAndSccpchSetupReq
 ;  FUNC_ENTRY     plwCphyPrachAichSetupReq
 ;  FUNC_ENTRY     plwCphyDpchSetupReq
 ;  UNIMPLEMENTED  plwCphyPdschSetupReq
 ;  FUNC_ENTRY     plwCphyRlReleaseReq
 ;  FUNC_ENTRY     plwCphyPccpchSkipFramesReq
 ;  FUNC_ENTRY     plwCphyModifyDpchReq
 ;  FUNC_ENTRY     plwSttdModifyReq
 ;  FUNC_ENTRY     plwCphySetFachOccasionParamsReq
 ;  FUNC_ENTRY     plwCbsLevel2SchedulingReq
 ;  FUNC_ENTRY     plwCphySetCompressedModeParams
 ;  FUNC_ENTRY     plwDpchDlEstablished
 ;  FUNC_ENTRY     plwBindCphyRlSetupCnf
 ;  FUNC_ENTRY     plwBindCphyRlReleaseCnf
 ;  FUNC_ENTRY     plwBindCphyModifyDpchCnf
 ;  FUNC_ENTRY     plwBindSttdModifyCnf
 ;  FUNC_ENTRY     plwCphyDetectedCellMeasReq
 ;  FUNC_ENTRY     plTM_SetReleaseSingleRL
 ;  FUNC_ENTRY     plTM_SetReleaseMultiRL
 ;  FUNC_ENTRY     plTM_ReleaseRL
 ;  FUNC_ENTRY     plTM_FreezeMaitenance
 ;  FUNC_ENTRY     BindMSR_SerachReplyFunc
 ;  FUNC_ENTRY     plMSRRakeListModify
 ;  FUNC_ENTRY     plRakeSearchResultsUpdate
 ;  FUNC_ENTRY     simulateFrameSync
 ;  FUNC_ENTRY     frameIntHISRHandler
 ;  FUNC_ENTRY     plwBindCphyUeRxTxTimeDiffMeasurementInd
 ;  FUNC_ENTRY     plwBindCphyInterFreqCellMeasurementInd

        IF   :DEF: L1_DUAL_MODE
;        IF :LNOT::DEF: GERAN_ONLY
; Dual mode functions
;   FUNC_ENTRY     plwBindGsmRssiMeasInd
;        ENDIF
; GSM Functions
   FUNC_ENTRY     plgMphFindBcchReq
   FUNC_ENTRY     plgMphNextBcchReq
   FUNC_ENTRY     plgMphBchConfigReq
   FUNC_ENTRY     plgMphPageModeReq
   FUNC_ENTRY     plgMphServingCellBcchReq
   FUNC_ENTRY     plgMphCbchControlReq
   FUNC_ENTRY     plgMphBcchDecodeReq
   FUNC_ENTRY     plgMphAbortNcellOpReq
   FUNC_ENTRY     plgMphRandomAccessReq
   FUNC_ENTRY     plgMphStopRachReq
   FUNC_ENTRY     plgMphMeasureAllReq
   FUNC_ENTRY     plgMphBsicDecodeReq
   FUNC_ENTRY     plgMphNcellMeasReq
   FUNC_ENTRY     plgMphImmAssignmentReq
   FUNC_ENTRY     plgMphChanAssignmentReq
   FUNC_ENTRY     plgMphChanAssignmentFailReq
   FUNC_ENTRY     plgMphCipherModeReq
   FUNC_ENTRY     plgMphFrequencyChangeReq
   FUNC_ENTRY     plgMphChannelModeReq
   FUNC_ENTRY     plgMphHandoverReq
   FUNC_ENTRY     plgMphHandoverFailReq
   FUNC_ENTRY     plgMphTimingAdvReq
   FUNC_ENTRY     plgMphRadioLinkTimeoutReq
   FUNC_ENTRY     plgMphExtMeasurementReq
   FUNC_ENTRY     plgMphDeactivateReq
   FUNC_ENTRY     plgMphClassmarkReq
   FUNC_ENTRY     plgMphMonitorPlmnReq
   FUNC_ENTRY     plgPhDataReq
   FUNC_ENTRY     plgPhEmptyFrameInd
   FUNC_ENTRY     plgRtl1UplinkDataReq
;GSM Binding Functions
   FUNC_ENTRY     plgBindMphBcchMeasInd
   FUNC_ENTRY     plgBindMphBsicDecodeInd
   FUNC_ENTRY     plgBindMphUnitDataInd
   FUNC_ENTRY     plgBindMphDownlinkSignalFailInd
   FUNC_ENTRY     plgBindMphIdleNcellMeasInd
   FUNC_ENTRY     plgBindMphIdleScellMeasInd
   FUNC_ENTRY     plgBindMphHandoverStartInd
   FUNC_ENTRY     plgBindMphRadioLinkTimeoutInd
   FUNC_ENTRY     plgBindMphDedicatedMeasInd
   FUNC_ENTRY     plgBindMphErrorInd
   FUNC_ENTRY     plgBindMphMonitorPlmnInd
   FUNC_ENTRY     plgBindMphBchConfigCnf
   FUNC_ENTRY     plgBindMphRandomAccessCnf
   FUNC_ENTRY     plgBindMphBsicDecodeCnf
   FUNC_ENTRY     plgBindMphImmAssignmentCnf
   FUNC_ENTRY     plgBindMphChanAssignmentCnf
   FUNC_ENTRY     plgBindMphChanAssignmentFailCnf
   FUNC_ENTRY     plgBindMphCipherModeCnf
   FUNC_ENTRY     plgBindMphFrequencyChangeCnf
   FUNC_ENTRY     plgBindMphChannelModeCnf
   FUNC_ENTRY     plgBindMphHandoverCnf
   FUNC_ENTRY     plgBindMphHandoverFailCnf
   FUNC_ENTRY     plgBindMphExtMeasurementCnf
   FUNC_ENTRY     plgBindMphDeactivateCnf
   FUNC_ENTRY     plgBindMphMonitorPlmnCnf
   FUNC_ENTRY     plgBindPhConnectInd
   FUNC_ENTRY     plgBindPhReadyToSendInd
   FUNC_ENTRY     plgBindPhDataInd
   FUNC_ENTRY     plgBindRtl1DownlinkDataInd
;GPRS Functions
   FUNC_ENTRY     plgGmphPbcchDecodeReq
   FUNC_ENTRY     plgGmphPccchConfigReq
   FUNC_ENTRY     plgGmphPrachReq
   FUNC_ENTRY     plgGmphStopPrachReq
   FUNC_ENTRY     plgGmphUlSbConfigReq
   FUNC_ENTRY     plgGmphUlSbAbortReq
   FUNC_ENTRY     plgGmphDlSbConfigReq
   FUNC_ENTRY     plgGmphDlTbfConfigReq
   FUNC_ENTRY     plgGmphUlDynTbfConfigReq
   FUNC_ENTRY     plgGmphUlFxdTbfConfigReq
   FUNC_ENTRY     plgGmphUlTbfShutdownReq
   FUNC_ENTRY     plgGmphDlTbfShutdownReq
   FUNC_ENTRY     plgGmphDynTsReconfigReq
   FUNC_ENTRY     plgGmphFxdTsReconfigReq
   FUNC_ENTRY     plgGmphTimingPowerReq
   FUNC_ENTRY     plgGmphPwrCtrlConfigReq
   FUNC_ENTRY     plgGmphPdchReleaseReq
   FUNC_ENTRY     plgGmphNetCtrlMeasReq
   FUNC_ENTRY     plgGmphExtMeasReq
   FUNC_ENTRY     plgGmphIntMeasReq
   FUNC_ENTRY     plgGmphPrachFormatReq
   FUNC_ENTRY     plgGl1CipherDataReq
;GPRS Binding Functions
   FUNC_ENTRY     plgBindGmphUnitDataInd
   FUNC_ENTRY     plgBindGmphUlFxdAllocEndInd
   FUNC_ENTRY     plgBindGmphPtmEnterInd
   FUNC_ENTRY     plgBindGmphPtmExitInd
   FUNC_ENTRY     plgBindGmphIntMeasInd
   FUNC_ENTRY     plgBindGmphPtmMeasInd
   FUNC_ENTRY     plgBindGmphPccchConfigCnf
   FUNC_ENTRY     plgBindGmphPrachCnf
   FUNC_ENTRY     plgBindGmphUlSbConfigCnf
   FUNC_ENTRY     plgBindGmphDlSbConfigCnf
   FUNC_ENTRY     plgBindGmphDlTbfConfigCnf
   FUNC_ENTRY     plgBindGmphUlDynTbfConfigCnf
   FUNC_ENTRY     plgBindGmphDynTsReconfigCnf
   FUNC_ENTRY     plgBindGmphFxdTsReconfigCnf
   FUNC_ENTRY     plgBindGmphUlFxdTbfConfigCnf
   FUNC_ENTRY     plgBindGmphPdchReleaseCnf
   FUNC_ENTRY     plgBindGmphExtMeasCnf
   FUNC_ENTRY     plgBindGl1CipherDataCnf
   FUNC_ENTRY     plgBindMacTxPayloadReq
   FUNC_ENTRY     plgBindMacL1Sequencer
   FUNC_ENTRY     plgBindMacRxRadioBlockInd
   FUNC_ENTRY     plgBindMacControlAckReq
   FUNC_ENTRY     plgBindMacDlConfigReq
   FUNC_ENTRY     plgBindMacUlConfigReq
   FUNC_ENTRY     plgBindMacDlStartInd
   FUNC_ENTRY     plgBindMacUlStartInd
   FUNC_ENTRY     plgBindMacDlFlushReq
   FUNC_ENTRY     plgBindMacUlFlushReq
   FUNC_ENTRY     plgBindMacUlSblockReq
   FUNC_ENTRY     plgBindMacRxDecodeErrorInd
   FUNC_ENTRY     plgBindMacRemoveUlSblockReq
   FUNC_ENTRY     plgBindMacTxBlockInfoReq
   FUNC_ENTRY     plgBindMacTxDataBlocksPurgedInd
   FUNC_ENTRY     plgBindMacTxBlockSentInd
   FUNC_ENTRY     plgBindMacUlTimeslotAllocInd
   FUNC_ENTRY     plgBindMacDlTimeslotAllocInd
  ; FUNC_ENTRY     plgDlmDiagPrintf
    ENDIF         ; L1_DUAL_MODE
    ENDIF         ; NO_APLP

  ; FUNC_ENTRY     romAlloc
  ; FUNC_ENTRY     romFree
  ; FUNC_ENTRY     cacheSync

   FUNC_ENTRY     ipcDispatchMsg
	; FUNC_ENTRY			GPIOConfigure
	; FUNC_ENTRY	  	GPIOPortControl
	; FUNC_ENTRY			GPIOPortOpen
	; FUNC_ENTRY			GPIOPortWithInterruptOpen
	; FUNC_ENTRY			GPIOPortClose
	; FUNC_ENTRY			GPIOStatusGet
	; FUNC_ENTRY     GPIOPortWrite
	; FUNC_ENTRY     GPIOPortRead
	 FUNC_ENTRY     INTCBind
	 FUNC_ENTRY     INTCUnbind
	; FUNC_ENTRY     INTCISRGet
	 FUNC_ENTRY     INTCDisable
	 FUNC_ENTRY     INTCEnable
	; FUNC_ENTRY     INTCSourceToGPIOPinConvert
	; FUNC_ENTRY     INTCSourceFromGPIOPinConvert
	; FUNC_ENTRY     INTCClear
   FUNC_ENTRY     INTCConfigure
  ; FUNC_ENTRY     cp14ReadCCNT
	 FUNC_ENTRY     timerCountRead

 IF   :LNOT:NO_APLP

 ;	 FUNC_ENTRY     plCalibCreateDefTxHwParams
 ;	 FUNC_ENTRY     plCalibCreateDefSwParams
 ;	 FUNC_ENTRY     plCalibCreateDefAfeParams
 ;	 FUNC_ENTRY     plCalibCreateDefRxAgcParams
 ;	 FUNC_ENTRY     plCalibCreateDefTxApcVgc
 ;	 FUNC_ENTRY     plCalibCreateDefTxApcVpa
 ;	 FUNC_ENTRY     plCalibCreateDefTxApcPower
 ;	 FUNC_ENTRY     plCalibCreateDefSpiRfConfig
 ;	 FUNC_ENTRY     plCalibCreateDefRfRegConfig
 ;	 FUNC_ENTRY     plCalibCreateDefRfDriversConfig
 ;	 FUNC_ENTRY     plCalibCreateDefRfEvents
 ;	 FUNC_ENTRY     plCalibCreateDefRfSequences
 ;	 FUNC_ENTRY     plCalibCreateFile

		ENDIF         ; NO_APLP


   ; add new functions here ONLY!!!


;--------------------------------------------------------------
;   spare space after jmptable (effective in target only)
;--------------------------------------------------------------

      IF   :DEF: DLM_JMP_TABLE

      ELSE

  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented
  ; FUNC_ENTRY     dlmUnImplemented


    EXPORT    jmpTableEnd
jmpTableEnd

      ENDIF

   END

