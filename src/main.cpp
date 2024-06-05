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

void print_help() {
    std::cout << "Usage: program_name [options] <json_string>\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help          Show this help message\n";
    std::cout << "  -j, --json <arg>    JSON string to be processed\n";
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

        // Work with the JSON data (for demonstration, we'll just print it)
        std::cout << "Parsed JSON:\n" << json_data.dump(4) << std::endl;
    } catch (nlohmann::json::parse_error& e) {
        mwa::ErrorHandler() << e.what();
        return 1;
    }

    return 0;
}

