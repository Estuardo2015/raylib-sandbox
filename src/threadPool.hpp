#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "vector"
#include "queue"
#include "thread"
#include "functional"
#include "mutex"
#include "condition_variable"
#include <unistd.h>

class ThreadPool {
public:
    std::vector<std::thread> threads;
    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
    std::condition_variable wait_until_finished_condition;
    std::queue<std::function<void()>> jobs;

    ThreadPool(int);

    void ThreadLoop();

    void QueueJob(const std::function<void()> &);

    bool busy();

    void Stop();

    void WaitUntilFinished();
};

ThreadPool::ThreadPool(int numThreads) {
    threads.resize(numThreads);
    for (uint32_t i = 0; i < numThreads; i++) {
        threads.at(i) = std::thread(&ThreadPool::ThreadLoop, this);
    }
}

void ThreadPool::ThreadLoop() {
    while (true) {
        std::function<void()> job;

        // Create unique lock from queue_mutex
        std::unique_lock<std::mutex> lock(queue_mutex);

        // Check if there are any jobs to run or if we should terminate
        mutex_condition.wait(lock, [this] {
            return !jobs.empty() || should_terminate;
        });
        if (should_terminate) {
            return;
        }

        // Execute a job
        job = jobs.front();
        jobs.pop();

        lock.unlock();
        job();
        wait_until_finished_condition.notify_one();
    }
}

void ThreadPool::QueueJob(const std::function<void()> &job) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    jobs.push(job);
    lock.unlock();

    mutex_condition.notify_one();
}

bool ThreadPool::busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        poolbusy = !jobs.empty();
    }
    return poolbusy;
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread &active_thread: threads) {
        active_thread.join();
    }
    threads.clear();
}

void ThreadPool::WaitUntilFinished() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    wait_until_finished_condition.wait(lock, [this] {
        return jobs.empty();
    });
    lock.unlock();
}

#endif
