/**
 * @file ResultFormatter.h
 *
 * @date 06.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */
 
#ifndef RESULTFORMATTER_H
#define RESULTFORMATTER_H
#include <memory>
#include <nlohmann/json.hpp>

namespace mw {
    class Ast;
}

namespace mwa {

class ResultFormatter {
public:
    explicit ResultFormatter(std::shared_ptr<mw::Ast> ast);

    nlohmann::json & result();

private:

    void format();
    std::shared_ptr<mw::Ast> m_ast;
    nlohmann::json m_result;
};

} // mwa

#endif //RESULTFORMATTER_H
