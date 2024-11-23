#include "compiler.hpp"
#include "parser.hpp"
#include "lexer.hpp"

namespace pacc {
    std::string  Compiler::compile(std::istream& s) {
        auto p = Parser{s};
        return p.parse();
    }
}