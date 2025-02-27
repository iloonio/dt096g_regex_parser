//
// Created by Terminal on 05/02/2025.
//

#include <utility>

#include "headers/parser.h"
#include <fstream>
#include <sstream>

parser::parser(std::queue<std::pair<Tokens, char>> tokens): tkList(std::move(tokens)){}

Tokens parser::currentToken() const {
    if (!tkList.empty()) {
        return tkList.front().first;
    }
    return Tokens::EOP;
}

void parser::nextToken() {
    if (!tkList.empty()) {
        tkList.pop();
    }
}

ASTNodePtr parser::parseExpr() {
    auto left = parseTerm();
    while (currentToken() == Tokens::OR) {
        nextToken();
        auto right = parseTerm();
        auto orNode = std::make_unique<ORNode>(std::move(left),std::move(right));
        left = std::move(orNode);
    }
    return left;
}

ASTNodePtr parser::parseTerm() {
    auto left = parseFactor();
    // This loop will go on until we capture every possible factor.
    while (currentToken() != Tokens::OR and currentToken() != Tokens::GROUP_END and !tkList.empty()) {
        auto right = parseFactor();
        auto concatNode = std::make_unique<ConcatNode>();
        concatNode->children.push_back(std::move(left));
        concatNode->children.push_back(std::move(right));
        left = std::move(concatNode);
    }
    return left;
}

ASTNodePtr parser::parseFactor() {
    // handle atoms here! as per grammar rules
    /*
     * if DOT:
     * TODO: Implement "."!!!
     * if CASE:
     * TODO: Implement Case insensitive!
     */
    if (currentToken() == Tokens::GROUP_START) {
        return parseGroup();
    }
    if (currentToken() == Tokens::CHAR) {
        char ch = tkList.front().second;
        nextToken();
        auto charNode = std::make_unique<CharNode>(ch);
        return parseUnary(std::move(charNode));
    }
    throw std::runtime_error("parseFactor(): unexpected token");
}

ASTNodePtr parser::parseUnary(ASTNodePtr node) {
    switch (currentToken()) {
        case Tokens::KLEENE:
            auto unaryNode = std::make_unique<KleeneNode>(std::move(node));
            return unaryNode;
        case Tokens::COUNT_START:
            std::string strNum;
              while (currentToken() != Tokens::COUNT_END) {
                  nextToken();
                   if (currentToken() == Tokens::CHAR) {
                       strNum += tkList.front().second;
                   } else if (currentToken() != Tokens::COUNT_END) {
                       throw std::runtime_error("parseUnary(): unexpected token (COUNT_START case)");
                   }
              }
              int count = std::stoi(strNum); //convert concatenated string to a number.
              /* create unique CountingNode that stores count and is
              parent to an atom that precedes it in tkList. */
              auto countNode = std::make_unique<CountNode>(std::move(node), count);
              return countNode;
        default:
            throw std::runtime_error("parseUnary(): unexpected token (default case)");
    }
    return node;
}

ASTNodePtr parser::parseGroup() {
    if (currentToken() == Tokens::GROUP_START) {
        nextToken();
        auto groupNode = std::make_unique<GroupNode>(parseExpr());
        if (currentToken() == Tokens::GROUP_END) {
            nextToken();
        }
        return groupNode;
    }
    throw std::runtime_error("Expected group but found " + tkList.front().second);
}
