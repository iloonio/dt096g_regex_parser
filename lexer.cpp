//
// Created by Terminal on 05/02/2025.
//

#include "headers/lexer.h"
#include <iostream>

std::queue<std::pair<Tokens, char>> lex(std::string regex) {
    std::queue<std::pair <Tokens, char>> tokens;

    //First, lex for all cases of "\", then do the rest of the lexing.
    for (auto p = regex.begin(); p != regex.end(); ++p) {
        if (*p == '\\') {
            auto startPos = p;
            ++p;
            if (*p =='I') {
                tokens.emplace(CASE, *p);
            }
            else if (*p == 'O') {
                tokens.emplace(OUTPUT, *p);
            } else {
                std::cerr << "invalid regex: Expected 'I' or 'O' after '/'." << std::endl;
                break;
            }
            p = regex.erase(startPos, p+1);
        }
    }

    auto p = regex.begin();
    while (p != regex.end()) {
        switch (*p) {
            case '+':
                tokens.emplace(OR,*p);
                break;
            case '*':
                tokens.emplace(KLEENE, *p);
                break;
            case '.':
                tokens.emplace(DOT, *p);
                break;
            case '(':
                tokens.emplace(GROUP_START, *p);
                break;
            case ')':
                tokens.emplace(GROUP_END, *p);
                break;
            case '{':
                tokens.emplace(COUNT_START, *p);
                break;
            case '}':
                tokens.emplace(COUNT_END, *p);
                break;
            default:
                if (isalnum(*p) or isspace(*p)){
                    tokens.emplace(Tokens::CHAR, *p);
                }
                else if (isdigit(*p)) {
                    tokens.emplace(Tokens::DIGIT, *p);
                } else {
                    std::cerr << "invalid char in regex." << std::endl;
                }
                break;
        }

        //begin at the start of the string and treat each case
        ++p; //move on to the next char
    }

    tokens.emplace(EOP, '_');
    return tokens;
}
