/**
 * @file main.cpp
 *
 * @date 05.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#include <iostream>
#include <getopt.h>
#include <string>
#include <nlohmann/json.hpp>

#include "ErrorHandler.h"
#include "VariableTable.h"
#include "Driver.h"
#include "ResultFormatter.h"
#include "VariableTableBuilder.h"

void print_help() {
    std::cout << "Usage: program_name [options] <json_string>\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help          Show this help message\n";
    std::cout << "  -j, --json <arg>    JSON string with variables and expression\n";
}

int main(int argc, char* argv[]) {
    int opt;
    std::string json_arg;

    // Define long options
    static option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"json", required_argument, nullptr, 'j'},
        {nullptr, 0, nullptr, 0}
    };

    // Process options
    while ((opt = getopt_long(argc, argv, "hj:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
            return 0;
            case 'j':
                json_arg = optarg;
            break;
            default:
                print_help();
            return 1;
        }
    }

    if (json_arg.empty()) {
        mwa::ErrorHandler() << "Error: No JSON string provided.";
        print_help();
        return 1;
    }

    try {
        // Parse JSON from the argument
        const nlohmann::json json_data = nlohmann::json::parse(json_arg);

        if(json_data.is_null() || !json_data.is_object()) {
            mwa::ErrorHandler() << "Error: JSON string is not an object.";
        }
        mw::VariableTable vt;

        if(json_data.contains("variables")) {
            if(!json_data["variables"].is_array()) {
                mwa::ErrorHandler() << "Error: JSON object does not contain 'variables' array.";
            }

            const auto& variables = json_data["variables"];

            const mwa::VariableTableBuilder builder(variables);

            vt = *builder.variableTable();
        }

        if(!json_data.contains("expression") || !json_data["expression"].is_string()) {
            mwa::ErrorHandler() << "Error: JSON object does not contain 'expression' string.";
        }

        const auto& expression = json_data["expression"].get<std::string>();

        mw::Driver driver;
        driver.setVariableTable(vt);

        const auto ast = driver.Parse(expression);
        mw::EvalVisitor visitor;

        visitor.visit(ast);
        const auto result = visitor.result();

        mwa::ResultFormatter formatter(result);
        std::cout << formatter.result().dump(4) << std::endl;

    } catch (const std::exception &e) {
        mwa::ErrorHandler() << e.what();
        return 1;
    }

    return 0;
}

