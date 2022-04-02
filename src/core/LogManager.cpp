#include "LogManager.h"
namespace DEngine {
    std::shared_ptr<spdlog::logger> LogManager::DEngineLogger;

    void LogManager::init() {
        auto consoleSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
        consoleSink ->set_pattern("%^[%T] %n: %v%$");
        std::vector<spdlog::sink_ptr> sinks{consoleSink};
        DEngineLogger = std::make_shared<spdlog::logger>(DENGINE_DEFUALT_LOGGER_NAME, sinks.begin(), sinks.end());
        DEngineLogger->set_level(spdlog::level::trace);
    }
    void LogManager::shutdown() {

    }
}