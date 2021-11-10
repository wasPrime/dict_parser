#pragma once

#include "dict_format.hpp"

namespace parser {

/**
 * @brief 注册指定数据类型的解析函数
 * @param [in] DATA_TYPE    数据类型名
 * @param [in] PARSE_FUNC   解析函数
 **/
#define REGISTER_DATA_FORMAT(DATA_TYPE, PARSE_FUNC) \
    static DictRegister register_##DATA_TYPE(#DATA_TYPE, PARSE_FUNC)

/**
 * @brief 注册指定数据类型及其数组的解析函数
 * @param [in] TYPE_NAME    逻辑数据类型名
 * @param [in] DATA_TYPE    实际数据类型
 * @remarks 推荐使用此宏而非两句 REGISTER_DATA_FORMAT
 **/
#define REGISTER_DATA_AND_ARRAY(TYPE_NAME, DATA_TYPE)  \
    REGISTER_DATA_FORMAT(TYPE_NAME, parse<DATA_TYPE>); \
    REGISTER_DATA_FORMAT(TYPE_NAME##_array, parse_array<DATA_TYPE>)

}  // namespace parser
