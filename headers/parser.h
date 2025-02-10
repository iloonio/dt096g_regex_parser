//
// Created by Terminal on 05/02/2025.
//

#ifndef DT096G_REGEX_PARSER_PARSER_H
#define DT096G_REGEX_PARSER_PARSER_H
/**
 * Parse Tree:
First, create a parse tree that describes the pattern in grammatical terms.
Your runtime will then take the parse tree and go through the entire input to see if any part of the input matches the pattern.
The parse tree can benefit from polymorphism, where an abstract base could be structured as:

struct ASTNode {
  virtual EvalResult evaluate() = 0;
  std::vector<ASTNode*> operands;
};

 */

class parser {

};


#endif //DT096G_REGEX_PARSER_PARSER_H
