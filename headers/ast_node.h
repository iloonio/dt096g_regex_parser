//
// Created by Terminal on 05/02/2025.
//
#ifndef DT096G_REGEX_PARSER_AST_NODE_H
#define DT096G_REGEX_PARSER_AST_NODE_H
#include <memory>
#include <utility>
#include <vector>
#include "ast_node.h"
using ASTNodePtr = std::unique_ptr<struct ASTNode>;

/**
 * MatchResult struct is passed around during the evaluation of the syntax tree.
 *
 * Std::string match contains the string of characters that has been matched by an evaluation
 *
 * bool exit is a flag notifying a successful match or not.
 * Upon failing, we will most likely always flush
 * the string match.
 */
struct MatchResult {
    std::string match;
    bool exit;
    MatchResult(std::string match, const bool exit): match(std::move(match)), exit(exit) {}
};

/**
 * Abstract Syntax Tree Nodes built a tree which is used to evaluate a given regex pattern
 * to produce behavior. This class is abstract and is inherited by all other Node types.
 */
struct ASTNode {
    virtual MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) = 0;
    virtual ~ASTNode()= default;
};

/**
 * CharNode manages evaluation of any single characters in a tree.
 */
struct CharNode : ASTNode{
    char c;
    //Constructor for CharNode
    explicit CharNode(char c);
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * DotNode manages evaluation of the dot operand (.) in a tree. shares similarities to CharNode
 */
struct DotNode : ASTNode {
    explicit DotNode();
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * ORNode manages evaluation of an OR operation between two operands (OP1 + OP2).
 * It can only be constructed if given a left and right ASTNode.
 */
struct ORNode : ASTNode {
    ASTNodePtr left;
    ASTNodePtr right;
    explicit ORNode(ASTNodePtr lhs, ASTNodePtr rhs);
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * ConcatNode manages evaluation of concatenated Operands (OP1 OP2 OP3 ...)
 */
struct ConcatNode : ASTNode {
    std::vector<ASTNodePtr> children;
    explicit ConcatNode();
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * KleeneNode manages evaluation of an operand under the effect of a KleeneNode (OP*).
 */
struct KleeneNode : ASTNode {
    ASTNodePtr atom;
    explicit KleeneNode(ASTNodePtr atom);
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * CountNode manages evaluation of an operand under the effect of a counter (OP{n})
 */
struct CountNode : ASTNode {
    ASTNodePtr atom;
    int count;
    explicit CountNode(ASTNodePtr atom, int count);
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

/**
 * GroupNode manages evaluation of an expression directly inside it. ((EXPR))
 */
struct GroupNode : ASTNode {
    ASTNodePtr expression;
    explicit GroupNode(ASTNodePtr expression);
    MatchResult evaluate(size_t &index, const std::string &text, bool caseInsensitive) override;
};

#endif //DT096G_REGEX_PARSER_AST_NODE_H
