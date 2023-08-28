#pragma once

#include <memory>
#include <thread>
#include <mutex>

namespace Rightware {

    namespace core {

        static std::mutex task_manager_mutex;
        
        /**
         * @brief Manages invocable thread objects. Only one instance of this class is allowed.
         * TODO: Add other useful functions such as reporting number of threads running, etc. 
         * 
         */
        class TaskManager {
            public:
            virtual ~TaskManager();

            TaskManager(const TaskManager&) = delete;
            TaskManager& operator=(const TaskManager&) = delete;

            static TaskManager* getInstance()
            {
                static std::unique_ptr<TaskManager> instance = nullptr;

                std::lock_guard<std::mutex> lk{task_manager_mutex};
                
                if (!instance) {
                    instance = std::unique_ptr<TaskManager>(new TaskManager());
                }

                return instance.get();
            }

            /**
             * @brief Invokes the thread object
             * 
             * @param task invocable thread object
             */
            void execute(std::thread&& task);

            /**
             * @brief Terminates (joins) the remaining threads
             * 
             */
            void flush();

            private:
            TaskManager();
            
            struct impl;
            std::unique_ptr<impl> m_Impl;
        };
    }
}
