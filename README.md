# AppLogger
A simple project that demonstrates the logger class API written in C++. It can support multiple threads (loggers), however, the logs are processed sequentially with their respective timestamps. Currently, the logs are written to the console by default; they can also be written into a log file. The class can also be extended to support some other output device in the future.

The project requires at least C++ 11 as it uses `std::thread` library along with the standard C++ synchronization primitives.

## Build and run the application
Download the `.zip` file or clone the repo. The project utilizes `CMake` to generate the build configuration files. 

In Linux, open the terminal and navigate to the project folder, then run the command: `mkdir build && cd build && cmake ..`. To build the project, run: `make -j2`. `j2` denotes the number of threads the compiler utilizes in building the project. Run the app by entering `./AppLogger`.

In Windows, use Powershell or the terminal to generate the build files using CMake command: `mkdir build && cd build && cmake ..`. Open the `.vcxproj` or `.sln` file in the latest Visual Studio IDE (2022) to build and run the application.

## Caveat
When building the project in Windows, you may need to modify the project properties and set the `C++ Language Standard` to `C++ 17`.
