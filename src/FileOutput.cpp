#include <fstream>
#include <iostream>

#include "FileOutput.h"

namespace Rightware {
    
    namespace OutputDevice {

        File::File(std::string file)
        {
            std::lock_guard<std::mutex> lk{m_mutex};

            m_file.exceptions(std::ifstream::badbit);

            try {
                m_file.open(file, std::ios::out);
            } catch(const std::ifstream::failure& error) {
                std::cerr << "Failed to open file: " << error.what() << std::endl;
            }
        }

        File::~File()
        {
            std::lock_guard<std::mutex> lk{m_mutex};

            m_file.close();
        }

        void File::write(std::string&& msg)
        {
            std::lock_guard<std::mutex> lk{m_mutex};

            if (m_file.is_open())
            {
                m_file << std::move(msg);
            }
        }

        void File::remove(const std::string& file)
        {
            std::lock_guard<std::mutex> lk{m_mutex};

            if (std::remove(file.c_str()) != 0)
            {
                std::cout << "Failed to remove: " << file;
            }
        }
    }
}