/**
 * @file string.h
 * @brief Manipulate string.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_STRING_H__
#define EDUCASORT_STRING_H__

/** Opaque string structure. **/
typedef struct string string_t;

/**
 * Create a string.
 *
 * @param initial_capa Initial length capacity of the string.
 * @return string allocated.
 */
string_t* string_create(size_t initial_capa);

/**
 * Destroy a string.
 *
 * @param String previously allocated with @c string_create.
 */
void string_destroy(string_t *str);

/**
 * Appends the src string to the dst string.
 *
 * @param dst Destination string.
 * @param src Source string.
 */
void string_append(struct string *dst, const char *src);

/**
 * Get the string.
 *
 * @param String previously allocated with @c string_create.
 * @return string
 */
const char* string_get(const struct string *str);

#endif /* !EDUCASORT_STRING_H__ */
