#include "notify.h"
#include <minwindef.h>



VOID MyCreateProcessNotifyRoutine(
	_In_ HANDLE parentPid,
	_In_ HANDLE processId,
	_In_ BOOLEAN isCreate
)
{
	if (isCreate) {
		KdPrint(("[procnotify] " __FUNCTION__ " PPID(%u) created PID(%u)\n",
			     PtrToUint(parentPid),
			     PtrToUint(processId)));
	}
	else {
		KdPrint(("[procnotify] " __FUNCTION__ " PID(%u) was terminated\n",
			     PtrToUint(processId)));
	}
}



VOID MyCreateThreadNotifyRoutine(
	_In_ HANDLE processId,
	_In_ HANDLE threadId,
	_In_ BOOLEAN isCreate
)
{
	if (isCreate) {
		KdPrint(("[procnotify] " __FUNCTION__ " TID(%u) was created in PID(%u) by PID(%u)\n",
			     PtrToUint(threadId),                  // made thread
			     PtrToUint(processId),                 // process that thread was made
			     PtrToUint(PsGetCurrentProcessId()))); // process that make this thread
	}
	else {
		KdPrint(("[procnotify] " __FUNCTION__ " TID(%u) in PID(%u) was terminated\n",
			     PtrToUint(threadId),
			     PtrToUint(processId)));
	}
}



VOID MyLoadImageNotifyRoutine(
	_In_opt_ PUNICODE_STRING imageName,
	_In_ HANDLE processId,
	_In_ PIMAGE_INFO imageInfo
)
{
	if (imageName) {
		KdPrint(("[procnotify] " __FUNCTION__ " PID(%u) loaded a/an %wZ at 0x%p\n",
			     PtrToUint(processId),
			     imageName,
			     imageInfo->ImageBase));
	}
}