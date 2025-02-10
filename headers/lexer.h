//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_LEXER_H
#define DT096G_REGEX_PARSER_LEXER_H
#include <string>
#include <vector>
#include <queue>
#include "Evaluator.h"
#include "ast_node.h"

/* <REGEXPR>    ->  <EXPR>
 * <EXPR>       ->  <CHAR> | <EOP>
 * <CHAR>       ->  <CHAR>[<EXPR>]
 * <EOP>        ->  exit
 *
 *
 */



/**
 * The Lexer takes in an input string and turns it into an array of tokens.
 */
//TODO: Reconsider if we even need a whole class for Lexing.

//Reasons for having a classless Lexer:
    // - We only lex once and then we're done.
class Lexer {
    enum Tokens {
        REGEXP,
        OR,
        KLEENE,
        GROUP_START,
        GROUP_END,
        DOT,
        COUNT_START,
        COUNT_END,
        CASE,
        OUTPUT,
        CHAR,
        DIGIT,
        EOP,
    };
public:
    /**
     * In convoluted linguistics-borrowed language: sequentially categorizes every lexeme in a sequence into
     * a token category. In simpler english: Sequentially divides each symbol into a tokens.
     * @param regex An expression that complies with regex standards.
     * @return A list of Tokens which will be processed by a parser into an Abstract Syntax Tree
     */
    static std::vector<Tokens> lex(std::string regex);
};


#endif //DT096G_REGEX_PARSER_LEXER_H
