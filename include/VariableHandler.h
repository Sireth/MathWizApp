/**
 * @file VariableHandler.h
 *
 * @date 05.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#ifndef VARIABLE_HANDLER_H
#define VARIABLE_HANDLER_H

#include <nlohmann/json.hpp>
#include <Variable.h>

namespace mwa {
    class VariableHandler {
    public:
        enum Type {
            String,
            Number,
            Boolean
        };

        explicit VariableHandler(const nlohmann::json &varible);

        VariableHandler() = delete;

        VariableHandler(const VariableHandler &) = delete;

        VariableHandler &operator=(const VariableHandler &) = delete;

        const std::string &name() const;

        Type type() const;

        std::shared_ptr<mw::Variable> varible() const;

    private:
        /// Имя переменной
        std::string m_name;
        /// Тип переменной
        Type m_type;
        /// Указатель на переменную
        std::shared_ptr<mw::Variable> m_varible;
    };
} // mwa

#endif //VARIABLE_HANDLER_H
