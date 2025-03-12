//
// Created by Terminal on 11/03/2025.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "ast_node.h"


//TODO: Create your evaluator class that will run evaluation functions.
class Evaluator {
public:
    /**
     * Constructor for Evaluator class.
     * @param text input.txt
     * @param root root to an Abstract Syntax Tree
     */
    Evaluator(std::string text, ASTNodePtr root);

    /**
     * Calls for evaluation of Abstract Syntax Tree (root). Will keep evaluating until we return match.exit = true,
     * or until we reach the end of the text.
     */
    void evaluate();

    /**
     * prints out match.match result and match.exit bool value.
     */
    void printMatch() const;
private:
    std::string text;
    ASTNodePtr root;
    MatchResult match = {"", false};

};



#endif //EVALUATOR_H
