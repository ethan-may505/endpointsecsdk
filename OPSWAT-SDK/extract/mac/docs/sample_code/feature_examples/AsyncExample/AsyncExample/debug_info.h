#pragma once
#include <iostream>

// turn on this flag to enable debug output
constexpr bool k_debug = false;

namespace Debug 
{
	void print_debug_info()
	{
		if (k_debug)
		{
			std::wcout << L"Debug mode is enabled!" << std::endl;
			return;
		}
		
		std::wcout << L"Debug mode is disabled." << std::endl
			<< L"To enable debug output, change k_debug to true in debug_info.h" << std::endl;
	}

	void print_to_console(const std::wstring& str) 
	{
		if (k_debug)
			std::wcout << str << std::endl;
	}

	void pause_if_debug()
	{
		if (k_debug)
		{
			std::wcout << L"Press Enter to continue..." << std::endl;
			std::cin.get();
		}
	}
}
