/* ============================================================================
File        : gbl_trace.h
Description : Debug/Trace/Assert Macros and associated Function Prototypes.
              Build-wide customization file. This file is only used for
              testing the compilation and archiving of the 
              ^PACKAGE_BASE/^PACKAGE package.

Notes       : #define MACRO - names identical for ALL macro->function 
              mapping - custom to yer build. Do not customize MACRO 
              names *or* parameters. IsotelEngineId macros exist only
              for supporting tracing in the ITE test environment.
              
              Changes Required:
              1) Add module ID's to the module ID list, for each package. 
              2) Add trace categories to the TraceCategory enum
                 for each package.

Copyright ^YEAR, Intel Corporation, All rights reserved.
============================================================================ */

#if !defined(_GBL_TRACE_H_)
#define _GBL_TRACE_H_

/* Add Module ID definitions here ------------------------------------------ */

/* ^PACKAGE package Module ID definitions */
/* Change the file names */
#define ^UP_PACKAGE_FILE1ID          (change_this_to_a_number)
#define ^UP_PACKAGE_FILE2ID          (change_this_to_a_number)

/* Used by the token parser. This value must be last */
#define MAX_MODULEID              (change_this_to_a_number)  


/* Add Trace categories here ----------------------------------------------- */
typedef enum
{
  /* add ^PACKAGE Trace categories */


  MAX_NUM_TRACE_CATEGORIES
} TraceCategory;


/* No changes required below this line! ------------------------------------ */

/* these provide values to what ITRACE_TYPE is told to be */
#define TOKEN_TRACING 0
#define STRING_TRACING 1

#ifndef ITRACE_TYPE
#define ITRACE_TYPE TOKEN_TRACING
#endif

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */


#define NULL_STATEMENT

#ifdef DEBUG
void AssertFail( char *file, unsigned line );
#define ASSERT(f)   if ( !(f) ) AssertFail( __FILE__ , __LINE__ )

#else
#define ASSERT(f)     NULL_STATEMENT
#endif  /* DEBUG */

#ifndef TRACEON
     /* Tracing is turned off so define the trace macros as empty */
#define TRACE_INSTALL(s, i)
#define IASSERT(expr) ASSERT(expr)
#define TRACE(cat,level,token,s)
#define TRACEVAR(cat,level,token,s)

#define FTRACE2P(cat,level,token,fmt,var1,var2)
#define FTRACE1P(cat,level,token,fmt,var)
#define FTRACES(cat,level,token,fmt,var)

#define TRACEDATA(cat,level,token,dat,len)

#define ERROR(token,s)
#define FATAL(token,s)    _system_exit()

#define FERROR(token,fmt,var1)


#else   /* TRACEON */

/* Define switch for legacy code */
#define TraceIt

/* Trace levels; LEVEL0 = little detail; LEVEL5 = lots of detail */
typedef enum
{
  LEVEL0 = 0,
  LEVEL1,
  LEVEL2,
  LEVEL3,
  LEVEL4,
  LEVEL5
  
} TraceLevel;


#if (ITRACE_TYPE == TOKEN_TRACING)

#define TRACE_INSTALL(s, i) static CONST UINT8 ROM MyNameID = i;

#define IASSERT(expr) if (!(expr))   engAssert(ENGINE_ID, MyNameID, __LINE__)
  
#define TRACE(cat, level, token, s) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyNameID, token, \
              0, NULL, 0, NULL)
  
#define TRACEDATA(cat, level, token, dat, len) \
engTraceDataEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyNameID, token, \
                  len, (UINT8 *)dat)

#define FTRACE1P(cat, level, token, fmt, var1) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyNameID, token, \
              sizeof(var1), (UINT8 *)&var1, 0, NULL)
  
#define FTRACE2P(cat, level, token, fmt, var1, var2) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyNameID, token, \
              sizeof(var1), (UINT8 *)&var1, sizeof(var2), (UINT8 *)&var2)
  
#define FTRACES(cat, level, token, fmt, var1) \
engTraceStringEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, \
                    MyNameID, token, (char *)var1)
  
/* tdma only , ITE keeps these for code compatibility */
#define TRACEVAR(cat,level,token,s)   NULL_STATEMENT
#define ERROR(token,s)          trace(MyNameID, token, 0UL, 0UL)
#define FATAL(token,s)          trace(MyNameID, token, 0UL, 0UL)
#define FERROR(token,fmt,var1)  trace(MyNameID, token, (DWORD)var1, 0UL)


void engTraceEvent (const IsotelEngineID engine_id, 
                    const UINT8 cat, const UINT8 level,
                    const UINT8 moduleId, const UINT8 token,
                    UINT8 size1, UINT8 *var1, 
                    UINT8 size2, UINT8 *var2);

void engTraceStringEvent (const IsotelEngineID engine_id,
                          const UINT8 cat, const UINT8 level,
                          const UINT8 mod_id, const UINT8 token,
                          char *var1);

void engTraceDataEvent (const IsotelEngineID engine_id,
                        const UINT8 cat, const UINT8 level,
                        const UINT8 moduleId, const UINT8 token,
                        int size, UINT8 *var1);

void engAssert (const IsotelEngineID engine_id,
                const UINT8 moduleId, unsigned line);

#endif /* TOKEN_TRACING */


#if (ITRACE_TYPE == STRING_TRACING)

#define TRACE_INSTALL(s, i) static CONST char ROM MyName[] = s;

#define IASSERT(expr) if (!(expr)) engAssert(MyName, __LINE__)
  
#define TRACE(cat, level, token, s) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyName, s, \
              0, NULL, 0, NULL)
  
#define TRACEDATA(cat, level, token, dat, len) \
engTraceDataEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyName, "data: ", \
                  len, (UINT8*)dat)
  
#define FTRACE1P(cat, level, token, fmt, var1) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyName, fmt, \
              (UINT8)sizeof(var1), &var1, 0, NULL)
  
#define FTRACE2P(cat, level, token, fmt, var1, var2) \
engTraceEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyName, fmt, \
              (UINT8)sizeof(var1), &var1, (UINT8)sizeof(var2), &var2)
  
#define FTRACES(cat, level, token, fmt, var1) \
engTraceStringEvent(ENGINE_ID, (UINT8)cat, (UINT8)level, MyName, fmt, \
                    (char *)var1)

/* tdma macros, keep for code compatibility */
#define TRACEVAR(cat,level,token,s)   NULL_STATEMENT
#define ERROR(token,s)          trace(MyNameID, token, 0UL, 0UL)
#define FATAL(token,s)          trace(MyNameID, token, 0UL, 0UL)
#define FERROR(token,fmt,var1)  trace(MyNameID, token, (DWORD)var1, 0UL)
  
void engTraceEvent (const IsotelEngineID engine_id,
                    const UINT8 cat, const UINT8 level,
                    const char *modName, 
                    char *string, UINT8 size1, void *var1,
                    UINT8 size2, void *var2);

void engTraceStringEvent (const IsotelEngineID engine_id,
                          const UINT8 cat, const UINT8 level,
                          const char *modName,
                          char *string, char *var1);

void engTraceDataEvent (const IsotelEngineID engine_id,
                        const UINT8 cat, const UINT8 level,
                        const char *modName,
                        char *str, int size, UINT8 *var1);

void engAssert (const char *modName, unsigned line);

#endif /* STRING_TRACING */
#endif /* TRACEON */


/* these things are dummy declarations, if ever referenced
 * gcc will give a link-error */
void trace( BYTE MyNameID, BYTE token, DWORD var1, DWORD var2 ) ;
void traces( BYTE MyNameID, BYTE token, CHAR *str ) ;

#ifdef __cplusplus
  }
#endif /* __cplusplus */

#endif /* _GBL_TRACE_H_ */

/*                      end of gbl_trace.h
--------------------------------------------------------------------------- */








