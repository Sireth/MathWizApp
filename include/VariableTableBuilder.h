/**
 * @file VariableTableBuilder.h
 *
 * @date 06.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#ifndef VARIABLETABLEBUILDER_H
#define VARIABLETABLEBUILDER_H
#include <nlohmann/json.hpp>

namespace mw {
    class VariableTable;
}

namespace mwa {
    class VariableTableBuilder {
    public:
        explicit VariableTableBuilder(const nlohmann::json &variables);

        const std::shared_ptr<mw::VariableTable> & variableTable() const;

        std::shared_ptr<mw::VariableTable> & variableTable();

    private:
        void init() const;

        const nlohmann::json &m_variables;

        std::shared_ptr<mw::VariableTable> m_variableTable;
    };
} // mwa

#endif //VARIABLETABLEBUILDER_H
