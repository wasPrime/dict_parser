#pragma once

#include <glog/logging.h>

#include <memory>
#include <string>

#include "data_define/builtin/base_type.h"
#include "utils/utils.h"

namespace parser {

class TestData : public BaseType {
public:
    int v1;
    std::string v2;

    // 自定义类型解析函数
    static int parse(const std::string& input, std::shared_ptr<BaseType>& output) {
        std::shared_ptr<TestData> p_data = std::make_shared<TestData>();

        std::string tmp;
        std::istringstream iss(input);

        if (std::getline(iss, tmp, '|')) {
            if (sscanf(tmp.c_str(), "%d", &p_data->v1) != 1) {
                LOG(ERROR) << "fail to convert string to int, string[" << tmp << "]";
                return FAILURE;
            }
        }

        if (std::getline(iss, tmp, DELIMITER)) {
            p_data->v2 = tmp;
        }

        output = p_data;

        return SUCCESS;
    }

    std::string to_string() const override {
        std::string ret = "(" + std::to_string(v1) + DELIMITER + v2 + ")";
        return ret;
    }

    ~TestData() override = default;

private:
    static const char DELIMITER = '|';
};

}  // namespace parser
