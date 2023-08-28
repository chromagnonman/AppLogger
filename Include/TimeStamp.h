#pragma once

#include <chrono>

namespace Rightware {

    namespace utils {

        namespace TimeStamp {

            static auto now() noexcept
            {
                const auto now = std::chrono::system_clock::now();
                const auto time_t = std::chrono::system_clock::to_time_t(now);
                
                return std::ctime(&time_t);
            }
        };
    }
}