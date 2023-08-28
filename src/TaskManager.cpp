#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "TaskManager.h"

namespace Rightware {

    namespace core {

        struct TaskManager::impl {

            void execute(std::thread&& task)
            {
                {
                    std::unique_lock<std::mutex> lk{m_task_mtx};
                    m_task_cv.wait(lk, [&] {return m_thread_count < std::thread::hardware_concurrency();});
                    
                    m_tasks.emplace_back(std::move(task));
                    ++m_thread_count;
                    
                    auto& t = m_tasks.back();
                    if (t.joinable())
                    {
                        t.join();
                        --m_thread_count;
                    }
                }

                m_task_cv.notify_one();
            }

            void flush()
            {
                std::lock_guard<std::mutex> lk{m_task_mtx};
                for (auto& task : m_tasks)
                {
                    if (task.joinable())
                    {
                        task.join();
                    }
                }
            }

            size_t thread_count() const
            {
                std::lock_guard<std::mutex> lk{m_task_mtx};
                return m_thread_count;
            }

            private:
            std::vector<std::thread> m_tasks;
            mutable std::mutex m_task_mtx;
            std::condition_variable m_task_cv;
            std::atomic<uint32_t> m_thread_count{0};
        };

        TaskManager::TaskManager() : m_Impl{std::make_unique<impl>()}
        {
        }

        TaskManager::~TaskManager()
        {
            m_Impl->flush();
        }

        void TaskManager::flush()
        {
            m_Impl->flush();
        }

        void TaskManager::execute(std::thread&& task)
        {
            m_Impl->execute(std::move(task));
        }
    }
}