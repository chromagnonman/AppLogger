#include "Logger.h"

using namespace Rightware;

int main()
{
    core::Logger console("Kanzi");
    core::Logger file("Kani", "logfile.txt");
    core::Logger console2("Unreal");

    for (uint32_t i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        std::string msg { "thread id:" };
        msg += std::to_string(i);

        console.log_info(msg);
        console2.log_info(msg);
        console.log_error(msg);
        console2.log_error(msg);
        console.log_warning(msg);
        console2.log_warning(msg);
        console.log_fatal(msg);
        console2.log_fatal(msg);

        file.log_info(msg);
        file.log_error(msg);
        file.log_warning(msg);
        file.log_fatal(msg);
    }

    return 0;
}