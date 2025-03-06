//
// Created by Terminal on 05/02/2025.
//

#include "headers/ast_node.h"


// ReSharper disable once CppParameterMayBeConst
CharNode::CharNode(char c): c(c) {
}


MatchResult CharNode::evaluate(size_t &index, const std::string &text, bool caseInsensitive) {
    const char c = text[index];
    index++;
    if (c == this->c) {
        return {std::string(1, c), true};
    }
    return {"", false};
}

DotNode::DotNode() = default;

MatchResult DotNode::evaluate(size_t &index, const std::string &text, bool caseInsensitive) {
    if (index < text.size()) {
        return {std::string(1, text[index]), true};
    }
    return {"", false};
}


ORNode::ORNode(ASTNodePtr lhs, ASTNodePtr rhs) : left(std::move(lhs)), right(std::move(rhs)) {
}

MatchResult ORNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    size_t rhsIndex = index; //stores an instance of index before a call chain has been invoked

    MatchResult lhs = left->evaluate(index, text, caseInsensitive);
    if (lhs.exit == false) {
        return right->evaluate(rhsIndex, text, caseInsensitive);
    }

    return lhs;
}


ConcatNode::ConcatNode() = default;

MatchResult ConcatNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    std::string concatenation{};

    for (const ASTNodePtr &node: children) {
        //Unique Pointers cannot be copied, only moved. We pass by ref
        if (const MatchResult eval = node->evaluate(index, text, caseInsensitive); eval.exit == false) {
            return eval; //returns {"", false}
        } else {
            concatenation += eval.match;
        }
    }

    return {concatenation, true};
}


KleeneNode::KleeneNode(ASTNodePtr atom) : atom(std::move(atom)) {
}

MatchResult KleeneNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    std::string concatenation;
    MatchResult eval = atom->evaluate(index, text, caseInsensitive);

    while (eval.exit == true) {
        eval = atom->evaluate(index, text, caseInsensitive);
        concatenation += eval.match;
    }

    return eval;
}


CountNode::CountNode(ASTNodePtr atom, const int count) : atom(std::move(atom)), count(count) {
}

MatchResult CountNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    std::string concatenation;
    MatchResult eval = {"", false};

    for (int i = 0; i < count; i++) {
        eval = atom->evaluate(index, text, caseInsensitive);
        if (eval.exit == false) {
            return eval;
        }
        concatenation += eval.match;
    }
    return {concatenation, true};
}


GroupNode::GroupNode(ASTNodePtr expression) : expression(std::move(expression)) {
}

MatchResult GroupNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    return expression->evaluate(index, text, caseInsensitive);
}


FlagNode::FlagNode(const bool caseInsensitive, const int captureCount): caseInsensitive(caseInsensitive),
                                                            captureCount(captureCount) {}

MatchResult FlagNode::evaluate(size_t &index, const std::string &text, const bool caseInsensitive) {
    MatchResult behavior = expression->evaluate(index, text, caseInsensitive);
    //Eval child node x many times, based on our internal captureCount
    for (size_t i = 0; i < captureCount; i++) {
        index = 0;
        behavior = expression->evaluate(index, text, caseInsensitive);
    }
    //the internal case-insensitive flag is managed inside evaluator's constructor.
    return behavior;
}
