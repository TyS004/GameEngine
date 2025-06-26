#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>

class Log
{
public:
    static void Init();
    static HANDLE getConsoleHandle();

    static void info(const std::string& message, HANDLE handle);
	static void warn(const std::string& message, HANDLE handle);
	static void fatal(const std::string& message, HANDLE handle);
	static void trace(const std::string& message, HANDLE handle);

    static void updateTimeNow();

private:
    static HANDLE m_ConsoleHandle;
    static std::tm m_timeNow;
};

enum class ConsoleColor
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTPURPLE = 13,
    LIGHTYELLOW = 14,
    WHITE = 15
};

#define INFO(x)  Log::info(x, Log::getConsoleHandle())
#define WARN(x)  Log::warn(x, Log::getConsoleHandle())
#define FATAL(x) Log::fatal(x, Log::getConsoleHandle())
#define TRACE(x) Log::trace(x, Log::getConsoleHandle())