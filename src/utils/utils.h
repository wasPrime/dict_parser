#pragma once

#include <sstream>
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
    ~TypeName();

/**
 * @brief 工具类
 **/
class Utils {
public:
    /**
     * @brief 字符串分割
     * @param [in] str         原字符串
     * @param [in] delimiter   分割符
     * @return 分割后的字符串数组
     **/
    static const std::vector<std::string> string_split(const std::string& str,
                                                       const std::string& delimiter);

    /**
     * @brief 字符串连接
     * @param [in] begin        范围首位置
     * @param [in] end          范围末位置
     * @param [in] connector    连接符
     * @return 连接后的字符串
     **/
    template <typename Iter>
    static const std::string string_join(const Iter begin, const Iter end,
                                         const std::string& connector);

private:
    DISABLE_CONSTRUCTOR_AND_DESTRUCTOR(Utils)
};

}  // namespace parser

#include "utils.hpp"
