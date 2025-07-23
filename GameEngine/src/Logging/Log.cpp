#include "gepch.h"

#include "Log.h"

namespace GameEngine
{
    HANDLE Log::m_ConsoleHandle;
    std::tm Log::m_timeNow;

    void Log::Init()
    {
        Log::m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    HANDLE Log::getConsoleHandle()
    {
        return Log::m_ConsoleHandle;
    }

    void Log::updateTimeNow() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        localtime_s(&m_timeNow, &t);
    }
}
