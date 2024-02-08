// thread_pool.cpp

#include <iostream>
#include <stdexcept>

#include "thread_pool.hpp"

ThreadPool::ThreadPool(int size) : m_stop(false)
{
    for (int i = 0; i < size; ++i)
    {
        m_threads.emplace_back([this]
                               {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

                    if (m_stop && m_tasks.empty()) {
                        return;
                    }

                    task = std::move(m_tasks.front());
                    m_tasks.pop_front();
                }

                task();
            } });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
    }

    m_condition.notify_all();
    for (auto &thread : m_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void ThreadPool::EnqueueTask(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.push_back(std::move(task));
    }
    m_condition.notify_one();
}
