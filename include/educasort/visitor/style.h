/**
 * @file style.h
 * @brief Coding style visitor.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef VISITOR_STYLE_H__
#define VISITOR_STYLE_H__

struct visitor_style {
  struct visitor visitor;
  int indent;
};

/**
 * Initialize visitor coding style.
 */
void visitor_style_init(struct visitor_style *v);

#endif /* !VISITOR_STYLE_H__ */
