/**
 * @file    dict_format.h
 * @author  wenshishi
 * @brief   数据转换
 **/

#pragma once

#include <sstream>

#include "data_define/builtin/base_type.h"
#include "data_define/builtin/string.h"
#include "data_define/custom_data/test_data.h"
#include "register/dict_register.h"

namespace parser {

/**
 * @brief 注册指定格式
 * @param [in] DATA_TYPE    数据类型名
 * @param [in] FUNC         解析函数
 **/
#define REGISTER_DATA_FORMAT(DATA_TYPE, FUNC) \
    DictRegister register_##DATA_TYPE(        \
        #DATA_TYPE, std::bind(FUNC, std::placeholders::_1, std::placeholders::_2))

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
 * @brief 函数模板，解析单值字符串(模板类型为字符串)
 * @param [in]  input    待解析字符串
 * @param [out] output   解析出的内容
 * @return 是否转换成功
 * @retval  0   成功
 * @retval -1   失败
 **/
template <>
int parse<String>(const std::string& input, std::shared_ptr<BaseType>& output);

template <>
int parse<TestData>(const std::string& input, std::shared_ptr<BaseType>& output);

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
