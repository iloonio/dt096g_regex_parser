#include <fstream>
#include <iostream>
#include "headers/lexer.h"
#include "headers/parser.h"
/**
 * There are multiple approaches to this. We can either run a program, or have a token list consisting of the tokens that our
 * lexer has made. That way we dont need to lex at every point, instead we can use tokens from a list for our parsing (which
 * will create the abstract syntax tree).
 *
 * Define a Grammar of operands (<CHAR>, <OR>, etc) which are
 * Lexer will breakdown the input string into a Token List.
 * We will then sequentially run through this list with our Parser/parse function to build an abstract syntax tree.
 *
 * //https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form
 *
 * We will use Recursive Descent parsing to make the tree. This means that we will need to keep in mind our current
 * token in the list, as well as the token that will follow it. Tokens will be "consumed" by the parser to make progress.
 * This works best with Left-to-Right parsers,
 * https://en.wikipedia.org/wiki/Recursive_descent_parser
 *
 *
 *
 * To avoid parentheses, it is assumed that the Kleene star has the highest priority followed by concatenation,
 * then alternation. If there is no ambiguity, then parentheses may be omitted.
 * //https://en.wikipedia.org/wiki/Regular_expression
 *
 *
 *
 * HOW TO EVALUATE:
 * Group-by-Group, evaluate one at a time.
 * Go through the string sequentially and if a match is found, develop on it.
 * This means that we will repeatedly try to find the first instance of our operators,
 * and slice of any character that we've already gone through.
 *
 * Also: See page 183 in Concepts of Programming Languages
 *
 * More Thoughts: A language should consist of a lexical analyzer and a Syntax analyzer.
 * Lexical analyzers are straight-forward, while Syntax analyzers have two goals: detect syntax errors
 * and produce a parse tree, or possibly just the information to construct the parser tree.
 *
 * Parsers have complexity O(n^3), but parsers for programming languages work on subclasses of
 * unambiguous grammars and have complexity O(n).
 *
 * ALSO: Case-insensitive and Capture-group should always be parsed first >:( They should be the root of a given tree
 * a solution could be to have the lexer first look after every instance of "/" to find these special tokens.
 * Our parser can then eat these tokens the first thing it does, which saves us time by not forcing us to move everything
 * away from queues.
 */

/* <REGEX>      ->      <EXPR> [CASE][CAPTURE]                                                                          DONE
 * <EXPR>       ->      <TERM> {"+" <TERM>  }*                  (* Alternation OR *)                                    DONE
 * <TERM>       ->      <FACTOR>+                               (* Concatenation *)                                     DONE
 * <FACTOR>     ->      <ATOM> <UNARY>?                         (* Atom with optional unary operand *)                  DONE
 * <ATOM>       ->      <CHAR> | <DOT> | <GROUP>                (* Smallest unit in expressions *)                      DONE
 * <GROUP>      ->      "(" <EXPR> ")"                                                                                  DONE
 * <UNARY>      ->      <STAR> | <COUNT>                                                                                DONE
 *
 * <STAR>       ->      "*"                                     (*One or more occurrences*)                             DONE
 * <COUNT>      ->      "{" <DIGIT> "}"                                                                                 DONE
 * <CASE>       ->      "/I"                                                                                            WIP
 * <CAPTURE>    ->      "/O"<COUNT>                                                                                     FORGOT :(
 * <DOT>        ->      "."                                                                                             DONE
 * <CHAR>       ->      [a-zA-Z0-9]                                                                                     DONE
 * <DIGIT>      ->      [0-9]+                                                                                          DONE
 *
 *
 */
/*
 * ### OLD ###
 * <EXPR>           ->     <KLEENE> | <GROUP> | <OR> | <EOP>         ;
 * <CHAR>           ->      <LETTER> [<EXPR>]   ;  //a letter and none or one instance of an <EXPR>
 * <EOP>            ->     End of Code         ;
 *
 * <OR>             ->      <EXPR> '+' <EXPR>   ; //Binary operand, requires two expressions
 *                                                //OR is incorect here, as n
 *
 * <KLEENE>         ->      <EXPR>'*'           ; //Primary operand, requires one expression ahead of itself
 * <GROUP>          ->      '(' <EXPR> ')'      ; //grouping operand.
 *
 *
 * ## Supporting grammar
 * <LETTER>         ->        "A" | "B" | "C" | "D" | "E" | "F" | "G"
                            | "H" | "I" | "J" | "K" | "L" | "M" | "N"
                            | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
                            | "V" | "W" | "X" | "Y" | "Z" | "a" | "b"
                            | "c" | "d" | "e" | "f" | "g" | "h" | "i"
                            | "j" | "k" | "l" | "m" | "n" | "o" | "p"
                            | "q" | "r" | "s" | "t" | "u" | "v" | "w"
                            | "x" | "y" | "z" ;
 */

int finalMain();

int main() {
    // Ensure the correct number of arguments
    std::ifstream file;
    file.open("input.txt");
    std::string pattern = R"(\I loo \O )";
    std::string text{};
    std::getline(file, text);

    auto list = lex(pattern);

    parser prs(lex(R"(a+bc*)"));

    //auto root = prs.parseExpr();

    return 0;
}

// match "lo* could.{3}" < input.txt
    // "lo* could.{3}" is passed as argv into the function
    // < input.txt is redirected into std::cin, which we read from.
int finalMain(int argc, char *argv[]) {
    //prepare inputs
    //TODO test that this works.
    std::string pattern = argv[1];
    std::string text;
    std::getline(std::cin, text);

    //lex & pass to parser
    const auto tkList = lex(pattern);

    //parse & pass to evaluator
    parser prs(tkList);

    //Evaluate & Print to console
    auto root = prs.getRoot();

    return 0;
}
