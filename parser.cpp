//
// Created by Terminal on 05/02/2025.
//

#include <utility>

#include "headers/parser.h"
#include <fstream>
#include <sstream>

Parser::Parser(std::queue<std::pair<Tokens, char> > tokens) : tkList(std::move(tokens)),
                                                              root(parseExpr()) {
}

//TODO:: This is currently broken! causes seg fault for some reason?
Tokens Parser::currentToken() const {
    if (!tkList.empty()) {
        return tkList.front().first;
    }
    return Tokens::EOP;
}

Tokens Parser::peekNextToken() const {
    if (tkList.size() < 1) {
        return Tokens::EOP;
    }
    auto temp = tkList;
    temp.pop();
    return temp.front().first;
}

void Parser::nextToken() {
    if (!tkList.empty()) {
        tkList.pop();
    }
}

ASTNodePtr Parser::getRoot() {
    return std::move(root);
}

ASTNodePtr Parser::parseExpr() {
    auto left = parseTerm();
    while (currentToken() == Tokens::OR) {
        nextToken();
        auto right = parseTerm();
        auto orNode = std::make_unique<ORNode>(std::move(left), std::move(right));
        left = std::move(orNode);
    }
    return left;
}

ASTNodePtr Parser::parseTerm() {
    std::vector<ASTNodePtr> factors;

    factors.push_back(parseFactor());

    while ( // This loop will go on until we capture every possible factor.
        currentToken() != Tokens::OR and
        currentToken() != Tokens::GROUP_END and
        currentToken() != Tokens::EOP
    ) {
        factors.push_back(parseFactor());
    }

    if (factors.size() == 1) {
        return std::move(factors.front());
    }
    auto concatNode = std::make_unique<ConcatNode>();
    concatNode->children = std::move(factors);
    return concatNode;
}

ASTNodePtr Parser::parseFactor() {
    // handle atoms here! as per grammar rules
    if (currentToken() == Tokens::DOT) {
        nextToken();
        auto dotNode = std::make_unique<DotNode>();
        return parseUnary(std::move(dotNode));
    }
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

ASTNodePtr Parser::parseUnary(ASTNodePtr node) {
    switch (currentToken()) {
        case Tokens::KLEENE: {
            auto unaryNode = std::make_unique<KleeneNode>(std::move(node));
            nextToken();
            return unaryNode;

        }
        case Tokens::COUNT_START: {
            std::string strNum;
            while (currentToken() != Tokens::COUNT_END) {
                nextToken();
                if (currentToken() == Tokens::CHAR) {
                    strNum += tkList.front().second;
                } else if (currentToken() != Tokens::COUNT_END) {
                    throw std::runtime_error("parseUnary(): unexpected token (COUNT_START case)");
                }
            }
            int count = std::stoi(strNum);
            nextToken(); // Consume the COUNT_END token.
            auto countNode = std::make_unique<CountNode>(std::move(node), count);
            return countNode;
        }
        default:
            break;
    }
    return node;
}

ASTNodePtr Parser::parseGroup() {
    nextToken();
    auto groupNode = std::make_unique<GroupNode>(parseExpr());
    if (currentToken() == Tokens::GROUP_END) {
        nextToken();
    } else {
        throw std::runtime_error("Expected group but found " + tkList.front().second);
    }
    return groupNode;
}
