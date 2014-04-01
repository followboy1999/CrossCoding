#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BUFSIZE 4096
void main()
{
	 HANDLE hFile;
	 HANDLE hTempFile; 
	 DWORD  dwBytesRead, dwBytesWritten, dwBufSize=BUFSIZE;
	 DWORD FileSize;
	 char szTempName[MAX_PATH];
	 char buffer[BUFSIZE]; 
	 char lpPathBuffer[BUFSIZE];

	 // Open the existing file. 
	 hFile = CreateFile("Chkps.bak",  // file name 
	  GENERIC_READ,                   // open for reading 
	  0,                              // do not share 
	  NULL,                           // default security 
	  OPEN_EXISTING,                  // existing file only 
	  FILE_ATTRIBUTE_NORMAL,          // normal file 
	  NULL);                          // no template 

	 if (hFile == INVALID_HANDLE_VALUE) 
	 { 
		  printf("Could not open file.");
	 } 

	 //Get file size
	 FileSize=GetFileSize(hFile,NULL);

	 if (ReadFile(hFile, buffer, FileSize, 
		   &dwBytesRead, NULL)==0)
	 {
		 printf("Could not read file.");
	 }
	 CloseHandle(hFile); 

	 __asm{
		 xor eax,eax
       loop1:
	     mov bl,byte ptr [buffer+eax]
		 add eax,2
		 sub bl,0xfb
		 cmp eax,FileSize
		 mov byte ptr [buffer+eax-2],bl
		 jl loop1

         xor eax,eax
       loop2:
		 mov bl,byte ptr [buffer+eax]
	     sub bl,0x3
		 mov byte ptr [buffer+eax],bl
		 inc eax
		 cmp eax,FileSize
		 jl loop2

		 
	 }
	 // Get the temp path
	 GetTempPath(dwBufSize,   // length of the buffer
	  lpPathBuffer);      // buffer for path 
	 // Create a temporary file. 
	 GetTempFileName(lpPathBuffer, // directory for temp files 
	  "CRACKED.txt",                    // temp file name prefix 
	  0,                        // create unique name 
	  szTempName);              // buffer for name 

	 DeleteFile(szTempName);

	 hTempFile = CreateFile((LPTSTR) szTempName,  // file name 
	  GENERIC_READ | GENERIC_WRITE, // open for read/write 
	  0,                            // do not share 
	  NULL,                         // default security 
	  CREATE_ALWAYS,                // overwrite existing file
	  FILE_ATTRIBUTE_NORMAL,        // normal file 
	  NULL);                        // no template 
	 if (hTempFile == INVALID_HANDLE_VALUE) 
	 { 
		  printf("Could not create temporary file."); 
	 } 
	 // Read 4K blocks to the buffer. 
	 // Change all characters in the buffer to upper case. 
	 // Write the buffer to the temporary file. 
	 CharUpperBuff(buffer, FileSize); 
	 WriteFile(hTempFile,buffer,FileSize,&dwBytesWritten,NULL);

	 // Close both files. 

	 CloseHandle(hTempFile); 
	 // Move the temporary file to the new text file.
	

}