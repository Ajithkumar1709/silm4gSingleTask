#define _LCC_DEBUG

#define _WIN32_WINNT 0x0400

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


/*************************Functions Declarations*****************************/
BOOL SetFileToSpecTime(HANDLE hFile,SYSTEMTIME * pSysTime);
int  GetSpecTime(char * szTime, SYSTEMTIME * pSysTime);
int  StrToInt(char * str,int start,int end);

#define DEFAULT_TIME "20190101010101"
int main(int argc, char *argv[])
{
  SYSTEMTIME st;
  HANDLE hFile;

#if 0
  if ( (argc != 2) )
  {
  #ifdef _LCC_DEBUG
      printf("Format:%s filename time",argv[0]);
    printf("\nExample:%s test.txt 20040715140810",argv[0]);
  #endif
    return (0);
  }
  else if ( strlen(DEFAULT_TIME)!=14)
  {
    #ifdef _LCC_DEBUG
      printf("Argument Error.time string length is 14.");
  #endif
  return (0);
  }
#endif

  if ( GetSpecTime(DEFAULT_TIME,&st) == 0 )
  {
    #ifdef _LCC_DEBUG
    printf("Time Error.");
  #endif
    return (0);
  }

  hFile = CreateFile(argv[1],                   //LPCTSTR lpFileName,
            GENERIC_READ|GENERIC_WRITE,         //DWORD dwDesiredAccess,
            FILE_SHARE_READ|FILE_SHARE_DELETE,
            NULL,                //LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,         //DWORD dwFlagsAndAttributes,
            NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
  #ifdef _LCC_DEBUG
      printf ("Invalid File Handle. Error#:%d\n", GetLastError ());
  #endif
    return (0);
  }
  else
  {
    #ifdef _LCC_DEBUG
      printf("[%d-%d-%d_%d:%d:%d][%s]\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond,
            argv[1]
	    );
    #endif
    if( SetFileToSpecTime(hFile,&st) ==0)
    {
      #ifdef _LCC_DEBUG
       printf("fail to set file time.\n");
      #endif
    }

    CloseHandle(hFile);
    return (1);
  }
}


int StrToInt(char * str,int start,int end)
{
  int result=0;

  if(start>end)
  {
    result = -1;
  }
  else
  {
    while(start<=end)
    {
      result = (str[start]-'0') + result*10;
      start ++;
    }
  }

  return result;
}


int GetSpecTime(char * szTime, SYSTEMTIME * pSysTime)
{
  int i;
  for(i=0;i<14;)
  {
    if( (szTime[i]>='0') &&(szTime[i]<='9') )
      i++;
    else
    {
    #ifdef _LCC_DEBUG
      printf("Invalid time string.\n");
    #endif
    return 0;
    }
  }

  pSysTime->wYear         = StrToInt(szTime,0,3);
  pSysTime->wMonth        = StrToInt(szTime,4,5);
  pSysTime->wDayOfWeek    = 1;             //is ignored by SystemTimeToFileTime
  pSysTime->wDay          = StrToInt(szTime,6,7);
  pSysTime->wHour         = StrToInt(szTime,8,9);
  pSysTime->wMinute       = StrToInt(szTime,10,11);
  pSysTime->wSecond       = StrToInt(szTime,12,13);
  pSysTime->wMilliseconds = 0;

  if( (pSysTime->wYear <1601)
      || (pSysTime->wMonth <1)   || (pSysTime->wMonth  >12 )
      || (pSysTime->wDay  < 0 )  || (pSysTime->wDay    >31 )
      || (pSysTime->wHour < 0 )  || (pSysTime->wHour   >23 )
      || (pSysTime->wMinute <0)  || (pSysTime->wMinute >59 )
      || (pSysTime->wMinute <0)  || (pSysTime->wMinute >59 ) )
  {
  #ifdef _LCC_DEBUG
    printf("time overflow.\n");
  #endif
    return 0;
  }
  else
  {
    return 1;
  }
}

 

BOOL SetFileToSpecTime(HANDLE hFile,SYSTEMTIME * pSysTime)
{
  FILETIME ft,LocalFileTime;
  BOOL f;

  SystemTimeToFileTime(pSysTime, &ft);
  LocalFileTimeToFileTime(&ft,&LocalFileTime);

  f = SetFileTime(hFile,
                  &LocalFileTime,
                  (LPFILETIME) NULL,
                  &LocalFileTime);
  return f;
}
