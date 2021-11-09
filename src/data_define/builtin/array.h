#pragma once

#include <vector>

#include "base_type.h"
#include "system/system_boost.h"

namespace parser {

// 当且仅当 T 继承于 BaseType 才可实例化
template <typename T, typename = typename std::enable_if<std::is_base_of<BaseType, T>::value>::type>
class Array : public BaseType {
public:
    std::vector<T> value;

    virtual const std::string to_string() const override {
        std::vector<std::string> value_str_vec;
        value_str_vec.reserve(value.size());
        for (const T& value_element : value) {
            value_str_vec.emplace_back(value_element.to_string());
        }

        return "[" + boost::join(value_str_vec, ", ") + "]";
    }

    virtual ~Array() {}
};

}  // namespace parser
