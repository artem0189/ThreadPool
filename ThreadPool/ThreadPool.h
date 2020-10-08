#pragma once

#include "Thread.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>

#define DEFAULT_THREADS_COUNT 5

class ThreadPool
{
public:
	ThreadPool()
	{
		_logger = new Logger("log.txt");
		_mainThread = new Thread(999, _logger);
		_mainThread->Start(std::bind(InitThreads, this));
		while (_mainThread->isActive) {}
	}

	~ThreadPool()
	{
		for (int i = 0; i < threadsCount; i++) {
			delete _threads[i];
		}
	}

	template <typename FuncType, typename... Args>
	void AddTask(FuncType func, Args&&... args)
	{
		std::function<void()> test = std::bind(func, std::forward<Args>(args)...);
		_mainThread->Start(std::bind(Execute, this, test));
	}

	void WaitForThreads()
	{
		bool result;
		do
		{
			result = true;
			for (int i = 0; i < threadsCount; i++) {
				result &= !_threads[i]->isActive;
			}
		} while (!result);
	}
private:
	Thread* _mainThread;
	std::vector<Thread*> _threads;
	int threadsCount = DEFAULT_THREADS_COUNT;
	Logger* _logger;

	static void InitThreads(ThreadPool* currentObject)
	{
		for (int i = 0; i < currentObject->threadsCount; i++) {
			currentObject->_threads.push_back(new Thread(i, currentObject->_logger));
			currentObject->_logger->Output("—оздание потока номер: " + std::to_string(i));
		}
	}

	static void Execute(ThreadPool* currentObject, std::function<void()> func)
	{
		int index = currentObject->GetFreeThreadIndex();
		if (index >= 0) {
			currentObject->_threads[index]->Start(func);
			currentObject->_logger->Output("ƒобавлена задача, выполн€етс€ потоком номер: " + std::to_string(index));
		}
		else {
			currentObject->_logger->Output("ѕревышение максимально допустимого количества работающих потоков");
		}
	}

	int GetFreeThreadIndex()
	{
		for (int i = 0; i < threadsCount; i++)
		{
			if (!_threads[i]->isActive) {
				return i;
			}
		}
		return -1;
	}
};