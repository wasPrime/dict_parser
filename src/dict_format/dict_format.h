#pragma once

#include <glog/logging.h>

#include "data_define/builtin/array.h"
#include "data_define/builtin/base_type.h"
#include "data_define/builtin/uint64.h"
#include "register/dict_register.h"

namespace parser {

/**
 * @brief 注册指定数据类型的解析函数
 * @param [in] DATA_TYPE    数据类型名
 * @param [in] PARSE_FUNC   解析函数
 **/
#define REGISTER_DATA_FORMAT(DATA_TYPE, PARSE_FUNC) \
    DictRegister register_##DATA_TYPE(              \
        #DATA_TYPE, std::bind(PARSE_FUNC, std::placeholders::_1, std::placeholders::_2))

/**
 * @brief 注册指定数据类型及其数组的解析函数
 * @param [in] TYPE_NAME    逻辑数据类型名
 * @param [in] DATA_TYPE    实际数据类型
 * @remarks 推荐使用此宏而非两句 REGISTER_DATA_FORMAT
 **/
#define REGISTER_DATA_AND_ARRAY(TYPE_NAME, DATA_TYPE)  \
    REGISTER_DATA_FORMAT(TYPE_NAME, parse<DATA_TYPE>); \
    REGISTER_DATA_FORMAT(TYPE_NAME##_array, parse_array<DATA_TYPE>)

/**
 * @brief 函数模板，解析单值
 * @param [in]  input    待解析字符串
 * @param [out] output   解析出的内容
 * @return 是否转换成功
 * @retval 0    成功
 * @retval -1   失败
 **/
template <typename T>
typename std::enable_if<std::is_base_of<BaseType, T>::value, int>::type parse(
    const std::string& input, std::shared_ptr<BaseType>& output);

/**
 * @brief 函数模板，解析数组
 * @param [in]  input    待解析字符串
 * @param [out] output   解析出的内容
 * @return 是否转换成功
 * @retval  0   成功
 * @retval -1   失败
 **/
template <typename T>
typename std::enable_if<std::is_base_of<BaseType, T>::value, int>::type parse_array(
    const std::string& input, std::shared_ptr<BaseType>& output);

}  // namespace parser

#include "dict_format.hpp"
