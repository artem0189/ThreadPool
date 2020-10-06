#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	for (int i = 0; i < threadsCount; i++) {
		threads.push_back(new Thread(NULL));
	}
}

ThreadPool::~ThreadPool()
{
	for (int i = 0; i < threadsCount; i++) {
		delete threads[i];
	}
}

template <typename Func, typename... Args>
void ThreadPool::AddTask(Func&& func, Args&&... args)
{
	if (threads.size() > 0) {
	}
}

Thread* ThreadPool::GetFreeThread()
{
	for (int i = 0; i < threadsCount; i++) {
		if (threads[i]->IsAlive()) {
			return threads[i];
		}
	}
}