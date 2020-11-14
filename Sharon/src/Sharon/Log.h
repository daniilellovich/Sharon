#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Sharon
{
	class SHARON_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define SHARON_CORE_TRACE(...)    ::Sharon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SHARON_CORE_INFO(...)     ::Sharon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SHARON_CORE_WARN(...)     ::Sharon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SHARON_CORE_ERROR(...)    ::Sharon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SHARON_CORE_FATAL(...)    ::Sharon::Log::GetCoreLogger()->fatal(__VA_ARGS__)
									 
// Client log macros				
#define SHARON_TRACE(...)	      ::Sharon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SHARON_INFO(...)	      ::Sharon::Log::GetClientLogger()->info(__VA_ARGS__)
#define SHARON_WARN(...)	      ::Sharon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SHARON_ERROR(...)	      ::Sharon::Log::GetClientLogger()->error(__VA_ARGS__)
#define SHARON_FATAL(...)	      ::Sharon::Log::GetClientLogger()->fatal(__VA_ARGS__)