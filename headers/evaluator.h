//
// Created by Terminal on 11/03/2025.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "ast_node.h"


//TODO: Create your evaluator class that will run evaluation functions.
class Evaluator {
public:
    Evaluator(std::string text, ASTNodePtr root);

    void evaluate();
private:
    std::string text;
    ASTNodePtr root;
    MatchResult match;

};



#endif //EVALUATOR_H
