/**
 * @file    array.h
 * @author  wenshishi
 * @brief   built-in Array 类型
 **/

#pragma once

#include <sstream>
#include <vector>

#include "base_type.h"

namespace parser {

// 当且仅当 T 继承于 BaseType 才可实例化
template <typename T, typename = typename std::enable_if<std::is_base_of<BaseType, T>::value>::type>
class Array : public BaseType {
public:
    std::vector<T> value;

    virtual const std::string to_string() const override {
        std::stringstream ss;

        ss << "[";

        auto begin = value.begin();
        auto end = value.end();
        if (begin != end) {
            auto elem = begin;
            ss << elem->to_string();
            ++elem;
            for (; elem != end; ++elem) {
                ss << ",";
                ss << elem->to_string();
            }
        }

        ss << "]";

        return ss.str();
    }

    virtual ~Array() {}
};

}  // namespace parser
