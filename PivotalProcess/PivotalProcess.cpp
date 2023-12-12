// PivotalProcess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
BOOLEAN SetCurrentProcessAsPivotal()
{
	BOOLEAN tmp1;
	ULONG tmp2 = TRUE;
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtSetInformationProcess = GetProcAddress(ntdll, "NtSetInformationProcess");
	if (RtlAdjustPrivilege != NULL && NtSetInformationProcess != NULL)
	{
		((void(*)(DWORD, BOOLEAN, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(20, TRUE, FALSE, &tmp1);
		((void(*)(HANDLE, PROCESS_INFORMATION_CLASS, PVOID, ULONG))NtSetInformationProcess)(GetCurrentProcess(), (PROCESS_INFORMATION_CLASS)29, &tmp2, sizeof(tmp2));
		return 1;
	}
	else return 0;
}
BOOLEAN CancelCurrentPivotalProcess()
{
	ULONG Flag = FALSE;
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC NtSetInformationProcess = GetProcAddress(ntdll, "NtSetInformationProcess");
	if (NtSetInformationProcess != NULL)
	{
		((void(*)(HANDLE, PROCESS_INFORMATION_CLASS, PVOID, ULONG))NtSetInformationProcess)(GetCurrentProcess(), (PROCESS_INFORMATION_CLASS)29, &Flag, sizeof(Flag));
		return 1;
	}
	else return 0;
}
void main()
{
	char ch;
	BOOL r;
	printf("输入a设置当前进程为关键进程，输入b取消当前进程为关键进程，输入q退出.\n");
	do
	{
		scanf("%c", &ch);
		if (ch == 'a' || ch == 'A')
		{
			if (SetCurrentProcessAsPivotal())printf("设置成功\n");
			else printf("设置失败\n");
		}
		if (ch == 'b' || ch == 'B')
		{
			if (CancelCurrentPivotalProcess())printf("取消成功\n");
			else printf("取消失败\n");
		}
	} 
	while (ch!='Q'&&ch!='q');
	IsProcessCritical(GetCurrentProcess(), &r);
	if (r) CancelCurrentPivotalProcess();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
