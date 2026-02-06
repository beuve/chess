#include <stdio.h>

#define ASSERT_EQ(ACTUAL, EXPECTED, TEXT)                                      \
  if (EXPECTED != ACTUAL) {                                                    \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, TEXT);                  \
    return 1;                                                                  \
  }

#define ASSERT(EXPR, TEXT)                                                     \
  if (!EXPR) {                                                                 \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, TEXT);                  \
    return 1;                                                                  \
  }
