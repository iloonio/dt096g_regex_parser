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

    MatchResult(std::string match, const bool exit): match(std::move(match)), exit(exit) {
    }
};


/**
 * Abstract Syntax Tree Nodes built a tree which is used to evaluate a given regex pattern
 * to produce behavior. This class is abstract and is inherited by all other Node types.
 */
struct ASTNode {
    virtual MatchResult evaluate(size_t &index, const std::string &text) = 0;

    virtual ~ASTNode() = default;
};


/**
 * CharNode manages evaluation of any single characters in a tree.
 */
struct CharNode final : ASTNode {
    char c;

    //Constructor for CharNode
    explicit CharNode(char c);

    /**
    * moves index up by one step
    * @param index current index of text
    * @param text input.txt
    * @return MatchResult with a character matching member c.
    */
    MatchResult evaluate(size_t &index, const std::string &text) override;
};


/**
 * DotNode manages evaluation of the dot operand (.) in a tree. shares similarities to CharNode
 */
struct DotNode final : ASTNode {
    explicit DotNode();

    /**
     * moves index up by one step
     * @param index current index of text
     * @param text input.txt
     * @return MatchResult with a character on the passed index
     */
    MatchResult evaluate(size_t &index, const std::string &text) override;
};

/**
 * ORNode manages evaluation of an OR operation between two operands (OP1 + OP2).
 * It can only be constructed if given a left and right ASTNode.
 */
struct ORNode final : ASTNode {
    ASTNodePtr left;
    ASTNodePtr right;


    /**
    * Runs evaluates on member nodes, returning whichever one is true first (lhs preference)
    * @param index Current index of text
    * @param text input.txt
    * @return evaluates lhs, and if it returns false, we evaluates rhs.
    */
    explicit ORNode(ASTNodePtr lhs, ASTNodePtr rhs);

    MatchResult evaluate(size_t &index, const std::string &text) override;
};

/**
 * ConcatNode manages evaluation of concatenated Operands (OP1 OP2 OP3 ...)
 */
struct ConcatNode final : ASTNode {
    std::vector<ASTNodePtr> children;

    explicit ConcatNode();

    /**
    * moves index up by one step
    * @param index current index of text
    * @param text input.txt
    * @return MatchResult with a character matching member c.
    */
    MatchResult evaluate(size_t &index, const std::string &text) override;
};

/**
 * KleeneNode manages evaluation of an operand under the effect of a KleeneNode (OP*).
 */
struct KleeneNode final : ASTNode {
    ASTNodePtr operand;

    explicit KleeneNode(ASTNodePtr operand);

    /**
    * Will run its operand until it returns MatchResult.match == false
    * @param index current index of text
    * @param text input.txt
    * @return MatchResult with characters from operand->evaluate
    */
    MatchResult evaluate(size_t &index, const std::string &text) override;
};

/**
 * CountNode manages evaluation of an operand under the effect of a counter (OP{n})
 */
struct CountNode final : ASTNode {
    ASTNodePtr operand;
    int count;

    explicit CountNode(ASTNodePtr operand, int count);

    /**
     * evaluates member operand [count]-many times
     * @param index
     * @param text
     * @return MatchResult containing a match with exactly the amount of counts lbalbalblalal...
     */
    MatchResult evaluate(size_t &index, const std::string &text) override;
};

/**
 * GroupNode manages evaluation of an expression directly inside it. ((EXPR))
 */
struct GroupNode final : ASTNode {
    ASTNodePtr expression;

    explicit GroupNode(ASTNodePtr expression);

    MatchResult evaluate(size_t &index, const std::string &text) override;
};

#endif //DT096G_REGEX_PARSER_AST_NODE_H
