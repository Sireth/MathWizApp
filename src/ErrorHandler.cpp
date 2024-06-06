/**
 * @file ErrorHandler.cpp
 *
 * @date 05.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#include "../include/ErrorHandler.h"

#include <iostream>
#include <../external/json/include/nlohmann/json.hpp>

namespace mwa {
    ErrorHandler::ErrorHandler(const std::exception &e) {
        logError(e.what());
        std::exit(EXIT_FAILURE); // Завершение работы программы с кодом ошибки
    }

    ErrorHandler::~ErrorHandler() {
        if (!m_errorStream.str().empty()) {
            logError(m_errorStream.str());
            std::exit(EXIT_FAILURE); // Завершение работы программы с кодом ошибки
        }
    }

    void ErrorHandler::logError(const std::string &errorMessage) {
        // Создаем JSON объект с информацией об ошибке
        nlohmann::json errorJson;
        errorJson["type"] = "error";
        errorJson["result"] = errorMessage;

        // Выводим JSON объект в консоль
        std::cout << errorJson.dump(4) << std::endl;
    }
} // mwa
