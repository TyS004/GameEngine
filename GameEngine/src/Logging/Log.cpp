#include "gepch.h"

#include "Log.h"

HANDLE Log::m_ConsoleHandle;
std::tm Log::m_timeNow;

void Log::Init()
{
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE Log::getConsoleHandle()
{
	return Log::m_ConsoleHandle;
}

void Log::info(const std::string& message, HANDLE handle)
{
	updateTimeNow();

	SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::LIGHTBLUE));
	std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
}

void Log::warn(const std::string& message, HANDLE handle)
{
	updateTimeNow();

	SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::LIGHTRED));
	std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
}

void Log::fatal(const std::string& message, HANDLE handle)
{
	updateTimeNow();

	SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::RED));
	std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
}

void Log::trace(const std::string& message, HANDLE handle)
{
	updateTimeNow();

	SetConsoleTextAttribute(handle, static_cast<WORD>(ConsoleColor::GREEN));
	std::cout << std::put_time(&m_timeNow, "%H:%M:%S") << " GameEngine: " << message << std::endl;
}

void Log::updateTimeNow() {
	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	localtime_s(&m_timeNow, &t);
}