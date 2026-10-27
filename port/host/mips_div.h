/*
 * Inserted into wasm2c's output after its division macros (port.mk).
 * MIPS divides by zero without a trap, and the game does it: the
 * quotient is -1 (1 for a negative dividend), all ones unsigned, and the
 * remainder is the dividend. INT_MIN / -1 gives INT_MIN.
 */
#define PORT_MIPS_DIV 1
#undef DIV_S
#undef REM_S
#undef DIV_U
#undef REM_U
#define DIV_S(ut, min, x, y)                                       \
  ((UNLIKELY((y) == 0))                  ? (ut)((x) < 0 ? 1 : -1) \
   : (UNLIKELY((x) == min && (y) == -1)) ? (ut)(x)                \
                                         : (ut)((x) / (y)))
#define REM_S(ut, min, x, y)                             \
  ((UNLIKELY((y) == 0))                  ? (ut)(x)       \
   : (UNLIKELY((x) == min && (y) == -1)) ? 0             \
                                         : (ut)((x) % (y)))
#define DIV_U(x, y) ((UNLIKELY((y) == 0)) ? ~((x) ^ (x)) : (x) / (y))
#define REM_U(x, y) ((UNLIKELY((y) == 0)) ? (x) : (x) % (y))
