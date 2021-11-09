#pragma once

#include <glog/logging.h>

#include <exception>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "register/dict_register.h"
#include "system/system_boost.h"
#include "system/system_yaml.h"

namespace parser {

/**
 * @brief 词表转换器
 **/
class Parser {
public:
    /**
     * @brief 词表每列格式
     **/
    struct ColMeta {
        ColMeta(std::string col_name, std::string col_type, const DictParseFunc* col_parse_func)
            : name(col_name), type(col_type), parse_func(col_parse_func) {}

        std::string name;                 // 列名
        std::string type;                 // 列数据类型
        const DictParseFunc* parse_func;  // 列数据解析函数
    };

    /**
     * @brief  获取单例
     * @return Parser 单例
     **/
    static Parser& get_instance() { return _s_instance; }

    /**
     * @brief 初始化词表格式
     * @param [in] conf_path   词表格式配置文件所在文件夹路径
     * @param [in] conf_name   词表格式配置文件名
     * @return 是否初始化成功
     * @retval  0   成功
     * @retval -1   失败
     **/
    int init(const std::string& conf_path, const std::string& conf_name);

    int process_dict(const std::string& dict_path, const std::string& dict_name);

private:
    /**
     * @brief 解析词表每一行相应 key 的 value
     * @param [in]  original_node   行 YAML 结点
     * @param [in]  key             词表文件名
     * @param [out] value           解析值
     * @return 是否解析成功
     * @retval  0   成功
     * @retval -1   失败
     **/
    int get_conf_value(const YAML::Node& original_node, const std::string& key, std::string& value);

    /**
     * @brief 打开词表文件
     * @param [in] dict_path   词表文件所在文件夹路径
     * @param [in] dict_name   词表文件名
     * @return 是否打开词表成功
     * @retval  0   成功
     * @retval -1   失败
     **/
    int open_dict(const std::string& dict_path, const std::string& dict_name);

    /**
     * @brief 读取一行数据
     * @param [in] delimiter 行内列间分隔符
     * @return 是否读取数据成功
     * @retval  0   成功
     * @retval -1   失败
     **/
    int read_line(const std::string& delimiter = COL_DELIMITER);

    /**
     * @brief  处理一行数据
     * @return 是否处理数据成功
     * @retval  0   成功
     * @retval -1   失败
     **/
    int process_line();

    /**
     * @brief  YAML node type 转为 string
     * @param [in] type YAML node type
     * @return 转换后的 string
     **/
    const std::string yaml_node_type2string(YAML::NodeType::value type) const;

private:
    static Parser _s_instance;  // Parser 单例

    std::vector<ColMeta> _col_meta_vec;       // 词表格式数组
    std::ifstream _fin;                       // 词表数据输入流
    uint32_t _cur_line;                       // 当前行数
    std::vector<std::string> _dict_contents;  // 词表当前行各列内容

    DISABLE_CONSTRUCTOR_AND_DESTRUCTOR(Parser);
};

}  // namespace parser
