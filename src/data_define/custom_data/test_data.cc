#include "test_data.h"

#include "dict_format/dict_format.h"

namespace parser {

/**
 * @brief 函数模板，解析 TestData
 * @param [in]  input    待解析字符串
 * @param [out] output   解析出的内容
 * @return 是否转换成功
 * @retval  0   成功
 * @retval -1   失败
 **/
template <>
int parse<TestData>(const std::string& input, std::shared_ptr<BaseType>& output) {
    return TestData::parse(input, output);
}

REGISTER_DATA_AND_ARRAY(test_data, TestData);

}  // namespace parser
