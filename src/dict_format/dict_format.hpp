#pragma once

#include <glog/logging.h>

#include <sstream>

#include "data_define/builtin/array.h"
#include "data_define/builtin/base_type.h"
#include "data_define/builtin/uint64.h"
#include "register/dict_register.h"
#include "system/system_boost.h"
#include "utils/utils.h"

namespace parser {

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
    const std::string& input, std::shared_ptr<BaseType>& output) {
    // 建立指向实际类型的指针
    std::shared_ptr<T> data = std::make_shared<T>();

    // 组装数据
    std::stringstream ss(input);
    if (!(ss >> data->value)) {
        LOG(ERROR) << "input string is invalid while parsing";
        return FAILURE;
    }

    // 检查是否有残余字符
    std::string str;
    if (ss >> str) {
        LOG(ERROR) << "leave unused characters[" << str << "] after parsing";
        return FAILURE;
    }

    // 更新实际指针
    output = data;

    return SUCCESS;
}

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
    const std::string& input, std::shared_ptr<BaseType>& output) {
    std::vector<std::string> vec;
    boost::split(vec, input, boost::is_any_of(ARRAY_DELIMITER));
    if (vec.size() != 2) {
        LOG(ERROR) << "failed to parse string[" << input << "] which doesn't match array pattern";
        return FAILURE;
    }

    // 解析数组长度
    std::shared_ptr<BaseType> array_size = nullptr;
    if (parse<Uint64>(vec[0], array_size) != SUCCESS) {
        LOG(ERROR) << "failed to parse string[" << vec[0] << "] as an array size";
        return FAILURE;
    }
    auto* array_size_uint64 = dynamic_cast<Uint64*>(array_size.get());
    if (array_size_uint64 == nullptr) {
        LOG(ERROR) << "dynamic_cast transfer BaseType* to Uint64* failed";
        return FAILURE;
    }
    if (array_size_uint64->value <= 0) {
        LOG(ERROR) << "invalid array size[" << array_size_uint64->value << "]";
        return FAILURE;
    }

    // 校验给出数组长度与实际长度是否一致
    std::vector<std::string> array_element_vec;
    boost::split(array_element_vec, vec[1], boost::is_any_of(ARRAY_DATA_DELIMITER));
    if (array_element_vec.size() != array_size_uint64->value) {
        LOG(ERROR) << "array data's size[" << array_element_vec.size()
                   << "] doesn't match array_size given[" << array_size_uint64->value << "]";
        return FAILURE;
    }

    // 建立指向实际数组类型的指针
    std::shared_ptr<Array<T>> data = std::make_shared<Array<T>>();
    // 解析每个数组元素
    for (uint64_t i = 0; i < array_size_uint64->value; ++i) {
        std::shared_ptr<BaseType> value = nullptr;
        if (parse<T>(array_element_vec[i], value) != SUCCESS) {
            LOG(ERROR) << "failed to parse array element[" << array_element_vec[i] << "]";
            return FAILURE;
        }
        T* real_value = dynamic_cast<T*>(value.get());
        if (real_value == nullptr) {
            LOG(ERROR) << "dynamic_cast transfer BaseType* to T* failed";
            return FAILURE;
        }

        data->value.emplace_back(*real_value);
    }

    // 更新实际指针
    output = data;

    return SUCCESS;
}

}  // namespace parser
