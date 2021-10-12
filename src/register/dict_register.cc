/**
 * @file    dict_register.cc
 * @author  wenshishi
 * @brief   数据转换方式注册器
 **/

#include "dict_register.h"

namespace parser {

DictMetaRegistry::DictMetaRegistry() {}
DictMetaRegistry::~DictMetaRegistry() {}

void DictMetaRegistry::register_parse_func(const std::string& data_type,
                                           const DictParseFunc& dict_parse_func) {
    _parse_map.emplace(data_type, dict_parse_func);
}

const DictParseFunc* DictMetaRegistry::find_parse_func(const std::string& data_type) const {
    auto iter = _parse_map.find(data_type);
    return iter != _parse_map.end() ? &(iter->second) : nullptr;
}

}  // namespace parser
