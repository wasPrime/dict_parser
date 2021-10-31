#include <gflags/gflags.h>

#include <vector>

#include "dict_format/dict_format.h"
#include "parser/parser.h"
#include "utils/log_setting.h"

DEFINE_string(conf_path, "conf", "conf path");
DEFINE_string(format_conf, "format.yml", "format conf file");

DEFINE_string(data_path, "conf", "data path");
DEFINE_string(dict_data, "dict_data.txt", "dict data file");

using namespace parser;

int main_impl();

int main(int argc, char** argv) {
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);

    // 初始化日志
    LogSetting log_setting;
    if (log_setting.init(argv[0], "log") != SUCCESS) {
        LOG(ERROR) << "log setting init failed";
        return -1;
    }

    return main_impl();
}

int main_impl() {
    Parser& parser_instance = Parser::get_instance();

    int ret = parser_instance.init(FLAGS_conf_path, FLAGS_format_conf);
    if (ret != SUCCESS) {
        LOG(ERROR) << "failed to init format conf, path: " << FLAGS_conf_path
                   << ", file_name: " << FLAGS_format_conf;
        return FAILURE;
    }

    ret = parser_instance.process_dict(FLAGS_data_path, FLAGS_dict_data);
    if (ret != SUCCESS) {
        LOG(ERROR) << "failed to process dict, path: " << FLAGS_data_path
                   << ", file_name: " << FLAGS_dict_data;
        return FAILURE;
    }

    return SUCCESS;
}
