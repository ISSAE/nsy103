#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* The type of a single-character operators is the character, so
 * other token types need to start at 256. We use 0 to indicate
 * the end of input token type.
 */
enum TokenType { NUMBER = 256, ID };
typedef struct Token {
  enum TokenType token_type;
  union { /* Anonymous unions are a C11 feature. */
    long      number;  /* Only valid if type is NUMBER */
    char*     id;      /* Only valid if type is ID */
  }; 
} Token;

/* You would normally call this like this:
 * do {
 *   s = next_token(s, &token);
 *   // Do something with token
 * } while (token.token_type);
 */
const char* next_token(const char* input, Token* out) {
  /* Skip whitespace */
  while (isspace(*input)) ++input;
  if (isdigit(*input)) {
    char* lim;
    out->number = strtol(input, &lim, 10);
    out->token_type = NUMBER;
    return lim;
  } else if (isalpha(*input)) {
    const char* lim = input + 1;
    /* Find the end of the id */
    while (isalnum(*lim)) ++lim;
    /* Allocate enough memory to copy the id. We need one extra byte
     * for the NUL
     */
    size_t len = lim - input;
    out->id = malloc(len + 1);
    memcpy(out->id, input, len);
    out->id[len] = 0;  /* NUL-terminate the string */
    out->token_type = ID;
    return lim;
  } else {
    out->token_type = *input;
    /* If we hit the end of the input string, we don't advance the
     * input pointer, to avoid reading random memory.
     */
    return *input ? input + 1 : input;
  }
}
