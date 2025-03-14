//
// Created by Terminal on 11/03/2025.
//

#include <utility>

#include "headers/evaluator.h"

#include <iostream>

Evaluator::Evaluator(std::string text, ASTNodePtr root) :   text(std::move(text)),
                                                            root(std::move(root)) {}

void Evaluator::evaluate() {
    size_t index = 0;
    while (match.exit == false and index < text.size()) {
        match = root->evaluate(index, text);
    }
}

void Evaluator::printMatch() const {
    std::cout << std::boolalpha;
    std::cout << match.match << '\n' << match.exit << std::endl;
}
