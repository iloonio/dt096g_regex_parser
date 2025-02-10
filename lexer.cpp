//
// Created by Terminal on 05/02/2025.
//

#include "headers/lexer.h"
#include <iostream>

//TODO: implement proper error handling
//TODO: Convert vector to queue (We want FIFO for the parser)
std::vector<Lexer::Tokens> Lexer::lex(std::string regex) {
    std::vector<Tokens> tokens;
    auto p = regex.begin();
    while (p != regex.end()) {
        switch (*p) {
            case '+':
                tokens.push_back(OR);
                break;
            case '*':
                tokens.push_back(KLEENE);
                break;
            case '.':
                tokens.push_back(DOT);
                break;
            case '(':
                tokens.push_back(GROUP_START);
                break;
            case ')':
                tokens.push_back(GROUP_END);
                break;
            case '{':
                tokens.push_back(COUNT_START);
                break;
            case '}':
                tokens.push_back(COUNT_END);
                break;

            case '\\': // escape char for '\'
                ++p;
                if (*p =='I') {
                    tokens.push_back(CASE);
                }
                else if (*p == 'O') {
                    tokens.push_back(OUTPUT);
                } else {
                    std::cerr << "invalid regex: Expected 'I' or 'O' after '/'.";
                }
                break;

            default:
                if (isalnum(*p) or isspace(*p)){
                    tokens.push_back(Tokens::CHAR);
                }
                else if (isdigit(*p)) {
                    tokens.push_back(Tokens::DIGIT);
                } else {
                    std::cerr << "invalid char in regex.";
                }
                break;
        }

        //begin at the start of the string and treat each case
        ++p; //move on to the next char
    }
    tokens.push_back(EOP);
    return tokens;
}
