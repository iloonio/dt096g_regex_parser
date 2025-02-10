cmake_minimum_required(VERSION 3.25)
project(dt096g_regex_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(dt096g_regex_parser main.cpp lexer.cpp headers/lexer.h parser.cpp headers/parser.h Evaluator.cpp headers/Evaluator.h ast_node.cpp headers/ast_node.h)
