#include "log_setting.h"

#include <glog/logging.h>

namespace parser {

LogSetting ::LogSetting() {}

LogSetting ::~LogSetting() {
    // 当单元测试无测试用例时，不会触发 GlobalEnvironment 的 SetUp() 方法，导致
    // google::InitGoogleLogging 未执行。未执行 google::InitGoogleLogging 时触发
    // google::ShutdownGoogleLogging() 会出错。
    if (::google::IsGoogleLoggingInitialized()) {
        ::google::ShutdownGoogleLogging();
    }
}

int LogSetting::init(const char* process_name, const std::string& log_dir) const {
    FLAGS_log_dir = log_dir;
    // 确保 log 目录存在（glog 不会自动生成 log 目录）
    std::string make_log_dir_command("mkdir -p " + FLAGS_log_dir);
    int ret = system(make_log_dir_command.c_str());
    if (ret != 0) {
        LOG(ERROR) << "`" << make_log_dir_command << "` failed, ret=" << ret;
        return FAILURE;
    }

    // Initialize Google’s logging library.
    FLAGS_stderrthreshold = ::google::ERROR;
    FLAGS_colorlogtostderr = true;
    ::google::InitGoogleLogging(process_name);

    return SUCCESS;
}

}  // namespace parser
