/**
 * @file Variable.cpp
 *
 * @date 05.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#include <iostream>
#include "VariableHandler.h"

#include "AstUtils.h"
#include "ErrorHandler.h"


namespace mwa {
    VariableHandler::VariableHandler(const nlohmann::json &varible) {
        if (varible.is_null()) {
            ErrorHandler() << "Variable is null";
        }
        try {

            if(!varible.contains("name")) {
                ErrorHandler() << "Variable has no name";
            }
            if(!varible.contains("type")) {
                ErrorHandler() << "Variable has no type";
            }
            if(!varible.contains("value")) {
                ErrorHandler() << "Variable has no value";
            }

            m_name = varible["name"];

            auto type = varible["type"].get<std::string>();
            if (type == "string") {
                m_type = String;
                m_varible = std::make_shared<mw::Variable>(m_name, mw::new_string(varible["value"].get<std::string>()));
            } else if (type == "number") {
                m_type = Number;
                m_varible = std::make_shared<
                    mw::Variable>(m_name, mw::new_number(varible["value"].get<std::int64_t>()));
            } else if (type == "boolean") {
                m_type = Boolean;
                m_varible = std::make_shared<mw::Variable>(m_name, mw::new_boolean(varible["value"].get<bool>()));
            } else {
                ErrorHandler() << "Unknown type: " << type;
            }
        } catch (const std::exception &e) {
            ErrorHandler() << e.what();
        }
    }

    const std::string &VariableHandler::name() const {
        return m_name;
    }

    VariableHandler::Type VariableHandler::type() const {
        return m_type;
    }

    std::shared_ptr<mw::Variable> VariableHandler::varible() const {
        return m_varible;
    }
} // mwa
