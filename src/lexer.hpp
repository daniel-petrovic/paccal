#pragma once

#include <istream>

namespace pacc
{

    enum class Tag
    {
        SOME_CHAR,      // some char which doesnt belong to the currently known tags

        // keywords
        KEY_PROGRAM,    // `program`
        KEY_BEGIN,      // `begin`
        KEY_END,        // `end`

        // symbols
        SYM_POINT, // Point `.`
        SYM_SEMICOL,  // Semicolumn `;`

        // other
        IDENTIFIER,   /// identifier e.g. "a" in a = 1, or "MyProg" in program MyProg;
    };

    struct Token {
        Tag tag;
    };

    class Lexer
    {
    public:
        Lexer(std::istream &stream) : m_str{stream} {}

        Token scan() noexcept;

    private:
        inline char peek() const {
            return m_str.peek();
        }

        inline char next() {
            return m_str.get();
        }

    private:
        std::istream &m_str;
    };
}