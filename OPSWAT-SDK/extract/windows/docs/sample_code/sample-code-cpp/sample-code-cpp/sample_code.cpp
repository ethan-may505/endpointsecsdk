// sample-code-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS


#include <map>
#include <chrono>
#include "OesisUtils.h"
#include "OesisCommand.cpp"

#include <future>

using namespace std::chrono;


int main(int argc, char** argv)
{
    // prevents crashes when setup fails due to WaJson unwinding
    // this is gross, but temporary
    try
    {
        OesisCommand::main(argc, argv);
    }
    catch (exception exc) {};

    if (!OesisCommand::g_autoExit)
    {
        std::wcout << std::endl << L"Press enter to exit..." << std::endl;
        getchar();
    }
    return 0;
}
