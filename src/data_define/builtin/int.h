/**
 * @file    int.h
 * @author  wenshishi
 * @brief   built-in Int 类型
 **/

#pragma once

#include "base_type.h"

namespace parser {

class Int : public BaseType {
public:
    int value;

    virtual const std::string to_string() const override { return std::to_string(value); }

    virtual ~Int() {}
};

}  // namespace parser
