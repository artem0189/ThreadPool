#include "Thread.h"

Thread::Thread(LPTHREAD_START_ROUTINE lpStartAddress)
{
	thread = CreateThread(NULL, 0, lpStartAddress, NULL, CREATE_SUSPENDED, NULL);
}

Thread::~Thread()
{
	CloseHandle(thread);
}

bool Thread::IsAlive()
{
	DWORD status;
	GetExitCodeThread(thread, &status);
	return status == STILL_ACTIVE;
}