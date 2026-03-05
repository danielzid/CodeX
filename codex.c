#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define INSIZE   10000
#define PIOFF    100
#define PRIMECNT 62

static int pi_digits[PIOFF] = {
    3, 1, 4, 1, 5, 9, 2, 6, 5, 3,
    5, 8, 9, 7, 9, 3, 2, 3, 8, 4,
    6, 2, 6, 4, 3, 3, 8, 3, 2, 7,
    9, 5, 0, 2, 8, 8, 4, 1, 9, 7,
    1, 6, 9, 3, 9, 9, 3, 7, 5, 1,
    0, 5, 8, 2, 0, 9, 7, 4, 9, 4,
    5, 9, 2, 3, 0, 3, 8, 4, 6, 2,
    6, 4, 3, 3, 8, 3, 2, 7, 9, 5,
    0, 2, 8, 8, 4, 1, 9, 7, 1, 6,
    9, 3, 9, 9, 3, 7, 5, 1, 0, 5
};

static int primes[PRIMECNT] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293
};

int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

// Encode n as prime factorization exponents, appended to output
void primeFactorizationPowers(int n, char *output) {
    int powers[PRIMECNT];
    memset(powers, 0, sizeof(powers));

    for (int i = 0; i < PRIMECNT && n > 1; i++) {
        while (n % primes[i] == 0) {
            powers[i]++;
            n /= primes[i];
        }
    }

    int zeroCount = 0;
    for (int i = 0; i < PRIMECNT; i++) {
        if (powers[i] == 0) {
            zeroCount++;
        } else {
            if (zeroCount > 0) {
                sprintf(output + strlen(output), "_%d.", zeroCount);
                zeroCount = 0;
            }
            sprintf(output + strlen(output), "%d", powers[i]);
        }
    }

    if (zeroCount > 0)
        sprintf(output + strlen(output), "_%d.", zeroCount);

    strcat(output, "$");
}

// Build factorization string then apply Pi-digit shift; result starts with "!!"
void encrypt(const char *input, char *output) {
    char factored[INSIZE] = {0};

    for (int i = 0; i < (int)strlen(input); i++) {
        int c = (unsigned char)input[i];
        if (c > 1) primeFactorizationPowers(c, factored);
    }

    output[0] = '!';
    output[1] = '!';

    int len = (int)strlen(factored);
    for (int i = 0; i < len && i + 2 < INSIZE - 1; i++) {
        output[i + 2] = (char)((int)factored[i] + pi_digits[i % PIOFF]);
    }
    output[len + 2] = '\0';
}

// Reverse Pi-digit shift then reconstruct characters from factorization tokens
void decrypt(const char *input, char *output) {
    char shifted[INSIZE] = {0};
    int len = (int)strlen(input);

    for (int i = 0; i < len; i++) {
        shifted[i] = (char)((int)input[i] - pi_digits[i % PIOFF]);
    }
    shifted[len] = '\0';

    int j = 0;
    char *token = strtok(shifted, "$");

    while (token != NULL) {
        int pindex = 0, total = 1, quit = 0;
        int tlen = (int)strlen(token);

        for (int i = 0; i < tlen && !quit; i++) {
            char c = token[i];

            if (c == '_') {
                if (i + 1 < tlen) {
                    int skip = atoi(&token[i + 1]);
                    pindex += skip;
                    i += (skip >= 10) ? 3 : 2; // advance past digits and '.'
                }
            } else if (c == '.') {
                // separator, skip
            } else if (isdigit((unsigned char)c)) {
                if (pindex >= PRIMECNT) { quit = 1; break; }
                total *= int_pow(primes[pindex++], c - '0');

                if (total > 31 && total < 127 && j < INSIZE - 1)
                    output[j++] = (char)total;
            }
        }

        token = strtok(NULL, "$");
    }

    output[j] = '\0';
}

int main() {
    printf("\t\tENCRYPTER | DECRYPTER\n");

    char input[INSIZE];
    char result[INSIZE];

    while (1) {
        printf("Input ('quit' to exit) > ");

        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0 || input[0] == '\0') break;

        memset(result, 0, sizeof(result));

        if (input[0] == '!' && input[1] == '!') {
            decrypt(input + 2, result);
        } else {
            encrypt(input, result);
        }

        printf("\nOutput> %s\n\n", result);
    }

    printf("Program terminated.\n");
    return 0;
}