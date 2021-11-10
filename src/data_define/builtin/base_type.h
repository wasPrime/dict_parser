#pragma once

#include <string>

namespace parser {

/**
 * @brief   词表数据类型基类，词表数据类型均须继承于此
 * @remarks 子类数据字段须命名为 value
 **/
class BaseType {
public:
    virtual std::string to_string() const = 0;

    virtual ~BaseType() = default;
};

}  // namespace parser
