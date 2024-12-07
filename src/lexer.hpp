#pragma once

#include <istream>
#include <variant>
#include <unordered_map>
#include <vector>

namespace pacc
{

    enum class Tag
    {
        SOME_CHAR, // some char which doesnt belong to the currently known tags

        // keywords
        KEY_PROGRAM, // `program`
        KEY_BEGIN,   // `begin`
        KEY_END,     // `end`
        KEY_VAR,     // `var`

        // symbols
        SYM_POINT,     // Point `.`
        SYM_SEMICOL,   // Semicolumn `;`
        SYM_DOUBLECOL, // Doubledolumn `:`
        SYM_COMMA,     // `,`

        // other
        IDENTIFIER, /// identifier e.g. "a" in a = 1, or "MyProg" in program MyProg;
    };

    struct Token
    {
        Tag tag;

        std::string str() const noexcept
        {
            return std::get<std::string>(attr);
        }

        int32_t i32() const noexcept
        {
            return std::get<int32_t>(attr);
        }

        std::variant<int32_t, std::string> attr;
    };

    class Lexer
    {
    public:
        Lexer(std::istream &stream);

        Token nextTok() noexcept;

        Token peekTok() noexcept;

    private:
        inline void reserve(std::string_view word, const Tag tag) noexcept
        {
            m_reserved_words.emplace(std::string{word}, tag);
        }

        inline char peek() const
        {
            return m_str.peek();
        }

        inline char next()
        {
            return m_str.get();
        }

    private:
        std::istream &m_str;
        std::vector<Token> m_tokenBuffer;
        std::unordered_map<std::string, Tag> m_reserved_words;
    };
}