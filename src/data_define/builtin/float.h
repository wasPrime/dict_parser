#pragma once

#include "base_type.h"

namespace parser {

class Float : public BaseType {
public:
    float value;

    virtual const std::string to_string() const override { return std::to_string(value); }

    virtual ~Float() {}
};

}  // namespace parser
