# Cryptonite — SHA-256 Implementation in C

A minimal, modular implementation of the SHA-256 cryptographic hash function in C. This is part of the **Cryptonite** library, designed for learning and lightweight cryptographic use cases.

## 📦 Features

- Clean and readable SHA-256 implementation
- Follows the FIPS 180-4 standard
- Padding, message scheduling, and compression implemented step-by-step
- Test file provided for easy verification

## 🗂️ Project Structure

```
.
├── Makefile              # For building the project
├── README.md             # This file
├── include/
│   └── cryptonite/
│       └── hash.h        # SHA-256 function declarations
├── src/
│   └── sha256.c          # SHA-256 implementation
│   └── sha256_internal.h # Internal constants/macros
├── tests/
│   └── test_sha256.c     # Test file
```

## 🛠️ Build Instructions

### 🔧 Prerequisites

- GCC or Clang
- Make (optional but recommended)

### 💡 Build using `gcc` (manual):

```bash
gcc -Wall -Wextra -o test_sha256 tests/test_sha256.c src/sha256.c -Iinclude
```

### 📦 Build using `make`:

Make sure your `Makefile` is present. Then simply run:

```bash
make
```

## 🚀 Usage

### Run the test:

```bash
./test_sha256
```

You should see:

```
Input: abc
SHA-256: ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
```

This matches the known correct hash of `"abc"`.

## 📚 References

- [FIPS PUB 180-4](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf) — Secure Hash Standard
- [Wikipedia: SHA-2](https://en.wikipedia.org/wiki/SHA-2)

## 🧠 Educational Use

This project is built for educational purposes and low-level cryptographic understanding. For production-grade security, use a vetted library like OpenSSL or libsodium.

## 📝 License

MIT License — see `LICENSE` file (if added).