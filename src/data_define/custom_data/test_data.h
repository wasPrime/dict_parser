#pragma once

#include <glog/logging.h>

#include <memory>
#include <string>

#include "data_define/builtin/base_type.h"
#include "system/system_boost.h"
#include "utils/utils.h"

namespace parser {

class TestData : public BaseType {
public:
    int v1;
    std::string v2;

    // 自定义类型解析函数
    static int parse(const std::string& input, std::shared_ptr<BaseType>& output) {
        std::shared_ptr<TestData> p_data = std::make_shared<TestData>();

        std::vector<std::string> vec;
        boost::split(vec, input, boost::is_any_of(DELIMITER));
        if (vec.size() != 2) {
            LOG(ERROR) << "for TestData, the input string[" << input
                       << "] doesn't match TestData pattern";
            return FAILURE;
        }

        try {
            // 对于 "abc123" 的情况会抛出异常
            p_data->v1 = std::stoi(vec[0]);
        } catch (const std::exception& e) {
            LOG(ERROR) << "for TestData, failed to convert string[" << vec[0] << "] to int";
            return FAILURE;
        }

        // 拦截 "123abc" 的情况
        if (std::to_string(p_data->v1) != vec[0]) {
            LOG(ERROR) << "for TestData, failed to convert string[" << vec[0] << "] to int";
            return FAILURE;
        }

        p_data->v2 = vec[1];

        output = p_data;

        return SUCCESS;
    }

    std::string to_string() const override {
        std::string ret = "(" + std::to_string(v1) + DELIMITER + v2 + ")";
        return ret;
    }

    ~TestData() override = default;

private:
    static const std::string DELIMITER;
};

}  // namespace parser
