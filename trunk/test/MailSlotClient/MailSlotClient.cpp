﻿// MailSlotClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// https://docs.microsoft.com/zh-cn/windows/win32/ipc/writing-to-a-mailslot

/*
Writing to a mailslot is similar to writing to a standard disk file. 
The following code uses the CreateFile, WriteFile, and CloseHandle functions to put a short message in a mailslot. 
The message is broadcast to the mailslot server named "sample_mailslot" on the local computer. 
The code operates under the assumption that the mailslot server was already created.
*/

#include <windows.h>
#include <stdio.h>

LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");

BOOL WriteSlot(HANDLE hSlot, LPCTSTR lpszMessage)
{
    BOOL fResult;
    DWORD cbWritten;

    fResult = WriteFile(hSlot,
                        lpszMessage,
                        (DWORD)(lstrlen(lpszMessage) + 1) * sizeof(TCHAR),
                        &cbWritten,
                        (LPOVERLAPPED)NULL);

    if (!fResult) {
        printf("WriteFile failed with %d.\n", GetLastError());
        return FALSE;
    }

    printf("Slot written to successfully.\n");

    return TRUE;
}

int main()
{
    HANDLE hFile;

    hFile = CreateFile(SlotName,
                       GENERIC_WRITE,
                       FILE_SHARE_READ,
                       (LPSECURITY_ATTRIBUTES)NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       (HANDLE)NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("CreateFile failed with %d.\n", GetLastError());
        return FALSE;
    }

    WriteSlot(hFile, TEXT("Message one for mailslot."));
    WriteSlot(hFile, TEXT("Message two for mailslot."));

    Sleep(5000);

    WriteSlot(hFile, TEXT("Message three for mailslot."));

    CloseHandle(hFile);

    return TRUE;
}
