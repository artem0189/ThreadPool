#pragma once

#include "Thread.h"
#include <iostream>
#include <vector>

#define DEFAULT_THREADS_COUNT 1

class ThreadPool
{
public:
	ThreadPool()
	{
		for (int i = 0; i < threadsCount; i++) {
			waitThreads.push_back(new Thread());
		}
	}

	~ThreadPool()
	{
		for (int i = 0; i < threadsCount; i++) {
			delete waitThreads[i];
		}
	}

	template <typename FuncType, typename... Args>
	void AddTask(FuncType func, Args&&... args)
	{
		if (!waitThreads.empty()) {
			Thread* thread = waitThreads.back();
			waitThreads.pop_back();
			activeThreads.push_back(thread);
			thread->Start(std::bind(func, std::forward<Args>(args)...));
		}
	}

	void WaitForThreads()
	{
		while (waitThreads.size() != threadsCount) {}
	}
private:
	int threadsCount = DEFAULT_THREADS_COUNT;
	std::vector<Thread*> activeThreads;
	std::vector<Thread*> waitThreads;
};