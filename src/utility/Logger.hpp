#pragma once

#include<fstream>
#include<iostream>

//Singleton
class Logger
{
public:
    static void message(const std::string& msg);

private:
    Logger();
    ~Logger();
    static Logger* _instance;
    std::ofstream file;
};


