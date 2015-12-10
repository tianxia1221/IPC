// 01PipeB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

#define BUFSIZE 4096

int _tmain(int argc, _TCHAR* argv[])
{
   CHAR chBuf[BUFSIZE]; 
   DWORD dwRead, dwWritten; 
   HANDLE hStdin, hStdout; 
   BOOL bSuccess; 
 
   hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
   hStdin = GetStdHandle(STD_INPUT_HANDLE); 
   if ( 
       (hStdout == INVALID_HANDLE_VALUE) || 
       (hStdin == INVALID_HANDLE_VALUE) 
      ) 
      ExitProcess(1); 
 
   // Send something to this process's stdout using printf.
   printf("\n ** This is a message from the child process. ** \n");
   fflush( stdout );  
  // This simple algorithm uses the existence of the pipes to control execution.
   // It relies on the pipe buffers to ensure that no data is lost.
   // Larger applications would use more advanced process control.
  int i = 0;
  int j = 0;
   for (;;i++) 
   { 
   // Read from standard input and stop on error or no data.
      bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL); 
      
      if (! bSuccess || dwRead == 0) 
         break; 
	  //printf("\n **CHILD times . START************ %d \n", i ); //for test tx
	  fflush( stdout ); 
	  dwWritten = 0;
   // Write to standard output and stop on error.	//for test tx
      bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL); 
	  j  = j + dwWritten;
		  printf("ThreadID: %d  times: %d\n current size:%d  total size:%d\n\n", GetCurrentThreadId(),i,dwWritten,j );   //for test tx
	 //printf("NNNNNNN %d TX", i );
	  fflush( stdout ); 
	//      Sleep(10000);
     Sleep(3000);
	 fflush( stdout ); 
	
      if (! bSuccess) 
         break; 
   } 

   CloseHandle(hStdout);
   return 0;
}

