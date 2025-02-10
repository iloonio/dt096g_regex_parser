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
 * The abstract syntax tree will then 
 *
 */

/* <EXPR>           ->      <CHAR> | <EOP> | etc
 * <CHAR>           ->      <CHAR>[EXPR]
 * <OR>             ->      <EXPR> '+' <EXPR>
 * <KLEENE>         ->      <EXPR>'*'
 * <GROUP>          ->      '(' <EXPR> ')'
 * <GROUP_START>    ->      '(' <EXPR>
 * <GROUP_END>      ->      <EXPR> ')'
 *
 */

int main() {

    auto list = Lexer::lex(R"(lo* could.{3})");

    return 0;
}
