# TTL4 math and logic examples

Build the project, then assemble and run any example from `ttl4/`, for example:

```sh
cmake -S . -B build
cmake --build build
build/ttl4-as programs/functions.asm
build/ttl4-run programs/functions.bin
```

The emulator prints hexadecimal output nibbles, one per line.

| Source | Example | Expected output |
|---|---|---|
| `programs/logic.asm` | AND, OR, XOR, NOT on 5 and 3 | `1`, `7`, `6`, `A` |
| `programs/calculator.asm` | 7+5, then 7−5 | `C`, `2` |
| `programs/algebra.asm` | y=2x+3 at x=4 | `B` |
| `programs/functions.asm` | f(x)=x² at x=3 using repeated addition | `9` |
| `programs/calculus.asm` | finite difference of x² at x=3 | `7` |
| `programs/input_add.asm` | add runtime input nibbles 3 and 5 | `8` |

These examples use 4-bit unsigned values, so arithmetic wraps modulo 16. The ISA supports queued input through `IN`, but it has no CALL/RET instructions; the function example uses a loop instead. The calculus sample demonstrates a discrete finite difference, not symbolic or floating-point calculus.
