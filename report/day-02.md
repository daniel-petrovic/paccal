# Day 2

------

1. Today we will add variable declaration part to our transformer: 


    ```
    var a : integer;
    var b : string;
    ```

    should be transformed to the following C-code:

    ```
    int a;
    string b;
    // we dont consider yet the possible transformation (string -> char*)
    ```

    For simplicity, we will be considering only integer identifiers.

    EBNF used:

    ```
    variable-declaration-part = `var` variable-declaration  `;` .
    variable-declaration = identifier-list `:` type .
    identifier-list = identifier {`,` identifier } .
    type = type-identifier . // for simplicity
    type-identifier = identifier;
    ```

2. We will accoridingly extend our parser (and lexer).
    We have to add the symbole table to the parser too.


    ```
    class Symbol {
        name: string;
    }

    class Env {
        Env(Env* p) : prev(p) {}
        Env* prev;
        table: Map<string, Symbol>;
    }
    ```

    ```
    class Parser {
        Env* env;
        ...

        variable_declaration_part() {
            match("var");
            variable_declaration();
            match(";");
        }

        variable_declaration() {
            identifier_list();
            match(":");
            type();
        }

        identifier_list() {
            identifier();
            if (peekc() == ',') {
                match(",");
                identifier();
            }
        }
    }
    ```