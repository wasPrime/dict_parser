#pragma once

#include "base_type.h"

namespace parser {

class String : public BaseType {
public:
    std::string value;

    virtual const std::string to_string() const override { return value; }

    virtual ~String() {}
};

}  // namespace parser
