#pragma once

#include "Core.h"

namespace GameEngine
{
    class GE_API Log
    {
    public:
        static void Init();
        static HANDLE getConsoleHandle();

        template <typename T>
        static void info(const T& message, HANDLE handle);

        template <typename T>
        static void warn(const T& message, HANDLE handle);

        template <typename T>
        static void fatal(const T& message, HANDLE handle);

        template <typename T>
        static void trace(const T& message, HANDLE handle);

        static void updateTimeNow();

    private:
        static HANDLE m_ConsoleHandle;
        static std::tm m_timeNow;
    };

    template <typename T>
    void Log::info(const T& message, HANDLE handle)
    {
        updateTimeNow();

        SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::LIGHTBLUE));
        std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
    }

    template <typename T>
    void Log::warn(const T& message, HANDLE handle)
    {
        updateTimeNow();

        SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::LIGHTRED));
        std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
    }


    template <typename T>
    void Log::trace(const T& message, HANDLE handle)
    {
        updateTimeNow();

        SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::GREEN));
        std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
    }

    template <typename T>
    void Log::fatal(const T& message, HANDLE handle)
    {
        updateTimeNow();

        SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::RED));
        std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
    }

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
}

#define INFO(x)  Log::info(x, Log::getConsoleHandle())
#define WARN(x)  Log::warn(x, Log::getConsoleHandle())
#define FATAL(x) Log::fatal(x, Log::getConsoleHandle())
#define TRACE(x) Log::trace(x, Log::getConsoleHandle())