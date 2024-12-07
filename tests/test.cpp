#include <catch2/catch_test_macros.hpp>

#include "compiler.hpp"
#include "lexer.hpp"

#include <sstream>

using namespace pacc;

TEST_CASE("program-block", "[program-block]") {
    Compiler c;
    std::istringstream source{"program Hello; begin end ."};
    REQUIRE(c.compile(source) == "int main() {}");
}

TEST_CASE("reserved keywords", "[lexer keywords]") {
    std::istringstream s("program Hello; begin end.");
    Lexer lexer(s);

    REQUIRE(Tag::KEY_PROGRAM == lexer.nextTok().tag);
    REQUIRE(Tag::IDENTIFIER == lexer.nextTok().tag);
    REQUIRE(Tag::SYM_SEMICOL == lexer.nextTok().tag);
    REQUIRE(Tag::KEY_BEGIN == lexer.nextTok().tag);
    REQUIRE(Tag::KEY_END == lexer.nextTok().tag);
    REQUIRE(Tag::SYM_POINT == lexer.nextTok().tag);
    
}

TEST_CASE("variable declaration keyword", "[lexer var keyword]") {
    std::istringstream s("xxx , var :  yyy");
    Lexer lexer(s);

    REQUIRE(Tag::IDENTIFIER == lexer.nextTok().tag);
    REQUIRE(Tag::SYM_COMMA == lexer.nextTok().tag);
    REQUIRE(Tag::KEY_VAR == lexer.nextTok().tag);
    REQUIRE(Tag::SYM_DOUBLECOL == lexer.nextTok().tag);
    REQUIRE(Tag::IDENTIFIER == lexer.nextTok().tag);
}

TEST_CASE("variable declaration", "[vardecl]") {
    Compiler c;
    std::istringstream source{"var a : integer;"};
    REQUIRE(c.compile(source) == "integer a;");
}