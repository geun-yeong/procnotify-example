#pragma once

#include <ntddk.h>

VOID MyCreateProcessNotifyRoutine(
	_In_ HANDLE parentPid,
	_In_ HANDLE processId,
	_In_ BOOLEAN isCreate
);

VOID MyCreateThreadNotifyRoutine(
	_In_ HANDLE processId,
	_In_ HANDLE threadId,
	_In_ BOOLEAN isCreate
);

VOID MyLoadImageNotifyRoutine(
	_In_opt_ PUNICODE_STRING imageName,
	_In_ HANDLE processId,
	_In_ PIMAGE_INFO imageInfo
);