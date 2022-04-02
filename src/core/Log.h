#ifndef DENGINE_LOG_H
#define DENGINE_LOG_H
#include "spdlog/spdlog.h"
#define DENGINE_DEFUALT_LOGGER_NAME "DEngineLogger"

#ifndef DENGINE_CONFIG_RELEASE
#define DENGINE_TRACE(...) if(spdlog::get(DENGINE_DEFUALT_LOGGER_NAME) != nullptr {spdlog::get(DENGINE_DEFUALT_LOGGER_NAME)->trace(__VA_ARGS__)})
#else
#define DENGINE_TRACE(...) (void)0
#endif
#endif