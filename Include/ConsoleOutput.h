#pragma once

#include "OutputDevice.h"

namespace Rightware {

    namespace OutputDevice {

        class Console : public AOuputDevice {
            public:
            Console() = default;
            virtual ~Console() = default;

            void write(std::string&& msg) override;
        };
    }
}