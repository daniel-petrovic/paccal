
#include "parser.hpp"

namespace pacc
{

    std::string Parser::parse() noexcept
    {
        program();
        return m_out.str();
    }

    void Parser::program()
    {
        programHeading();
        block();
        match(Tag::SYM_POINT);
    }

    void Parser::programHeading()
    {
        match(Tag::KEY_PROGRAM);
        identifier();
        match(Tag::SYM_SEMICOL);
        semaPrint("int main() ");
    }
    void Parser::block()
    {
        match(Tag::KEY_BEGIN);
        semaPrint("{");
        match(Tag::KEY_END);
        semaPrint("}");
    }
    void Parser::identifier()
    {
        // temporarily we handle identifier as a terminal
        match(Tag::IDENTIFIER);
    }

    void Parser::match(Tag tag)
    {
        if (m_lex.scan().tag != tag)
        {
            throw "Invalid Syntax";
        }
    }

    void Parser::semaPrint(std::string_view s)
    {
        m_out << s;
    }

}