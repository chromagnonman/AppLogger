#pragma once

#include <string>

namespace Rightware {

    namespace OutputDevice {
        
        class AOuputDevice {
            public:
            virtual ~AOuputDevice() = default;
            virtual void write(std::string&& msg) = 0;
        };
    }
}