#pragma once

#include "Thread.h"
#include <vector>

#define DEFAULT_THREADS_COUNT 5

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	template <typename Func, typename... Args>
	void AddTask(Func&& func, Args&&... args);
	Thread* GetFreeThread();
private:
	int threadsCount = DEFAULT_THREADS_COUNT;
	std::vector<Thread*> threads;
};