#pragma once

#include <windows.h>
#include <iostream>
#include <functional>

class Thread
{
public:
	Thread()
	{
		thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Execute, this, CREATE_SUSPENDED, NULL);
	}

	~Thread()
	{
		CloseHandle(thread);
	}

	void Start(std::function<void()> func)
	{
		_func = func;
		WakeUp();
	}
private:
	HANDLE thread;
	std::function<void()> _func;

	void WakeUp()
	{
		ResumeThread(thread);
	}

	void Sleep()
	{
		SuspendThread(thread);
	}

	static void Execute(Thread* currentObject)
	{
		while (true) {
			currentObject->_func();
			currentObject->Sleep();
		}
	}
};