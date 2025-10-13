#include "s21_string.h"

#define BUFF_SIZE 128

#if defined(__linux__)
#define S21_ERRLIST_SIZE 134
#elif defined(__APPLE__)
#define S21_ERRLIST_SIZE 107
#endif

#include <stdio.h>

#include "s21_string.h"

#define S21_ERRLIST_SIZE 134  // количество ошибок (для Linux; для macOS другое)
#define MAX_UNKNOWN_ERROR_LEN 64

#if __linux__
// -------------------------
// Таблица ошибок для Linux
// -------------------------
static const char *s21_error_list[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#elif __APPLE__
// -------------------------
// Таблица ошибок для macOS
// -------------------------
static const char *s21_error_list[] = {"Undefined error: 0",
                                       "Operation not permitted",
                                       "No such file or directory",
                                       "No such process",
                                       "Interrupted system call",
                                       "Input/output error",
                                       "Device not configured",
                                       "Argument list too long",
                                       "Exec format error",
                                       "Bad file descriptor",
                                       "No child processes",
                                       "Resource deadlock avoided",
                                       "Cannot allocate memory",
                                       "Permission denied",
                                       "Bad address",
                                       "Block device required",
                                       "Resource busy",
                                       "File exists",
                                       "Cross-device link",
                                       "Operation not supported by device",
                                       "Not a directory",
                                       "Is a directory",
                                       "Invalid argument",
                                       "Too many open files in system",
                                       "Too many open files",
                                       "Inappropriate ioctl for device",
                                       "Text file busy",
                                       "File too large",
                                       "No space left on device",
                                       "Illegal seek",
                                       "Read-only file system",
                                       "Too many links",
                                       "Broken pipe"};
#endif

char *s21_strerror(int errnum) {
  static char unknown_error[MAX_UNKNOWN_ERROR_LEN];
  static char *result = s21_NULL;

#if __linux__
  int max = sizeof(s21_error_list) / sizeof(s21_error_list[0]);
#elif __APPLE__
  int max = sizeof(s21_error_list) / sizeof(s21_error_list[0]);
#endif

  if (errnum >= 0 && errnum < max) {
    result = (char *)s21_error_list[errnum];
  } else {
    snprintf(unknown_error, MAX_UNKNOWN_ERROR_LEN, "Unknown error: %d", errnum);
    result = unknown_error;
  }

  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  void *result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == uc) {
      result = (void *)(p + i);
      i = n;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      result = p1[i] - p2[i];
      i = n;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t j = 0;

  while (dest[i] != '\0') {
    i++;
  }

  while (j < n && src[j] != '\0') {
    dest[i] = src[j];
    i++;
    j++;
  }

  dest[i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;

  while (*str) {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
    str++;
  }

  if (c == '\0') {
    result = (char *)str;  // указывает на '\0'
  }

  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 != c2 || c1 == '\0' || c2 == '\0') {
      return c1 - c2;
    }
  }
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (src != s21_NULL) {
    int i = 0;
    for (; *src && n > 0; src++, i++) {
      dest[i] = *src;
      n--;
    }
    if (n > 0) dest[i] = '\0';
  } else
    dest = s21_NULL;
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1 = s21_NULL, *p2 = s21_NULL;
  s21_size_t count = 0;
  int found = 0;
  for (p1 = str1; *p1 != '\0' && !found; p1++) {
    for (p2 = str2; *p2 != '\0' && !found; p2++) {
      if (*p1 == *p2) {
        found = 1;
      }
    }
    if (!found) {
      count++;
    }
  }
  return count;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str && str[len] != '\0') {
    len++;
  }
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *p1 = s21_NULL, *p2 = s21_NULL;
  int found = 0;
  char *rezult = s21_NULL;
  for (p1 = str1; *p1 != '\0' && !found; p1++) {
    for (p2 = str2; *p2 != '\0' && !found; p2++) {
      if (*p1 == *p2) {
        found = 1;
        rezult = (char *)p1;
      }
    }
  }

  return rezult;
}

char *s21_strrchr(const char *s, int c) {
  const char *last = s21_NULL;

  while (*s != '\0') {
    if (*s == (char)c) {
      last = s;
    }
    s++;
  }

  if (c == '\0') {
    return (char *)s;
  }

  return (char *)last;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    for (const char *h = haystack; *h && result == s21_NULL; h++) {
      const char *h_it = h;
      const char *n_it = needle;

      while (*h_it && *n_it && (*h_it == *n_it)) {
        h_it++;
        n_it++;
      }

      if (*n_it == '\0') {
        result = (char *)h;
      }
    }
  }

  return result;
}

s21_size_t s21_strspn(const char *str, const char *accept) {
  s21_size_t count = 0;

  for (; *str; str++) {
    const char *a = accept;
    int found = 0;
    while (*a) {
      if (*str == *a) {
        found = 1;
        break;
      }
      a++;
    }
    if (!found) break;
    count++;
  }

  return count;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = s21_NULL;

  if (str == s21_NULL && next_token == s21_NULL) return s21_NULL;
  if (str != s21_NULL) next_token = str;

  // Пропускаем все начальные разделители
  next_token += s21_strspn(next_token, delim);
  if (*next_token == '\0') {  // Строка закончилась
    next_token = s21_NULL;
    return s21_NULL;
  }

  char *token_start = next_token;

  // Находим конец токена
  char *delim_pos = s21_strpbrk(token_start, delim);
  if (delim_pos) {
    *delim_pos = '\0';
    next_token = delim_pos + 1;
  } else {
    next_token = s21_NULL;
  }

  return token_start;
}

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc((len + 1) * sizeof(char));

  if (result == s21_NULL) return s21_NULL;

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z')
      result[i] = str[i] - 32;  // Преобразуем вручную
    else
      result[i] = str[i];
  }

  result[len] = '\0';
  return (void *)result;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc((len + 1) * sizeof(char));

  if (result == s21_NULL) return s21_NULL;

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      result[i] = str[i] + ('a' - 'A');
    else
      result[i] = str[i];
  }
  result[len] = '\0';
  return (void *)result;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) return s21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  // Проверяем, что индекс не выходит за пределы исходной строки
  if (start_index > src_len) return s21_NULL;

  // Выделяем память под новую строку
  char *result = (char *)malloc(src_len + str_len + 1);
  if (result == s21_NULL) return s21_NULL;

  // Копируем часть до start_index
  for (s21_size_t i = 0; i < start_index; i++) {
    result[i] = src[i];
  }

  // Вставляем строку str
  for (s21_size_t j = 0; j < str_len; j++) {
    result[start_index + j] = str[j];
  }

  // Копируем оставшуюся часть src
  for (s21_size_t k = start_index; k < src_len; k++) {
    result[str_len + k] = src[k];
  }

  result[src_len + str_len] = '\0';
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) return s21_NULL;

  if (trim_chars == s21_NULL)
    trim_chars = " \t\n\r\v\f";  // стандартные пробелы

  s21_size_t src_len = s21_strlen(src);
  if (src_len == 0) {
    char *empty = (char *)calloc(1, sizeof(char));
    return empty;
  }

  s21_size_t start = 0;
  s21_size_t end = src_len - 1;

  // Находим индекс первого символа, который не входит в trim_chars
  while (start < src_len && s21_strchr(trim_chars, src[start]) != s21_NULL) {
    start++;
  }

  // Находим индекс последнего символа, который не входит в trim_chars
  while (end > start && s21_strchr(trim_chars, src[end]) != s21_NULL) {
    end--;
  }

  s21_size_t new_len = (start > end) ? 0 : end - start + 1;

  // Выделяем память под обрезанную строку
  char *result = (char *)malloc(new_len + 1);
  if (result == s21_NULL) return s21_NULL;

  for (s21_size_t i = 0; i < new_len; i++) {
    result[i] = src[start + i];
  }
  result[new_len] = '\0';

  return result;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (unsigned char)(*str1) - (unsigned char)(*str2);
}
