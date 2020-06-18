/**
 * @file utils.h
 * @brief Utilities
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef UTILS_H__
#define UTILS_H__

#define container_of(ptr, type, member)                                                            \
  ({                                                                                               \
    const typeof(((type *)0)->member) *__mptr = (ptr);                                             \
    (type *)((char *)__mptr - offsetof(type, member));                                             \
  })

#endif /* !UTILS_H__ */
