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

TEST_CASE("Testing lexer", "[lexer]") {
    std::istringstream s("program Hello; begin end.");
    Lexer lexer(s);

    REQUIRE(Tag::KEY_PROGRAM == lexer.scan().tag);
    REQUIRE(Tag::IDENTIFIER == lexer.scan().tag);
    REQUIRE(Tag::SYM_SEMICOL == lexer.scan().tag);
    REQUIRE(Tag::KEY_BEGIN == lexer.scan().tag);
    REQUIRE(Tag::KEY_END == lexer.scan().tag);
    REQUIRE(Tag::SYM_POINT == lexer.scan().tag);
    
}