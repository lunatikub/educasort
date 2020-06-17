/**
 * @file parser.h
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_PARSER_H__
#define EDUCASORT_PARSER_H__

#include <stdbool.h>
#include <stddef.h>

#include <educasort/parser/ast.h>

/**
 * Parse a sort alogrithm.
 *
 * @param ast Abstract syntax tree output.
 * @param sort Sort algorithm to parse.
 * @param len Lenght of the sort algorithm.
 *
 * @return true if the parsing succeed, otherwise false.
 */
bool parse(struct ast *ast, const char *sort, size_t len);

#endif /* !EDUCASORT_PARSER_H__ */
