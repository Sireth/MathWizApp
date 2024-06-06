/**
 * @file VariableTableBuilder.cpp
 *
 * @date 06.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#include "../include/VariableTableBuilder.h"

#include "ErrorHandler.h"
#include "VariableHandler.h"
#include "VariableTable.h"

namespace mwa {
    VariableTableBuilder::VariableTableBuilder(const nlohmann::json &variables) :
        m_variables(variables) {
        m_variableTable = std::make_shared<mw::VariableTable>();
        init();
    }

    const std::shared_ptr<mw::VariableTable> &VariableTableBuilder::variableTable() const {
        return m_variableTable;
    }

    std::shared_ptr<mw::VariableTable> & VariableTableBuilder::variableTable() {
        return m_variableTable;
    }

    void VariableTableBuilder::init() const {
        if (m_variables.is_null()) {
            ErrorHandler() << "Variables is null";
        }
        if (!m_variables.is_array()) {
            ErrorHandler() << "Variables is not array";
        }

        for (const auto &varible: m_variables) {
            VariableHandler variable_handler(varible);
            m_variableTable->setVariable(variable_handler.varible());
        }
    }
} // mwa
