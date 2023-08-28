#include <gtest/gtest.h>
#include "Logger.h"

using namespace Rightware;
using namespace Rightware::core;

TEST(Logger, ConsoleLogInfo)
{
    Logger logger("Kanzi");

    testing::internal::CaptureStdout();

    logger.log_info("Application running");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application running"));

    testing::internal::CaptureStdout();

    std::string msg{"Application terminated: "};
    logger.log_info(msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application terminated"));

    testing::internal::CaptureStdout();

    logger.log_message(utils::log_level::INFO, msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("INFO: Application terminated"));

    testing::internal::CaptureStdout();

    std::string user{"Administrator"};
    logger.log_message(utils::log_level::INFO, msg, user);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Administrator"));
}

TEST(Logger, ConsoleLogError)
{
    Logger logger("Firefox");

    testing::internal::CaptureStdout();

    logger.log_error("Application running");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application running"));

    testing::internal::CaptureStdout();

    std::string msg{"Application terminated: "};
    logger.log_error(msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application terminated"));

    testing::internal::CaptureStdout();

    logger.log_message(utils::log_level::ERROR, msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("ERROR: Application terminated"));

    testing::internal::CaptureStdout();

    std::string user{"Administrator"};
    logger.log_message(utils::log_level::ERROR, msg, user);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Administrator"));
}

TEST(Logger, ConsoleLogWarning)
{
    Logger logger("Chrome");

    testing::internal::CaptureStdout();

    logger.log_warning("Application running");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application running"));

    testing::internal::CaptureStdout();

    std::string msg{"Application terminated: "};
    logger.log_warning(msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application terminated"));

    testing::internal::CaptureStdout();

    logger.log_message(utils::log_level::WARNING, msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("WARNING: Application terminated"));

    testing::internal::CaptureStdout();

    std::string user{"Administrator"};
    logger.log_message(utils::log_level::WARNING, msg, user);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Administrator"));
}

TEST(Logger, ConsoleLogFatal)
{
    Logger logger("CLion");

    testing::internal::CaptureStdout();

    logger.log_fatal("Application running");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application running"));

    testing::internal::CaptureStdout();

    std::string msg{"Application terminated: "};
    logger.log_fatal(msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Application terminated"));

    testing::internal::CaptureStdout();

    logger.log_message(utils::log_level::FATAL, msg);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("FATAL: Application terminated"));

    testing::internal::CaptureStdout();

    std::string user{"Administrator"};
    logger.log_message(utils::log_level::FATAL, msg, user);

    output = testing::internal::GetCapturedStdout();
    ASSERT_NE(std::string::npos, output.find("Administrator"));
}

TEST (Logger, FileLogOutput)
{
    { // Need to destroy log_file object so that the file can be read
        Logger log_file("Unreal Engine", "logfile.txt");

        log_file.log_info("Logfile created.");
        log_file.log_error("Error log");
        log_file.log_warning("Warning log");
        log_file.log_fatal("Fatal log");
    }

    std::ifstream file("logfile.txt");
    ASSERT_TRUE(file.is_open());

    std::ostringstream stream;
    stream << file.rdbuf();

    std::string log;
    log = stream.str();
    ASSERT_FALSE(log.empty());

    EXPECT_NE(std::string::npos, log.find("Logfile created."));
    EXPECT_NE(std::string::npos, log.find("Error log"));
    EXPECT_NE(std::string::npos, log.find("Warning log"));
    EXPECT_NE(std::string::npos, log.find("Fatal log"));
}


TEST (Logger, MultipleFileLoggers)
{
    { // Need to destroy log_file object so that the file can be read
        Logger log_file("Unity", "logfile.txt");
        Logger log_file2("Unreal", "logfile2.txt");

        log_file.log_info("Logfile created.");
        log_file2.log_info("Logfile created.");

        log_file.log_error("Error log");
        log_file2.log_error("Error log");

        log_file.log_warning("Warning log");
        log_file2.log_warning("Warning log");

        log_file.log_fatal("Fatal log");
        log_file2.log_fatal("Fatal log");
    }

    std::ifstream file("logfile.txt");
    ASSERT_TRUE(file.is_open());

    std::ostringstream stream;
    stream << file.rdbuf();

    std::string log;
    log = stream.str();
    ASSERT_FALSE(log.empty());

    EXPECT_NE(std::string::npos, log.find("Logfile created."));
    EXPECT_NE(std::string::npos, log.find("Error log"));
    EXPECT_NE(std::string::npos, log.find("Warning log"));
    EXPECT_NE(std::string::npos, log.find("Fatal log"));
}

