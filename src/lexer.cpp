#include "lexer.hpp"


namespace pacc
{

    static bool isLetter(char c)
    {
        return ('a' <= c and c <= 'z') or ('A' <= c and c <= 'Z');
    }

        Lexer::Lexer(std::istream &stream) : m_str{stream}    {
            reserve("program", Tag::KEY_PROGRAM);
            reserve("begin", Tag::KEY_BEGIN);
            reserve("end", Tag::KEY_END);
            reserve("var", Tag::KEY_VAR);
        }

    Token Lexer::nextTok() noexcept
   {
        if (!m_tokenBuffer.empty()) {
            const auto tok = m_tokenBuffer.back();
            m_tokenBuffer.pop_back();
            return tok;
        }

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

        if (peek() == ':') {
            next();
            return {.tag = Tag::SYM_DOUBLECOL};
        }

        if (peek() == '.')
        {
            next();
            return {.tag = Tag::SYM_POINT};
        }

        if (peek() == ',') {
            next();
            return {.tag = Tag::SYM_COMMA};
        }


        if (isLetter(peek()))
        {

            std::string word;

            do
            {
                word.push_back(next());
            } while (isLetter(peek()));

            if (const auto it = m_reserved_words.find(word); it != m_reserved_words.end()) {
                return {.tag = it->second};
            }

            return {.tag = Tag::IDENTIFIER, .attr = word};
        }

        return {.tag = Tag::SOME_CHAR};
    }

Token Lexer::peekTok() noexcept {
    if (m_tokenBuffer.empty()) {
        m_tokenBuffer.push_back(nextTok());
    }
    return m_tokenBuffer.back();
}

} // namespace pacc