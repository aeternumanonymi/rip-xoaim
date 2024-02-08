// thread_pool.h
#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "logging.hpp"

class ThreadPool
{
public:
    explicit ThreadPool(int size);
    ~ThreadPool();

    void EnqueueTask(std::function<void()> task);

private:
    std::vector<std::thread> m_threads;
    std::deque<std::function<void()>> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_stop;
};
