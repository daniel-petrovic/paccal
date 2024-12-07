
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
        m_env = std::make_shared<Env>(m_env);
        match(Tag::KEY_BEGIN);
        semaPrint("{");
        match(Tag::KEY_END);
        semaPrint("}");
    }
    void Parser::identifier()
    {
        auto tokIdentifier = m_lex.nextTok();
        if (tokIdentifier.tag != Tag::IDENTIFIER) {
            throw "Error: Expected identifier";
        }
        semaPrint(tokIdentifier.str());
    }

    void Parser::match(Tag tag)
    {
        if (m_lex.nextTok().tag != tag)
        {
            throw "Invalid Syntax";
        }
    }

        void Parser::variableDeclarationPart() {
            match(Tag::KEY_VAR);
            variableDeclaration();
            match(Tag::SYM_SEMICOL);
        }

        void Parser::variableDeclaration() {
            identifierList();
            match(Tag::SYM_DOUBLECOL);
            type();
        }

        void Parser::identifierList() {
            identifier();
            if (m_lex.peekTok().tag == Tag::SYM_COMMA) {
                match(Tag::SYM_COMMA);
                semaPrint(",");
                identifierList();
            }
        }

        void Parser::type() {
            typeIdentifier();
        }

        void Parser::typeIdentifier() {
            Token tokType = m_lex.nextTok();

            if (tokType.tag != Tag::IDENTIFIER) {
                throw "Error: Type identifier expected";
            }
        }

    void Parser::semaPrint(std::string_view s)
    {
        m_out << s;
    }

}