//
// Created by Terminal on 05/02/2025.
//

#include "headers/ast_node.h"


// ReSharper disable once CppParameterMayBeConst
CharNode::CharNode(char c): c(c) {
}

DotNode::DotNode() = default;

ORNode::ORNode(ASTNodePtr lhs, ASTNodePtr rhs) : left(std::move(lhs)), right(std::move(rhs)) {
}

ConcatNode::ConcatNode() = default;

GroupNode::GroupNode(ASTNodePtr expression) : expression(std::move(expression)) {
}

CountNode::CountNode(ASTNodePtr atom, const int count) : atom(std::move(atom)), count(count) {
}

KleeneNode::KleeneNode(ASTNodePtr atom) : atom(std::move(atom)) {
}

/**
 * @brief Moves forward index and evaluates if the current index matches the character inside this CharNode.
 * @param index current index
 * @param text text whose index will be checked
 * @return MatchResult containing matched char and a true statement (no char and false if no match was found)
 */
MatchResult CharNode::evaluate(size_t &index, const std::string &text) {
    const char ch = text[index];
    index++;
    if (ch == this->c) {
        return {std::string(1, ch), true};
    }
    return {"", false};
}


MatchResult DotNode::evaluate(size_t &index, const std::string &text) {
    MatchResult result = {"", false};
    const char c = text[index];

    if (index < text.size()) {
        result = {std::string(1, c), true};
    }

    index++;
    return result;
}


MatchResult ORNode::evaluate(size_t &index, const std::string &text) {
    size_t rhsIndex = index; //stores an instance of index before a call chain has been invoked

    MatchResult lhs = left->evaluate(index, text);
    if (lhs.exit == false) {
        return right->evaluate(rhsIndex, text);
    }

    return lhs;
}


MatchResult ConcatNode::evaluate(size_t &index, const std::string &text) {
    std::string concatenation{};

    for (const ASTNodePtr &node: children) {
        //Unique Pointers cannot be copied, only moved. We pass by ref
        if (MatchResult eval = node->evaluate(index, text); eval.exit == false) {
            return eval; //returns {"", false}
        } else {
            concatenation += eval.match;
        }
    }

    return {concatenation, true};
}


MatchResult KleeneNode::evaluate(size_t &index, const std::string &text) {
    std::string concatenation;
    MatchResult eval = atom->evaluate(index, text);
    if (eval.exit == false) {
        return eval;
    }
    concatenation += eval.match;
    while (eval.exit == true) {
        eval = atom->evaluate(index, text);
        concatenation += eval.match;
    }
    index--;
    //Returns index to previous value after failed match. This is because Chars and Dots move the index forward.
    return {concatenation, true};
}


MatchResult CountNode::evaluate(size_t &index, const std::string &text) {
    std::string concatenation;
    MatchResult eval = {"", false};

    for (int i = 0; i < count; i++) {
        eval = atom->evaluate(index, text);
        if (eval.exit == false) {
            return eval;
        }
        concatenation += eval.match;
    }
    return {concatenation, true};
}



MatchResult GroupNode::evaluate(size_t &index, const std::string &text) {
    return expression->evaluate(index, text);
}
