#ifndef DENGINE_LOGMANAGER_H
#define DENGINE_LOGMANAGER_H
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Log.h"

namespace DEngine {
    class LogManager {
    public:
        static void shutdown();
        static void init();
        static std::shared_ptr<spdlog::logger> DEngineLogger;
        static std::shared_ptr<spdlog::logger> getLogger(){return DEngineLogger;};
    };
}
#endif