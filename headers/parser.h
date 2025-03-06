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
     * Helper function used in the while loop for parseTerm (A ducktape fix for shoddy queue management)
     * @return if index is 2 or less, returns EOP, otherwise returns token
     * that is one step ahead of first()
     */
    Tokens peekNextToken() const;

    /**
     * Helper function to make parser code more readable.
     * Moves to the next token in line, consuming the previous one.
     */
    void nextToken();

    ASTNodePtr getRoot();

    ASTNodePtr parseRegex();

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
     * ParseUnary manages count groups and kleenestars following atomic nodes (dot and char) or flagNodes (solely count in that case), it is
     * called from parseRegex for flagNodes, and parseFactor for atomic nodes.
     *
     *
     *
     * @return For atomic nodes: returns either a countNode or KleeneNode containing the atomic node, or it will return
     * the parameter node as is. For FlagNodes: returns FlagNode with an updated captureCount member.
     * without creating any new nodes or recursive chains.
     */
    ASTNodePtr parseUnary(ASTNodePtr node);

    /**
     * Handles parsing inside of groups. Has error handling included to enforce
     * correct syntax.
     * @return A recursive branch starting from <EXPR>
     */
    ASTNodePtr parseGroup();

    std::unique_ptr<FlagNode> parseCaptureCount(std::unique_ptr<FlagNode> flagNode);


private:
    std::queue<std::pair<Tokens, char>> tkList;
    ASTNodePtr root;
};


#endif //DT096G_REGEX_PARSER_PARSER_H
