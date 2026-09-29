@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off
echo ----------------- Launch make command
echo ----------------- %*
call %*
exit errorlevel
echo ----------------- DONE 