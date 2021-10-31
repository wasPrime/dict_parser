#pragma once

#include <string>

#include "utils.h"

namespace parser {

class LogSetting {
public:
    LogSetting();
    ~LogSetting();
    int init(const char* process_name, const std::string& log_dir);
};

}  // namespace parser
