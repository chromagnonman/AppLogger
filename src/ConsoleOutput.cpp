#include <iostream>

#include "ConsoleOutput.h"

namespace Rightware {

    namespace OutputDevice {

        void Console::write(std::string&& msg)
        {
            std::lock_guard<std::mutex> lk{m_mutex};
            std::cout << std::move(msg);
        }
    }
}