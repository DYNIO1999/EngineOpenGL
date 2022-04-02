#ifndef DENGINE_LOGMANAGER_H
#define DENGINE_LOGMANAGER_H
#include <memory>
#include "spdlog/spdlog.h"
#include "Log.h"

namespace DEngine {
    class LogManager {
    public:
        //consoleSink->set_pattern("%^[%T] %n: %v%$");

        void shutdown();
        void init();
        static std::shared_ptr<spdlog::logger> DEngineLogger;
    };
}
#endif