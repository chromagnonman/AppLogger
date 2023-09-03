#pragma once

#include <string>

namespace Rightware
{

namespace utils
{

    enum class log_level : size_t
    {
        INFO,
        ERROR,
        WARNING,
        FATAL
    };

    namespace log_type
    {
        static constexpr auto INFO = " INFO: ";
        static constexpr auto ERROR = " ERROR: ";
        static constexpr auto WARNING = " WARNING: ";
        static constexpr auto FATAL = " FATAL: ";
    }

    [[nodiscard]] std::string log_type_literal(const log_level& log)
    {
        switch (log)
        {

        case log_level::INFO:
            return log_type::INFO;

        case log_level::ERROR:
            return log_type::ERROR;

        case log_level::WARNING:
            return log_type::WARNING;

        case log_level::FATAL:
            return log_type::FATAL;
        }

        return log_type::INFO;
    }
}
}
