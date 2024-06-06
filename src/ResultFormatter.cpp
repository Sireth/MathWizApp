/**
 * @file ResultFormatter.cpp
 *
 * @date 06.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */
 
#include "ResultFormatter.h"

#include <utility>

#include "Ast.h"
#include "AstUtils.h"
#include "Boolean.h"
#include "ErrorHandler.h"
#include "Number.h"
#include "String.h"

namespace mwa {
    ResultFormatter::ResultFormatter(std::shared_ptr<mw::Ast> ast) {
        m_ast = std::move(ast);
        m_result = nlohmann::json();
        format();
    }

    nlohmann::json & ResultFormatter::result() {
        return m_result;
    }

    void ResultFormatter::format() {
        if (m_ast == nullptr) {
            ErrorHandler() << "Result is null";
        }
        switch (m_ast->type()) {
            case mw::Ast::Type::string: {
                m_result["type"] = "string";
                m_result["result"] = mw::As<mw::String>(m_ast)->value();
                break;
            }
            case mw::Ast::Type::number: {
                m_result["type"] = "number";
                m_result["result"] = mw::As<mw::Number>(m_ast)->value();
                break;
            }
            case mw::Ast::Type::boolean: {
                m_result["type"] = "boolean";
                m_result["result"] = mw::As<mw::Boolean>(m_ast)->value();
                break;
            }
            default: {
                ErrorHandler() << "Unsupported type of result!";
            }
        }
    }
} // mwa