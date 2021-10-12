/**
 * @file    dict_register.h
 * @author  wenshishi
 * @brief   数据转换方式注册器
 **/

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "data_define/builtin/base_type.h"
#include "utils/utils.h"

namespace parser {

typedef std::function<int(const std::string&, std::shared_ptr<BaseType>&)> DictParseFunc;

/**
 * @brief 数据转换存储类
 **/
class DictMetaRegistry {
public:
    /**
     * @brief  获取单例
     * @return DictMetaRegistry 单例
     **/
    static DictMetaRegistry& get_instance() {
        static DictMetaRegistry _instance;
        return _instance;
    }

    /**
     * @brief 注册数据转换函数
     * @param [in] data_type        数据类型名
     * @param [in] dict_parse_func  数据转换函数
     * @return
     **/
    void register_parse_func(const std::string& data_type, const DictParseFunc& dict_parse_func);

    /**
     * @brief 获取数据转换函数
     * @param [in] data_type 数据类型名
     * @return 数据转换函数
     * @retval not nullptr  有效
     * @retval nullptr      无效
     **/
    const DictParseFunc* find_parse_func(const std::string& data_type) const;

private:
    typedef std::unordered_map<std::string, DictParseFunc> DictParseMap;
    /**
     * @brief 词表格式映射表
     **/
    DictParseMap _parse_map;

    DISABLE_CONSTRUCTOR_AND_DESTRUCTOR(DictMetaRegistry)
};

/**
 * @brief   数据转换注册类
 * @remarks 通过构造函数在数据转换存储类注册
 **/
class DictRegister {
public:
    DictRegister(const std::string& data_type, const DictParseFunc& func) {
        DictMetaRegistry::get_instance().register_parse_func(data_type, func);
    }
};

}  // namespace parser
