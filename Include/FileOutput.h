#pragma once

#include "OutputDevice.h"

#include <fstream>
#include <string>

namespace Rightware
{

namespace OutputDevice
{

    class File : public AOuputDevice
    {
    public:
        explicit File(std::string file);
        virtual ~File();

        void write(std::string&& msg) override;
        void remove(const std::string& file);

    private:
        std::fstream m_file;
    };
}
}