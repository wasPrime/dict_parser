#include <glog/logging.h>
#include <gtest/gtest.h>

#include "utils/log_setting.h"

class GlobalEnvironment : public testing::Environment {
protected:
    void SetUp() override {
        // 初始化测试日志
        if (log_setting.init("parser_test", "test_log") != parser::SUCCESS) {
            LOG(ERROR) << "failed to init log setting in GlobalEnvironment SetUp";
        }
    }

    void TearDown() override {}

private:
    parser::LogSetting log_setting;
};

int main(int argc, char** argv) {
    testing::AddGlobalTestEnvironment(new GlobalEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
