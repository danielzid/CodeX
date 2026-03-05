# CodeX

## Overview

CodeX is an experimental encryption system implemented in C that combines prime factorization, structured token encoding, and a Pi digit based shift to generate reversible encoded output.

The project demonstrates how mathematical transformations can be applied to text processing through custom encoding pipelines.

> This project is built for educational exploration and is not intended for production level cryptographic security.

---

## Features

* Prime factorization based encoding of ASCII characters
* Prime index mapping with exponent vector representation
* Compact token formatting for structured storage
* Pi digit keystream shift applied to encoded data
* Fully reversible encryption and decryption
* Implemented in pure ANSI C

---

## How It Works

Text → ASCII Conversion → Prime Factorization → Prime Index Encoding → Token Formatting → Pi Digit Shift → Ciphertext

Decryption reverses each transformation:

Ciphertext → Reverse Pi Shift → Token Parsing → Prime Reconstruction → Character Recovery

The system encodes each character as a product of prime powers, compresses zero exponent sequences, and then applies a deterministic shift based on digits of Pi to obfuscate the token stream.

---

## Performance

The program performs prime factorization using a fixed prime list and processes tokens sequentially during encryption and decryption.

Runtime increases with input size because each character requires factor decomposition. Output size is larger than the original text since factor data and shift transformations are stored explicitly.

The design prioritizes mathematical correctness and reversibility over speed or compression efficiency. It performs well for small and medium inputs but is not optimized for large scale processing.

---

## Build & Run

Compile:

```id="cpl91"
gcc codex.c -o codex -lm
```

Run:

```id="xq82m"
./codex
```

Enter text to encrypt. Input strings beginning with `!!` are automatically decrypted.

Type `quit` to exit.

---

## Example

### Example 1

Input:

```id="e91ks"
Test
```

Output:

```id="lq92x"
!!52c23:a;=1)g;<74a6>2*a824b=13f>8.&:g</:f687'
```

---

### Example 2

Input:

```id="m2z8q"
Hello, World!
```

Output:

```id="p7x4t"
!!63c757&e7839h:?1&5;c<24(56g925-d109g=/:f667';h656`5<6&5h=57(d:04_:65e782'b913fB31a=82%:8`;74h>75)33d912%7h347b:A7+h404g643e9:1,
```

---

### Example 3

Input:

```id="r1k9v"
!!52c23:a;=1);h;74a8>2*a72449b7?7)_469c678`;<1->b=6/$d901:8c><3-a5.4g943e961,8a=:3$a:<22h:84-8h?45)`234`9/6h793'd:5:b596(e346b564a<@3$39g9/:f6:7'h;856`3;6&2h?2:c:;0'5b>54&e6;19b5:7)_369c578`;>1-h556`534`943-a834d=78h851,c8645b6?1&f;;.3g;9/-f3;74h<95)
```

Output:

```id="s4t2n"
This is a secret m3ssage
```

---

## Project Structure

```id="f8x2k"
CodeX/
 ├── codex.c
 ├── README.md
```

---

## License

Free to use for learning and experimentation
