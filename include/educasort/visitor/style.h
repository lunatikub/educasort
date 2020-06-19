/**
 * @file style.h
 * @brief Coding style visitor.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef VISITOR_STYLE_H__
#define VISITOR_STYLE_H__

#include <educasort/utils/string.h>

struct visitor_style {
  struct visitor visitor;
  int indent;
  string_t *algo;
  bool first_vardec;
};

/**
 * Initialize visitor coding style.
 *
 * @param v Style visitor.
 */
void visitor_style_init(struct visitor_style *v);

/**
 * Clean visitor coding style.
 *
 * @param v Style visitor.
 */
void visitor_style_clean(struct visitor_style *v);

#endif /* !VISITOR_STYLE_H__ */
