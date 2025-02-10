//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_AST_NODE_H
#define DT096G_REGEX_PARSER_AST_NODE_H
#include <vector>

/**
 * Virtual Abstract Syntax tree Node. Using Polymorphism, we will implement all other various types of nodes that will
 * go in our tree.
 */
struct ASTNode {
    // virtual Evaluator evaluate() = 0;
    virtual ~ASTNode()= default;
    std::vector<ASTNode*> operands{};
};

struct OrNode : ASTNode {
    explicit OrNode(ASTNode* OP1, ASTNode* OP2) {
        operands.push_back(OP1);
        operands.push_back(OP2);
    }
};

/**
 * Example of a child node for the ASTNode. We will override the evaluate function.
 */
struct CharNode : ASTNode{
    char c;
    explicit CharNode(char c) : c(c){}; //Constructor for CharNode
    // Evaluator evaluate() override; //TODO: This has to be implemented in order for the vtable to work properly.
};

struct ExprNode : ASTNode {

};


#endif //DT096G_REGEX_PARSER_AST_NODE_H
