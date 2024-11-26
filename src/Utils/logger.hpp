#ifndef LOGGER_HPP
#define LOGGER_HPP

#if defined(DEBUG) || defined(NDEBUG)

#include <cstdarg>
#include <map>
#include <iostream>

enum class LogLevel : unsigned char
{
	Verbose = 0,
	Info = 1,
	Warning = 2,
	Error = 3,
	Success = 4
};

struct LogMsgPair
{
	const char* lvlMsg;
	const char* lvl_clr;
};

static std::map<LogLevel, LogMsgPair> Log2Str =
{
	{LogLevel::Verbose, {"VERBOSE", "\033[37m"}},
	{LogLevel::Info,	{"INFO", "\033[96m"}},
	{LogLevel::Warning, {"WARNING", "\033[93m"}},
	{LogLevel::Error,	{"ERROR", "\033[97m\033[41m"}},
	{LogLevel::Success, {"SUCCESS", "\033[97m\033[42m"}}
};

inline void log(LogLevel lvl, const char* format, ...)
{
	const LogMsgPair& msgPair = Log2Str[lvl];
	
	std::cout << msgPair.lvl_clr << "[" << msgPair.lvlMsg << "] - ";

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	std::cout << "\033[0m\n";
}

#define LOG_VERBOSE(format, ...)		log(LogLevel::Verbose, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)			log(LogLevel::Info, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...)		log(LogLevel::Warning, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)			log(LogLevel::Error, format, ##__VA_ARGS__)
#define LOG_SUCCESS(format, ...)		log(LogLevel::Success, format, ##__VA_ARGS__)

#else

#define LOG_VERBOSE(format, ...)
#define LOG_INFO(format, ...)
#define LOG_WARNING(format, ...)		
#define LOG_ERROR(format, ...)			
#define LOG_SUCCESS(format, ...)

#endif

#endif // !LOGGER_HPP
