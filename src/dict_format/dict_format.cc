/**
 * @file    dict_format.cc
 * @author  wenshishi
 * @brief   数据转换
 **/

#include "dict_format.h"

#include "data_define/builtin/array.h"
#include "data_define/builtin/float.h"
#include "data_define/builtin/int.h"
#include "data_define/builtin/string.h"
#include "data_define/builtin/uint32.h"
#include "data_define/builtin/uint64.h"

namespace parser {

/********************** 注册词表格式 **********************/
/*********************** built-in ***********************/
// 注册单值
REGISTER_DATA_FORMAT(int, parse<Int>);
REGISTER_DATA_FORMAT(uint32, parse<Uint32>);
REGISTER_DATA_FORMAT(uint64, parse<Uint64>);
REGISTER_DATA_FORMAT(float, parse<Float>);
REGISTER_DATA_FORMAT(string, parse<String>);
// 注册数组
REGISTER_DATA_FORMAT(int_array, parse_array<Int>);
REGISTER_DATA_FORMAT(uint32_array, parse_array<Uint32>);
REGISTER_DATA_FORMAT(uint64_array, parse_array<Uint64>);
REGISTER_DATA_FORMAT(float_array, parse_array<Float>);
REGISTER_DATA_FORMAT(string_array, parse_array<String>);
/*********************** built-in ***********************/

/********************* custom data *********************/
// 注册单值
REGISTER_DATA_FORMAT(TestData, parse<TestData>);
// 注册数组
REGISTER_DATA_FORMAT(TestData_array, parse_array<TestData>);
/********************* custom data *********************/
/********************** 注册词表格式 **********************/

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

template <>
int parse<TestData>(const std::string& input, std::shared_ptr<BaseType>& output) {
    return TestData::parse(input, output);
}

template <typename T>
typename std::enable_if<std::is_base_of<BaseType, T>::value, int>::type parse_array(
    const std::string& input, std::shared_ptr<BaseType>& output) {
    std::vector<std::string> vec = Utils::string_split(input, ARRAY_DELIMITER);
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
    Uint64* array_size_uint64 = dynamic_cast<Uint64*>(array_size.get());
    if (array_size_uint64 == nullptr) {
        LOG(ERROR) << "dynamic_cast transfer BaseType* to Uint64* failed";
        return FAILURE;
    }
    if (array_size_uint64->value <= 0) {
        LOG(ERROR) << "invalid array size[" << array_size_uint64->value << "]";
        return FAILURE;
    }

    // 校验给出数组长度与实际长度是否一致
    std::vector<std::string> array_element = Utils::string_split(vec[1], ARRAY_DATA_DELIMITER);
    if (array_element.size() != array_size_uint64->value) {
        LOG(ERROR) << "array data's size[" << array_element.size()
                   << "] doesn't match array_size given[" << array_size_uint64->value << "]";
        return FAILURE;
    }

    // 建立指向实际数组类型的指针
    std::shared_ptr<Array<T>> data = std::make_shared<Array<T>>();
    // 解析每个数组元素
    for (uint64_t i = 0; i < array_size_uint64->value; ++i) {
        std::shared_ptr<BaseType> value = nullptr;
        if (parse<T>(array_element[i], value) != SUCCESS) {
            LOG(ERROR) << "failed to parse array element[" << array_element[i] << "]";
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
