# Dict Parser

A dict parser that supports basic data types, custom data types, and arrays.

## 任务描述

在我们的开发任务中，最常见的一项工作就是解析并读取各种词表文件，请设计并实现一个通用的词表解析读取工具类(一个或者几个class/struct组成)，解析并读取如下形式的词表：

> \<col1\>\t\<col2\>\t...\t\<coln\>

每一行都是一条记录，每一列可能的类型包括：

- int
- float
- char *
- 其他用户自定义类型(需要灵活支持多种自定义类型)
- 形如 `num:item1,item2,item3` 的数组（可以理解为 `T[num]` 的数组，`T` 是用户给出某种 build-in 类型）
每一列的数据中均不包含 `\t` 字符，每一行以 `\n` 结尾。

要求:

1. 对于非用户自定义类型，封装解析行为；用户自定义类型，调用用户给出的 `parse` 函数（从 string 翻译成用户 struct）完成；
    > 提示，要将 string 翻译为内部类型或用户自定义类型，而不是简单的字符串切分。
2. 用户能通过某些形式，定制这个词表的结构，指明每一列的类型是什么；
3. 用户能逐行读取这个词表的信息，即按序读取每一行，然后能解析出这一行中的每一列内容；
4. 容错采用出错则报警并跳过整行记录的方式，但不论输入任何错误数据，程序不能出 core；
5. API 设计友好，做到自解释；
6. 代码严格遵守百度编码规范；
7. 代码的可读性和可维护性好；
8. 实现需要采用 Cmake 工具链并确保可编译通过，输出包括可执行的 demo 程序，以及对应的单测程序，单测有效而且通过。
   > 提示，demo 也要符合编码规范；
   > 单元测试必须使用 `gtest`。

## Quick Start

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# run
./bin/parser

# run unit tests
./test/parser_test
```

解析内容在 `build/log/` 中。若成功解析，解析输出结果在 INFO log 文件中。

## DIY

### 配置

1. 在 `src/data_define/custom_data` 下新建文件，如 `demo_data.h`；
2. 实现自定义数据类型，注意须继承于 `BaseType`（位于 `src/data_define/builtin/base_type.h`），意味着至少需要实现 `to_string()` 方法，建议 `parse` 方法设为类静态方法 。示例如下：

    ```C++
    class DemoData : public BaseType {
    public:
        // Define data in here

        // 自定义数据类型解析函数
        static int parse(const std::string& input, std::shared_ptr<BaseType>& output) {
            // pass
            return 0
        }

        virtual const std::string to_string() const override {
            // pass
        }
    };
    ```

3. 注册数据类型：

    ```C++
    // src/dict_format/dict_format.h
    #include "data_define/custom_data/demo_data.h"

    // 声明 DemoData 的 parse 特化模版
    template <>
    int parse<DemoData>(const std::string& input, std::shared_ptr<BaseType>& output);
    ```

    ```C++
    // src/dict_format/dict_format.cc
    // 注册解析方法
    REGISTER_DATA_FORMAT(DemoData, DemoData::parse);
    // parse_array 可直接调用 DemoData 的 parse 特化模版
    REGISTER_DATA_FORMAT(DemoData_array, parse_array<DemoData>);

    // 借用 DemoData::parse 实现 parse 特化模版
    template <>
    int parse<DemoData>(const std::string& input, std::shared_ptr<BaseType>& output) {
        return DemoData::parse(input, output);
    }
    ```

### 使用

1. 在 `conf/format.yml` 中可设定 `DemeData` 数据类型，如：

    ```YAML
    columns:

    # pass

    - name: demo_data_column
      type: DemoData

    - name: demo_data_array_column
      type: DemoData_array
    ```

2. 在 `conf/dict_data.txt` 中相应列输入符合 `DemoData` 规定的字符串格式。

### 单元测试

在 `test/data_define_test.cc` 和 `test/dict_format_test.cc` 内加入 `DemoData` 的相关单元测试。

## 讨论

联系 <1135677507@qq.com>
