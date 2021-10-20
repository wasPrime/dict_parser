# Dict Parser

[![ci](https://github.com/wasPrime/dict_parser/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/wasPrime/dict_parser/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A dict parser that supports basic data types, custom data types, and arrays.

## Task Description

In our development tasks, the most common task is to read and parse various vocabulary files. Please design and implement a general vocabulary parsing and reading tool class (composed of one or several `class`/`struct`) to read and parse the vocabulary in the following form:

> \<col1\>\t\<col2\>\t...\t\<coln\>

Each row is a record, and the possible types of each column include:

- int
- float
- char *
- Other user-defined types (need to flexibly support multiple custom types)
- An array like `num:item1,item2,item3` (can be understood as an array of `T[num]`, `T` is a certain build-in type given by the user). The data in each column does not contain the `\t` character, and each line ends with `\n`.

Require:

1. For non-user-defined types, encapsulate the parsing behavior; for user-defined types, call the `parse` function (translated from string to user struct) given by the user to complete;
    > Prompt, to parse string into internal type or user-defined type, rather than simple string segmentation.
2. Through some forms, users can customize the structure of this vocabulary, indicating what the type of each column is;
3. Users can read the information of this vocabulary line by line, that is, read each line in sequence, and then parse the content of each column in this line;
4. When an error occurs, the fault tolerance adopts the method of alarming and skipping the entire line of records, but no matter what wrong data is input, the program cannot has core;
5. API design is friendly and self-explanatory;
6. The code strictly complies with C++ coding standards;
7. Good readability and maintainability of the code;
8. The implementation needs to use CMake tool chains and ensure that it can be compiled. The output includes the executable demo program and the corresponding single test program. The single test is valid and passed.
   > Prompt, the demo must also conform to the coding standards;
   > Unit tests must use `gtest`.

## Quick Start

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# run
./bin/parser

# run unit tests
./test/parser_test
```

The parsed content is in `build/log/`. If the analysis is successful, the output result is in the INFO log file; the exception log is in the WARNING/ERROR log files; the ERROR log will also be output in the terminal (`FLAGS_stderrthreshold = ::google` is set in `src/utils/log_setting.cc` ::ERROR;`).

## DIY

### Configure

1. Create a new file under `src/data_define/custom_data`, such as `demo_data.h`;
2. To implement a custom data type, note that it must be inherited from `BaseType` (located in `src/data_define/builtin/base_type.h`), which means that at least the `to_string()` method needs to be implemented. It is recommended that the `parse` method be set as a class static method . Examples are as follows:

    ```C++
    #include <memory>

    #include "data_define/builtin/base_type.h"
    #include "utils/utils.h"

    class DemoData : public BaseType {
    public:
        // Define datas in here

        // Custom data type analysis function
        static int parse(const std::string& input, std::shared_ptr<BaseType>& output) {
            std::shared_ptr<DemoData> p_data = std::make_shared<DemoData>();

            // fill p_data

            output = p_data;

            return SUCCESS;
        }

        virtual const std::string to_string() const override {
            // pass
        }
    };
    ```

3. Register data type:

    ```C++
    // src/custom_data/demo_data.cc
    #include "demo_data.h"
    #include "dict_format/dict_format.h"

    template <>
    int parse<DemoData>(const std::string& input, std::shared_ptr<BaseType>& output) {
        return DemoData::parse(input, output);
    }

    REGISTER_DATA_AND_ARRAY(demo_data, DemoData);
    ```

### Use

1. The data type of `DemoData` can be set in `conf/format.yml`, such as:

    ```YAML
    columns:

    # pass

    - name: demo_data_column
      type: DemoData

    - name: demo_data_array_column
      type: demo_data_array
    ```

2. Enter the string format in the corresponding column in `conf/dict_data.txt` that meets the requirements of `DemoData`.

### Unit test

Add the relevant unit tests of `DemoData` in `test/data_define_test.cc` and `test/dict_format_test.cc`.

## Discussion

Contact <1135677507@qq.com>
