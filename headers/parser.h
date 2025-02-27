//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_PARSER_H
#define DT096G_REGEX_PARSER_PARSER_H
#include <memory>
#include <sstream>
#include "ast_node.h"
#include "lexer.h"
class parser {
public:
    explicit parser(std::queue<std::pair<Tokens, char>> tokens);

    /**
     * Helper function to make parser code more readable
     * @return current token that the parser is on, without consuming it
     */
    Tokens currentToken() const;

    /**
     * Helper function to make parser code more readable.
     * Moves to the next token in line, consuming the previous one.
     */
    void nextToken();

    /**
     * Recursive function that handles OR operands. Calls parseTerm()
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
     * Recursive function that handles atoms (chars) and unary operands. Calls parseUnary()
     * @return It will either return a groupNode with a recursive branch, or an charNode
     * which will be checked for any potential unary operands that may follow it.
     */
    ASTNodePtr parseFactor();

    /**
     * This is the final function in the recursive call which constructs potential unary operands.
     * This function is marked const because it does not affect any member variables, such as by using
     * nextToken().
     * @return it will either return a unaryNode containing a charNode, or it will simply return the charNode
     * without creating any new nodes or recursive chains.
     */
    ASTNodePtr parseUnary(ASTNodePtr node);

    /**
     * Handles parsing inside of groups. Has error handling included to enforce
     * correct syntax.
     * @return A recursive branch starting from <EXPR>
     */
    ASTNodePtr parseGroup();

private:
    //ASTNodePtr root;
    std::queue<std::pair<Tokens, char>> tkList;
};


#endif //DT096G_REGEX_PARSER_PARSER_H
