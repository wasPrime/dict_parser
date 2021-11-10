#pragma once

#include "base_type.h"

namespace parser {

class Int : public BaseType {
public:
    int value;

    std::string to_string() const override { return std::to_string(value); }

    ~Int() override = default;
};

}  // namespace parser
