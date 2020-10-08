#pragma once

#include "Logger.h"
#include <windows.h>
#include <iostream>
#include <functional>
#include <string>

class Thread
{
public:
	bool isActive = false;

	Thread(int id, Logger* logger)
	{
		_id = id;
		_logger = logger;
		_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Execute, this, CREATE_SUSPENDED, NULL);
	}

	~Thread()
	{
		Kill();
	}

	void Start(std::function<void()> func)
	{
		_func = func;
		WakeUp();
	}
private:
	int _id;
	HANDLE _thread;
	std::function<void()> _func;
	Logger* _logger;

	void WakeUp()
	{
		isActive = true;
		ResumeThread(_thread);
	}

	void Sleep()
	{
		isActive = false;
		SuspendThread(_thread);
	}

	void Kill()
	{
		TerminateThread(_thread, 0);
		CloseHandle(_thread);
	}

	static void Execute(Thread* currentObject)
	{
		while (true) {
			try {
				currentObject->_func();
			}
			catch (...) {
				currentObject->_logger->Output("Было поймано исключение потоком номер: " + std::to_string(currentObject->_id));
			}
			currentObject->Sleep();
		}
	}
};