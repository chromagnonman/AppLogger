#pragma once

#include "ConsoleOutput.h"
#include "FileOutput.h"
#include "SeverityLevel.h"
#include "TaskManager.h"
#include "TimeStamp.h"

#include <algorithm>
#include <execution>
#include <memory>
#include <sstream>
#include <string>

// TODO: Define convenience Macros: LOG_INFO, LOG_ERROR, LOG_WARNING, LOG_FATAL
namespace Rightware
{

namespace core
{
    /**
     * @brief  Provides API to log messages. By default it outputs the messages to the console.
     * It can support writing logs into a file. Can also be extended to support other output device.
     *
     */
    class Logger
    {

    public:
        /**
         * @brief Construct a new Logger object, which writes the log messages to the console
         *
         * @param appID Unique name or ID of the application
         */
        Logger(std::string appID)
            : m_appID { std::move(appID) }
        {
            m_output_device = std::make_shared<Rightware::OutputDevice::Console>();
        }

        /**
         * @brief Construct a new Logger object, which writes log messages into a file.
         *
         * @param appID Unique name or ID of the application
         * @param file name where the logs will be written
         */
        Logger(std::string appID, std::string file)
            : m_appID { std::move(appID) }
            , m_logfile { std::move(file) }
        {
            m_output_device = std::make_shared<Rightware::OutputDevice::File>(m_logfile);
        }

        virtual ~Logger() = default;

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        // TODO: Do some type checks - SFINAE
        template <typename T>
        void log_message(const utils::log_level& log_level, T&& msg)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type_literal(log_level) << std::forward<T>(msg);
            log_message(log_msg.str());
        }

        template <typename T, typename U>
        void log_message(const utils::log_level& log_level, T&& msg, U&& user)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type_literal(log_level) << std::forward<T>(msg) << std::forward<T>(user);
            log_message(log_msg.str());
        }

        template <typename T>
        void log_info(T&& msg)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type::INFO << std::forward<T>(msg);
            log_message(log_msg.str());
        }

        template <typename T>
        void log_error(T&& msg)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type::ERROR << std::forward<T>(msg);
            log_message(log_msg.str());
        }

        template <typename T>
        void log_warning(T&& msg)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type::WARNING << std::forward<T>(msg);
            log_message(log_msg.str());
        }

        template <typename T>
        void log_fatal(T&& msg)
        {
            std::ostringstream log_msg;

            log_msg << m_appID << utils::log_type::FATAL << std::forward<T>(msg);
            log_message(log_msg.str());
        }

        void log_message(std::string&& msg)
        {
            std::ostringstream log_msg;

            std::string timestamp = utils::TimeStamp::now();
            std::replace(std::execution::par, timestamp.begin(), timestamp.end(), '\n', ' ');

            log_msg << timestamp << std::move(msg) << '\n';

            TaskManager::getInstance()->execute(
                std::thread([&] { m_output_device->write(std::move(log_msg.str())); }));
        }

    private:
        std::string m_appID;
        std::string m_logfile;
        std::shared_ptr<Rightware::OutputDevice::AOuputDevice> m_output_device;
    };
}
}
