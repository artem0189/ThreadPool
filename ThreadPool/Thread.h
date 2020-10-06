#pragma once

#include <windows.h>

class Thread
{
public:
	Thread(LPTHREAD_START_ROUTINE);
	~Thread();
	bool IsAlive();
private:
	HANDLE thread;
};