#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core.h"
namespace EFS
{
	class log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		EFSAPI static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		EFSAPI static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		EFSAPI static void Init();
	};
}

//macros for core logging
#define EFS_Core_TRACE(...)		::EFS::log::GetCoreLogger()->trace(__VA_ARGS__)
#define EFS_Core_INFO(...)		::EFS::log::GetCoreLogger()->info(__VA_ARGS__)
#define EFS_Core_WARN(...)		::EFS::log::GetCoreLogger()->warn(__VA_ARGS__)
#define EFS_Core_ERROR(...)		::EFS::log::GetCoreLogger()->error(__VA_ARGS__)

//macros for client logging
#define EFS_TRACE(...)			::EFS::log::GetClientLogger()->trace(__VA_ARGS__)
#define EFS_INFO(...)			::EFS::log::GetClientLogger()->info(__VA_ARGS__)
#define EFS_WARN(...)			::EFS::log::GetClientLogger()->warn(__VA_ARGS__)
#define EFS_ERROR(...)			::EFS::log::GetClientLogger()->error(__VA_ARGS__)
