#include <iostream>

#include "ConsoleOutput.h"

namespace Rightware {

    namespace OutputDevice {

        void Console::write(std::string&& msg)
        {
            std::cout << std::move(msg);
        }
    }
}