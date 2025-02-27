#include <iostream>
#include "headers/Evaluator.h"
#include "headers/lexer.h"
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
 */

/* <REGEX>      ->      <EXPR>
 * <EXPR>       ->      <TERM> {"+" <TERM>  }*                  (* Alternation OR *)
 * <TERM>       ->      <FACTOR>+                               (* Concatenation *)
 * <FACTOR>     ->      <ATOM> <UNARY>?                         (* Atom with optional unary operand *)
 * <ATOM>       ->      <CHAR> | <DOT> | <GROUP> | <CASE>       (* Smallest unit in expressions *)
 * <GROUP>      ->      "(" <EXPR> ")"
 * <UNARY>      ->      <STAR> | <COUNT>
 *
 * <STAR>       ->      "*"                                     (*One or more occurrences*)
 * <COUNT>      ->      "{" <DIGIT> "}"
 * <CASE>       ->      "/O"
 * <DOT>        ->      "."
 * <CHAR>       ->      [a-zA-Z0-9]
 * <DIGIT>      ->      [0-9]+
 *
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

int main() {

    char c = '2';
    std::string str = " ";
    for (int i = 0; i < 5; ++i) {
        str += c;
    }
    int num = stoi(str);
    auto list = lex(R"(lo* could.{3})");

    //TODO: Debug parser! make sure it can create an AST from a given regex pattern.
    return 0;
}
