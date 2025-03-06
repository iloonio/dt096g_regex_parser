//
// Created by Terminal on 04/03/2025.
//

#include <utility>

#include "headers/evaluator.h"

Evaluator::Evaluator(FlagNode root, std::string text) : caseInsensitiveFlag(root.caseInsensitive),
                                                        root(std::move(root)),
                                                        text(std::move(text)),
                                                        result("", false) {
}

MatchResult Evaluator::EvaluateTree() {
    size_t index = 0;
    resetMatchResult();
    while (index < text.size() || !result.exit) {
        result = root.evaluate(index, text, caseInsensitiveFlag);
    }
    return result;
}

void Evaluator::resetMatchResult() {
    result = {"", false};
}
