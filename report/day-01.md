# Day 1

------

1. Define Grammar using EBNF (ISO-14977). Starting point https://www.cs.kent.edu/~durand/CS43101Fall2004/resources/Pascal-EBNF.html .

1. Setup basic project structure: C++/CMake/tests(CATCH2).

1. Implement lexer and parser for the following simple program block (file Hello.pas):

    ```
    program Hello;
    begin
    end.
    ```

    EBNF used:

    ```
    program = program-heading block `.` .
    program-heading = `program` identifier `;` .
    block = `begin` `end` .
    ```

    What we want to have as output is a C source file Hello.c with the following content:

    ```
    int main() {}
    ```

    We start with predictive recursive-descent parser, to keep it simple at the start.
    During parsing we will start executing some semantic actions.
    All semantic actions will start with *sema\<ActionName\>*, to be able to differentiate them from production handling methods for non-terminals.

    The pseudo code for the parser would look like:

    ```
    class Parser {
        parse() {
            program()
        }

        program() {
            program_heading();
            block();
            match(".")
        }

        program_heading() {
            match("program");
            identifier();
            match(";");
            semaPrint('int main() ')
        }

        block() {
            match("begin");
            semaPrint("{");
            match("end");
            semaPrint('}');
        }

    }
    ```