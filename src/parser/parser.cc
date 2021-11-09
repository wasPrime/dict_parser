#include "parser.h"

namespace parser {

Parser Parser::_s_instance;

Parser::Parser() {}
Parser::~Parser() {}

int Parser::init(const std::string& format_conf_path, const std::string& format_conf_name) {
    // 读取配置文件
    YAML::Node conf;
    try {
        conf = YAML::LoadFile(format_conf_path + "/" + format_conf_name);
    } catch (const YAML::BadFile& bad_file_exception) {
        LOG(ERROR) << "failed to load conf, catch BadFile[" << bad_file_exception.what() << "]";
        return FAILURE;
    }

    // 解析 columns
    YAML::Node columns = conf["columns"];
    if (!columns.IsSequence()) {
        LOG(ERROR) << "columns is not a sequence in format conf, node type["
                   << yaml_node_type2string(columns.Type()) << "]";
        return FAILURE;
    }

    std::unordered_set<std::string> name_dup;
    for (YAML::const_iterator column = columns.begin(); column != columns.end(); ++column) {
        // column 须为 Map，至少包含 key name 和 type
        if (!column->IsMap()) {
            LOG(ERROR) << "the column node is not a map in format conf, node type["
                       << yaml_node_type2string(column->Type()) << "]";
            return FAILURE;
        }

        // 解析 name
        std::string name;
        int ret = get_conf_value(*column, "name", name);
        if (ret != SUCCESS) {
            LOG(ERROR) << "failed to get name value";
            return FAILURE;
        }
        // 校验 name 非空
        if (name.empty()) {
            LOG(ERROR) << "empty name is invalid";
            return FAILURE;
        }
        // name 去重
        if (name_dup.find(name) != name_dup.end()) {
            LOG(ERROR) << "name[" << name << "] is repeated";
            return FAILURE;
        }
        name_dup.insert(name);

        // 解析 type
        std::string type;
        ret = get_conf_value(*column, "type", type);
        if (ret != SUCCESS) {
            LOG(ERROR) << "failed to get type value";
            return FAILURE;
        }
        // 校验 type 非空
        if (type.empty()) {
            LOG(ERROR) << "empty type is invalid";
            return FAILURE;
        }

        // 查询解析函数
        const DictParseFunc* parse_func = DictMetaRegistry::get_instance().find_parse_func(type);
        if (parse_func == nullptr) {
            LOG(ERROR) << "load format: data type[" << type << "] is not registered";
            return FAILURE;
        }

        _col_meta_vec.emplace_back(ColMeta(name, type, parse_func));
    }

    _cur_line = 0U;

    return SUCCESS;
}

int Parser::process_dict(const std::string& dict_path, const std::string& dict_name) {
    int ret = open_dict(dict_path, dict_name);
    if (ret != SUCCESS) {
        LOG(ERROR) << "failed to open dict data";
        return FAILURE;
    }

    while (read_line() == SUCCESS) {
        ret = process_line();
        // 本行解析有问题，跳过本行继续
        if (ret != SUCCESS) {
            LOG(WARNING) << "failed to process line[" << _cur_line << "]";
            continue;
        }
    }

    return SUCCESS;
}

int Parser::get_conf_value(const YAML::Node& original_node, const std::string& key,
                           std::string& value) {
    const YAML::Node value_node = original_node[key];
    // value_node 须为叶子 YAML 结点
    if (!value_node.IsScalar()) {
        LOG(ERROR) << "value node is not scalar when key[" << key << "]";
        return FAILURE;
    }

    // Scalar() 直接取字面字符串值
    value = value_node.Scalar();

    return SUCCESS;
}

int Parser::open_dict(const std::string& dict_path, const std::string& dict_name) {
    std::string dict_file_name = dict_path + "/" + dict_name;
    _fin.open(dict_file_name, std::ios::in);
    if (!_fin) {
        LOG(ERROR) << "failed to open dict file[" << dict_file_name << "]";
        return FAILURE;
    }
    _cur_line = 0U;

    return SUCCESS;
}

int Parser::read_line(const std::string& delimiter) {
    if (!_fin) {
        LOG(ERROR) << "the file doesn't open";
        return FAILURE;
    }
    if (_fin.eof()) {
        LOG(WARNING) << "fin EOF";
        return FAILURE;
    }

    std::string line;
    std::getline(_fin, line);
    // 将当前行分割成列
    boost::split(_dict_contents, line, boost::is_any_of(delimiter));

    return SUCCESS;
}

int Parser::process_line() {
    ++_cur_line;

    size_t dict_content_size = _dict_contents.size();  // 数据列数
    size_t col_meta_size = _col_meta_vec.size();       // 词表格式列数
    if (dict_content_size != col_meta_size) {
        LOG(ERROR) << "in line[" << _cur_line << "], input data col size[" << dict_content_size
                   << "] doesn't match col meta size[" << col_meta_size << "]";
        return FAILURE;
    }

    std::string print_log;
    std::vector<std::string> log_factor_vec;  // 每列的格式化输出内容
    log_factor_vec.reserve(dict_content_size);
    for (size_t i = 0; i < dict_content_size; ++i) {
        std::shared_ptr<BaseType> value;
        int parse_ret = (*_col_meta_vec[i].parse_func)(_dict_contents[i], value);
        if (parse_ret != SUCCESS) {
            LOG(ERROR) << "in line[" << _cur_line << "], failed to parse string["
                       << _dict_contents[i] << "]";
            return FAILURE;
        }
        log_factor_vec.emplace_back(_col_meta_vec[i].name + ":" + value->to_string());
    }

    LOG(INFO) << "line[" << _cur_line << "]" << boost::join(log_factor_vec, ", ");

    return SUCCESS;
}

const std::string Parser::yaml_node_type2string(YAML::NodeType::value type) const {
    static std::unordered_map<YAML::NodeType::value, std::string> yaml_node_type_map{
        {YAML::NodeType::Undefined, "Undefined"},
        {YAML::NodeType::Null, "Null"},
        {YAML::NodeType::Scalar, "Scalar"},
        {YAML::NodeType::Sequence, "Sequence"},
        {YAML::NodeType::Map, "Map"},
    };
    auto iter = yaml_node_type_map.find(type);
    return iter != yaml_node_type_map.end() ? iter->second : "Unknown";
}

}  // namespace parser
