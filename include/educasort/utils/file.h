/**
 * @file file.h
 * @brief Manipulate file.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_FILE_H__
#define EDUCASORT_FILE_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * Reading an entire file into memory.
 *
 * @param file_path Path of the file to read.
 * @param len Length read.
 * @return return the buffer read if succeed, NULL otherwise.
 */
char *filetobuf(const char *file_path, size_t *len);

/**
 * Writing a buffer into a file.
 *
 * @param file_path Path of the file to write.
 * @param buf Buffer to write.
 * @param len Length of the buffer.
 * @return True if succeeded, otherwise false.
 */
bool buftofile(const char *file_path, const char *buf, size_t len);

#endif /* !EDUCASORT_FILE_H__ */
