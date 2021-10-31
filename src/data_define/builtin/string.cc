#include "string.h"

#include "dict_format/dict_format.h"

namespace parser {

/**
 * @brief 函数模板，解析字符串
 * @param [in]  input    待解析字符串
 * @param [out] output   解析出的内容
 * @return 是否转换成功
 * @retval  0   成功
 * @retval -1   失败
 **/
template <>
int parse<String>(const std::string& input, std::shared_ptr<BaseType>& output) {
    // 建立指向实际类型的指针
    std::shared_ptr<String> data = std::make_shared<String>();

    // 组装数据
    data->value = input;

    // 更新实际指针
    output = data;

    return SUCCESS;
}

REGISTER_DATA_AND_ARRAY(string, String);

}  // namespace parser
