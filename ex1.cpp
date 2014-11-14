/*
   BOOL CreateProcess(
   LPCTSTR lpApplicationName,		//文件名
   LPTSTR lpCommandLine,			//命令行
   LPSECURITY_ATTRIBUTES lpProcessAttributes,	//进程安全描述符
   LPSECURITY_ATTRIBUTES lpThreadAttributes,	//主线程安全描述符
   BOOL bInheritHandles,	//是否继承句柄
   DWORD dwCreationFlags,	//标识
   LPVOID lpEnvironment,	//环境变量指针
   LPCTSTR lpCurrentDirectory,		//当前目录
   LPSTARTUPINFO lpStartupInfo,	//启动信息结构
   LPPROCESS_INFORMATION lpProcessInformation,	//进程信息结构，pcb块
   );
   */
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_LINE_LEN  80

int main(int argc,char *argv[]) {
	char cmdLine[MAX_LINE_LEN];
	
	LPCTSTR lpApplicationName = NULL;
	LPSECURITY_ATTRIBUTES processSA = NULL;
	LPSECURITY_ATTRIBUTES threadSA = NULL;
	BOOL shareRights = TRUE;
	DWORD creationMask = CREATE_NEW_CONSOLE;
	LPVOID environment = NULL;
	LPTSTR curDir = NULL;

	/* Result */
	STARTUPINFO startInfo;							
	PROCESS_INFORMATION processInfo;

	ZeroMemory(&startInfo,sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);

	fstream lx("batch",ios::in);
	while(lx.getline(cmdLine,100)){
		// printf("%s",cmdLine);
		if(!CreateProcess(	
						lpApplicationName,	/* File name of executable */
						cmdLine,			/* Command line */
						processSA,			/* Process inherited security */
						threadSA,			/* Thread inherited security */
						shareRights,		/* Right propagation */
						creationMask,		/* Various creation flags */
						environment,		/* Environment variabkesr */
						curDir,				/* Child's current directory */
						&startInfo,
						&processInfo
						)
		  ) 
		{
			fprintf(stderr,"CreatProcess failed on error %d\n",GetLastError());
			ExitProcess(1);
		};
		fprintf(stdout,"The Child Process's PID: %d.\n", processInfo.dwProcessId);
		fprintf(stdout,"The Parent Process finish.\n");
		Sleep(500);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	};
	Sleep(100000);
	return 0;
}

