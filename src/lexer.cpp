#include "lexer.hpp"

namespace pacc
{
    static bool isLetter(char c)
    {
        return ('a' <= c and c <= 'z') or ('A' <= c and c <= 'Z');
    }

    Token Lexer::scan() noexcept
    {
        for (;; next())
        {
            if (peek() == ' ' || peek() == '\t' || peek() == '\n') continue; 

            break;
        }

        if (peek() == ';')
        {
            next();
            return {.tag = Tag::SYM_SEMICOL};
        }

        if (peek() == '.')
        {
            next();
            return {.tag = Tag::SYM_POINT};
        }

        if (isLetter(peek()))
        {

            std::string word;

            do
            {
                word.push_back(next());
            } while (isLetter(peek()));

            if (word == "program")
            {
                return {.tag = Tag::KEY_PROGRAM};
            }
            if (word == "begin")
            {
                return {.tag = Tag::KEY_BEGIN};
            }
            if (word == "end")
            {
                return {.tag = Tag::KEY_END};
            }

            return {.tag = Tag::IDENTIFIER};
        }

        return {.tag = Tag::SOME_CHAR};
    }

} // namespace pacc