//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_PARSER_H
#define DT096G_REGEX_PARSER_PARSER_H
#include <memory>
#include "ast_node.h"
#include "lexer.h"
class Parser {
public:
    explicit Parser(std::queue<std::pair<Tokens, char>> tokens);

    /**
     * Helper function to make parser code more readable
     * @return current token that the parser is on, without consuming it
     */
    [[nodiscard]] Tokens currentToken() const;

    /**
     * Helper function used in the while loop for parseTerm (A ducktape fix for shoddy queue management)
     * @return returns EOP for empty lists, otherwise returns token
     * that is one step ahead of first()
     */
    [[nodiscard]] Tokens peekNextToken() const;

    /**
     * Helper function to make parser code more readable.
     * Moves to the next token in line, consuming the previous one.
     */
    void nextToken();

    /**
     * getter function for private member root
     * @return Returns private member root
     */
    ASTNodePtr getRoot();

    /**
     * Recursive function that handles OR between two factors. Calls parseTerm()
     * @return It will either return an OrNode with two recursive branches,
     * or it will continue parsing until it returns a single recursive branch
     */
    ASTNodePtr parseExpr();

    /**
     * Recursive function that handles concatenation. Calls parseFactor()
     * @return It will either return a concatNode containing some number of recursive branches.
     * or just one recursive branch
     */
    ASTNodePtr parseTerm();

    /**
     * Recursive function that handles operands. Calls parseUnary() for certain operands.
     * @return It will either return a groupNode with a recursive branch, or a charNode
     * which will be checked for any potential unary operands that may follow it.
     */
    ASTNodePtr parseFactor();

    /**
     * ParseSuffix manages count groups and kleenestars following operands, it is
     * called from parseFactor for operands.
     *
     * @return Returns either a countNode or KleeneNode containing the operand, or it will return
     * the parameter node as is.
     */
    ASTNodePtr parseSuffix(ASTNodePtr node);

    /**
     * Handles parsing inside groups. Has error handling included to enforce
     * correct syntax.
     * @return A recursive branch starting from <EXPR>
     */
    ASTNodePtr parseGroup();

private:
    std::queue<std::pair<Tokens, char>> tkList;
    ASTNodePtr root;
};


#endif //DT096G_REGEX_PARSER_PARSER_H
