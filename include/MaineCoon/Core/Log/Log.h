#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "MaineCoon/Core/Base.h"

namespace MaineCoon {
class Log {
public:
    static void Init();

    static Shared<spdlog::logger>& GetCoreLogger()
    {
        return s_CoreLogger;
    }
    static Shared<spdlog::logger>& GetClientLogger()
    {
        return s_ClientLogger;
    }

private:
    static Shared<spdlog::logger> s_CoreLogger;
    static Shared<spdlog::logger> s_ClientLogger;
};
}

// Core log macros
#define MC_CORE_TRACE(...) ::MaineCoon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MC_CORE_INFO(...) ::MaineCoon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MC_CORE_WARN(...) ::MaineCoon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MC_CORE_ERROR(...) ::MaineCoon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MC_CORE_CRITICAL(...) ::MaineCoon::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MC_TRACE(...) ::MaineCoon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MC_INFO(...) ::MaineCoon::Log::GetClientLogger()->info(__VA_ARGS__)
#define MC_WARN(...) ::MaineCoon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MC_ERROR(...) ::MaineCoon::Log::GetClientLogger()->error(__VA_ARGS__)
#define MC_CRITICAL(...) ::MaineCoon::Log::GetClientLogger()->critical(__VA_ARGS__)
