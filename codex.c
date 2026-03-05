#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INSIZE   10000
#define PIOFF    100
#define PRIMECNT 62

// first 100 digits of pi, used to scramble the output
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

// primes used to factor each character's ASCII value
static int primes[PRIMECNT] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293
};

// raises base to the power of exp
int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

// writes an integer into buf at the current position
static void write_int(char *buf, int *pos, int n) {
    int written = sprintf(buf + *pos, "%d", n);
    *pos += written;
}

// breaks n into prime factors and writes the exponents as a string
// zeros get compressed into "_N." ends with $
void primeFactorizationPowers(int n, char *output, int *outpos) {
    int powers[PRIMECNT] = {0};

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
                output[(*outpos)++] = '_';
                write_int(output, outpos, zeroCount);
                output[(*outpos)++] = '.';
                zeroCount = 0;
            }
            write_int(output, outpos, powers[i]);
        }
    }

    if (zeroCount > 0) {
        output[(*outpos)++] = '_';
        write_int(output, outpos, zeroCount);
        output[(*outpos)++] = '.';
    }

    output[(*outpos)++] = '$';
}

// converts each character to its factorization string, then shifts
// every byte by a pi digit to scramble it, prefixes result with !!
void encrypt(const char *input, char *output) {
    char factored[INSIZE];
    int  fpos = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        int c = (unsigned char)input[i];
        if (c > 1) primeFactorizationPowers(c, factored, &fpos);
    }
    factored[fpos] = '\0';

    // mark as encrypted
    output[0] = '!'; 
    output[1] = '!';

    int limit = (fpos + 2 < INSIZE - 1) ? fpos : INSIZE - 3;
    for (int i = 0; i < limit; i++) {
        output[i + 2] = (char)((int)factored[i] + pi_digits[i % PIOFF]);
    }
    output[limit + 2] = '\0';
}

// undoes the pi shift, then parses the factorization tokens back into characters
void decrypt(const char *input, char *output) {
    char shifted[INSIZE];
    int  len = 0;

    while (input[len] != '\0' && len < INSIZE - 1) {
        shifted[len] = (char)((int)input[len] - pi_digits[len % PIOFF]);
        len++;
    }
    shifted[len] = '\0';

    int j   = 0;
    int pos = 0;

    while (pos < len) {
        int pindex = 0;
        int total  = 1;
        int quit   = 0;

        while (pos < len && !quit) {
            char c = shifted[pos];

            if (c == '$') { pos++; break; }

            if (c == '_') {
                pos++;
                int skip = 0;
                while (isdigit((unsigned char)shifted[pos])) {
                    skip = skip * 10 + (shifted[pos] - '0');
                    pos++;
                }
                if (shifted[pos] == '.') pos++;
                pindex += skip; // jump over primes that had exponent 0
            } else if (c == '.') {
                pos++;
            } else if (isdigit((unsigned char)c)) {
                if (pindex >= PRIMECNT) { quit = 1; break; }
                total *= int_pow(primes[pindex++], c - '0');
                if (total > 31 && total < 127 && j < INSIZE - 1)
                    output[j++] = (char)total;
                pos++;
            } else {
                pos++;
            }
        }
    }

    output[j] = '\0';
}

// reads a line, encrypts or decrypts based on !! prefix, loops until quit
int main() {
    printf("\t\tENCRYPTER | DECRYPTER\n");

    char input[INSIZE];
    char result[INSIZE];

    while (1) {
        printf("Input ('quit' to exit) > ");

        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0 || input[0] == '\0') break;

        result[0] = '\0';

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