#ifndef _MBTK_AT_CMDS_HANDLE_H_
#define _MBTK_AT_CMDS_HANDLE_H_
#include <utlAtParser.h>
#include "utltypes.h"


//at test
utlReturnCode_T AtMbtkCustTest(const utlAtParameterOp_T op,const char *command_name_p,const utlAtParameterValue_P2c  parameter_values_p,const size_t num_parameters,const char *info_text_p,unsigned int *xid_p,void *arg_p);

#ifdef MBTK_POC_SUPPORT
utlReturnCode_T ciSetPoc(const utlAtParameterOp_T op,const char *command_name_p,const utlAtParameterValue_P2c  parameter_values_p,const size_t num_parameters,const char *info_text_p,unsigned int *xid_p,void *arg_p);
utlReturnCode_T AtMbtkPocSet(const utlAtParameterOp_T op,const char *command_name_p,const utlAtParameterValue_P2c  parameter_values_p,const size_t num_parameters,const char *info_text_p,unsigned int *xid_p,void *arg_p);
utlReturnCode_T  ciSetPoccfg(            const utlAtParameterOp_T op,
                  const char                      *command_name_p,
                  const utlAtParameterValue_P2c parameter_values_p,
                  const size_t num_parameters,
                  const char                      *info_text_p,
                  unsigned int                    *xid_p,
                  void                            *arg_p);

#endif

utlReturnCode_T AtMbtkCustFactory(const utlAtParameterOp_T op, const char* command_name_p, const utlAtParameterValue_P2c  parameter_values_p, const size_t num_parameters, const char* info_text_p, unsigned int* xid_p, void* arg_p);

#ifdef MBTK_PYTHON_SUPPORT
utlReturnCode_T AtMbtkPy(const utlAtParameterOp_T       op,
                                const char*                    command_name_p,
                                const utlAtParameterValue_P2c  parameter_values_p,
                                const size_t                   num_parameters,
                                const char*                    info_text_p,
                                unsigned int*                  xid_p,
                                void*                          arg_p);
#endif

utlReturnCode_T AtMbtkCatFS(const utlAtParameterOp_T       op,
                                const char*                    command_name_p,
                                const utlAtParameterValue_P2c  parameter_values_p,
                                const size_t                   num_parameters,
                                const char*                    info_text_p,
                                unsigned int*                  xid_p,
                                void*                          arg_p);

#endif
