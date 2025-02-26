//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_AST_NODE_H
#define DT096G_REGEX_PARSER_AST_NODE_H
#include <memory>
#include <vector>

#include "ast_node.h"
#include "ast_node.h"
#include "ast_node.h"

using ASTNodePtr = std::unique_ptr<struct ASTNode>;

/**
 * Also Known as Operands (OP), I am not sure on the naming convention
 *
 *
 */
/**
 * Virtual Abstract Syntax tree Node. Using Polymorphism, we will implement all other various types of nodes that will
 * go in our tree.
 */
struct ASTNode {
    // virtual Evaluator evaluate() = 0;
    virtual ~ASTNode()= default;
};

/**
 * Example of a child node for the ASTNode. We will override the evaluate function.
 */
struct CharNode : ASTNode{
    char c;
    //Constructor for CharNode
    explicit CharNode(const char c) : c(c) {};
    // Evaluator evaluate() override; //TODO: This has to be implemented in order for the vtable to work properly.
};

struct ORNode : ASTNode {
    ASTNodePtr left;
    ASTNodePtr right;
    explicit ORNode(ASTNodePtr lhs, ASTNodePtr rhs);
};

struct ConcatNode : ASTNode {
    std::vector<ASTNodePtr> children;
};

struct UnaryNode : ASTNode {
    ASTNodePtr atom;
    explicit UnaryNode(ASTNodePtr atom);
};

struct GroupNode : ASTNode {
    ASTNodePtr expression;
    explicit GroupNode(ASTNodePtr expression);
};

struct EOPNode : ASTNode {
    explicit EOPNode()= default;
  //Evaluator evaluate() override;
};

// struct OrNode : ASTNode {
//     explicit OrNode(ASTNode* OP1, ASTNode* OP2) {
//         operands.push_back(OP1);
//         operands.push_back(OP2);
//     }
// };

#endif //DT096G_REGEX_PARSER_AST_NODE_H
