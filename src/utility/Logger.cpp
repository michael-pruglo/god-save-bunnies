#include "Logger.hpp"

Logger* Logger::_instance = nullptr;

void Logger::message(const std::string& msg)
{
    if (Logger::_instance == nullptr)
        Logger::_instance = new Logger;

    std::cout<<msg<<std::endl;
    Logger::_instance->file<<msg<<"\n";
}

Logger::Logger()
    : file("log.txt")
{
}

Logger::~Logger()
{
    file.close();
}
