#ifndef DENGINE_LOG_H
#define DENGINE_LOG_H
#include "spdlog/spdlog.h"
#define DENGINE_DEFUALT_LOGGER_NAME "DEngineLogger"
#define DENGINE_TRACE(...) DEngine::LogManager::getLogger()->trace(__VA_ARGS__)
#define DENGINE_INFO(...) DEngine::LogManager::getLogger()->info(__VA_ARGS__)
#define DENGINE_WARN(...) DEngine::LogManager::getLogger()->warn(__VA_ARGS__)
#define DENGINE_ERROR(...) DEngine::LogManager::getLogger()->error(__VA_ARGS__)
#endif