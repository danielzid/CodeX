# CodeX

## Overview

CodeX is an experimental text encryption system written in C. It transforms text using prime factorization exponent vectors and applies a Pi digit keystream shift to produce reversible encoded output.

The project explores number theory concepts, structured data representation, and custom encoding pipelines.

> This project is for educational exploration and is not intended for real world cryptographic security.

---

## Features

* Prime factorization based encoding of ASCII characters
* Exponent vector representation stored in compact token format
* Pi digit keystream shift applied to encoded data
* Fully reversible encryption and decryption
* Implemented in pure ANSI C

---

## How It Works

Text → ASCII → Prime Factorization → Exponent Token Format → Pi Digit Shift → Ciphertext

Decryption reverses the pipeline:

Ciphertext → Reverse Pi Shift → Parse Tokens → Reconstruct Prime Products → Characters

---

## Build & Run

Compile:

```
gcc codex.c -o codex -lm
```

Run:

```
./codex
```

Enter text to encrypt.
Input strings starting with `!!` will be decrypted automatically.

Type `quit` to exit.

---

## Example

### Example 1

Input:

```
Test
```

Output:

```
!!52c23:a;=1)g;<74a6>2*a824b=13f>8.&:g</:f687'
```

---

### Example 2

Input:

```
Hello, World!
```

Output:

```
!!63c757&e7839h:?1&5;c<24(56g925-d109g=/:f667';h656`5<6&5h=57(d:04_:65e782'b913fB31a=82%:8`;74h>75)33d912%7h347b:A7+h404g643e9:1,
```

---

### Example 3

Input:

```
!!52c23:a;=1);h;74a8>2*a72449b7?7)_469c678`;<1->b=6/$d901:8c><3-a5.4g943e961,8a=:3$a:<22h:84-8h?45)`234`9/6h793'd:>5:b596(e346b564a<@3$39g9/:f6:7'h;856`3;6&2h?2:c:;0'5b>54&e6;19b5:7)_369c578`;>1-h556`534`943-a834d=78h851,c8645b6?1&f;;.3g;9/-f3;74h<95)
```

Output:

```
This is a secret m3ssage
```

---

## Project Structure

```
CodeX/
 ├── codex.c
 ├── README.md
```

---

## License

Free to use for learning and experimentation.
