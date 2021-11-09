#pragma once

#include <string>
#include <vector>

namespace parser {

// 返回码
const int SUCCESS = 0;
const int FAILURE = -1;

// 列分隔符
const std::string COL_DELIMITER = "\t";
// 数组分隔符
const std::string ARRAY_DELIMITER = ":";
// 数组元素分隔符
const std::string ARRAY_DATA_DELIMITER = ",";

/**
 * @brief 禁用构造函数和析构函数
 * @param [in] TypeName 类名/结构体名
 **/
#define DISABLE_CONSTRUCTOR_AND_DESTRUCTOR(TypeName) \
private:                                             \
    TypeName();                                      \
    TypeName(const TypeName&);                       \
    TypeName& operator=(const TypeName&);            \
    ~TypeName()

}  // namespace parser

#include "utils.hpp"
