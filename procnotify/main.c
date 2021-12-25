#include <ntddk.h>
#include "notify.h"
#include "error.h"

VOID DriverUnload(
	_In_ PDRIVER_OBJECT driverObject
);



NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT driverObject,
	_In_ PUNICODE_STRING registryPath
)
{
	UNREFERENCED_PARAMETER(driverObject);
	UNREFERENCED_PARAMETER(registryPath);



	NTSTATUS status = STATUS_SUCCESS;



	status = PsSetCreateProcessNotifyRoutine(MyCreateProcessNotifyRoutine,
		                                     FALSE);
	IF_ERROR(PsSetCreateProcessNotifyRoutine, EXIT_OF_DRIVER_ENTRY);
	KdPrint(("[procnotify] " __FUNCTION__ " PsSetCreateProcessNotifyRoutine success\n"));
	
	status = PsSetCreateThreadNotifyRoutine(MyCreateThreadNotifyRoutine);
	IF_ERROR(PsSetCreateThreadNotifyRoutine, EXIT_OF_DRIVER_ENTRY);
	KdPrint(("[procnotify] " __FUNCTION__ " PsSetCreateThreadNotifyRoutine success\n"));

	status = PsSetLoadImageNotifyRoutine(MyLoadImageNotifyRoutine);
	IF_ERROR(PsSetLoadImageNotifyRoutine, EXIT_OF_DRIVER_ENTRY);
	KdPrint(("[procnotify] " __FUNCTION__ " PsSetLoadImageNotifyRoutine success\n"));



	driverObject->DriverUnload = DriverUnload;



EXIT_OF_DRIVER_ENTRY:

	if (!NT_SUCCESS(status)) {
		DriverUnload(driverObject);
	}

	return status;
}



VOID DriverUnload(
	_In_ PDRIVER_OBJECT driverObject
)
{
	UNREFERENCED_PARAMETER(driverObject);

	PsSetCreateProcessNotifyRoutine(MyCreateProcessNotifyRoutine, TRUE);
	PsRemoveCreateThreadNotifyRoutine(MyCreateThreadNotifyRoutine);
	PsRemoveLoadImageNotifyRoutine(MyLoadImageNotifyRoutine);
}