#pragma once

#include "lexer.hpp"

#include <istream>
#include <sstream>

namespace pacc {
    class Parser {
        public:
        Parser(std::istream& source) : m_lex{source} {}

        std::string parse() noexcept;

        private:
        void program();
        void programHeading();
        void block();
        void identifier();
        void match(Tag);

        void semaPrint(std::string_view s);

        Lexer  m_lex;
        std::ostringstream m_out;
    };
}