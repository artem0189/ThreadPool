#include <iostream>
#include "ThreadPool.h"

void PrintHelloWorld()
{
    std::cout << "Hello, world!" << std::endl;
}

void ErrorFunction()
{
    throw "Error";
}

int main()
{
    ThreadPool* pool = new ThreadPool();
    pool->AddTask(PrintHelloWorld);
    pool->WaitForThreads();
    delete pool;
}
