cmake_minimum_required(VERSION 3.22.1)
project(dt096g_regex_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(match main.cpp lexer.cpp headers/lexer.h parser.cpp headers/parser.h ast_node.cpp headers/ast_node.h
       )
