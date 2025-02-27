//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_EVALUATOR_H
#define DT096G_REGEX_PARSER_EVALUATOR_H

/**
 * This will contain the text file we apply our regex on.
 *
 * Based on some experiments on regex101, i have an idea of how the evaluator should work:
 * for a regex term to be evaluated, the term that preceded it must have returned some sort of match.
 * We return a match if and only if every term in the regex pattern managed to returned something.
 * left-to-right priority: this means that for the binary OR operand, we check lhs and then rhs.
 * we traverse the tree almost DFS style, going from left to right.
 */
class Evaluator {

};


#endif //DT096G_REGEX_PARSER_EVALUATOR_H
