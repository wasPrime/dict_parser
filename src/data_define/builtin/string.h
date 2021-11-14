#pragma once

#include "base_type.h"

namespace parser {

class String : public BaseType {
public:
    std::string value;

    [[nodiscard]] std::string to_string() const override { return value; }

    ~String() override = default;
};

}  // namespace parser
