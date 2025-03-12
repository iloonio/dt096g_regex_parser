//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_LEXER_H
#define DT096G_REGEX_PARSER_LEXER_H
#include <string>
#include <queue>

enum Tokens {
    EXPR,
    OR,
    KLEENE,
    GROUP_START,
    GROUP_END,
    DOT,
    COUNT_START,
    COUNT_END,
    CHAR,
    DIGIT,
    EOP,
};


/**
 * In convoluted linguistics-borrowed language: sequentially categorizes every lexeme in a sequence into
 * a token category. In simpler english: Divides symbols in a string into tokens.
 * @param regex An expression that complies with regex standards.
 * @return A list of Tokens which will be processed by a parser into an Abstract Syntax Tree
 */
std::queue<std::pair<Tokens, char>> lex(std::string regex);

#endif //DT096G_REGEX_PARSER_LEXER_H
