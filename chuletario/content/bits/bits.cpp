#include <bitset>

bs.set(/*pos, val = true*/);	// Set bit at pos to val. Si no pones pos ni val se pone todo a 1.
bs.reset(/*pos*/);		        // Reset bit at pos to 0 .
bs.all();		                // Return whether all bits are set.
bs.test(pos);	                // Return value of bit at pos.
bs.to_ullong();		            // Return unsigned long long.

// Mascaras de bits
#define isOn(S, j) (S & (1 << j))
#define setBit(S, j) (S |= (1 << j))
#define clearBit(S, j) (S &= ~(1 << j))
#define toggleBit(S, j) (S ^= (1 << j))
#define lowOne(S) (S & (-S))
#define lowZero(S) ~S & (S+1)
#define setLowZero(S) S | (S+1)
#define setAll(S, n) (S = (1 << n) - 1)

// Mascaras de 64 bits
// Hay que poner LL.	 ej. (1LL << n) 
S &= ~(1LL << k) // Clear bit k version 64bits
S & (1LL << k)) // Check if bit k is on version 64bits

// Una mascara con los N bits menos significativos a 1
~(~(0LL) << N)

// Tu error esta aqui
if (x & (1 << i) == 0) { } // esta mal, tiene precedencia ==
(1ULL << n) // shiftea 1 n veces (si no pones ULL no puedes shiftearlo mas de 32 bits y te dara cero)

// Devuelve n con su msb puesto a cero. n es un entero de 32 bits sin signo.
uint clear_msb(uint n) {
    uint mask = n;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;
    mask = mask >> 1;

    return n & mask;
}

// Funciones guay en g++.

// Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined (el MSB lo puedes sacar haciendo 32 - __builtin_clz(x), si x != 0).
int __builtin_clz (unsigned int x);

// Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
int __builtin_ctz (unsigned int x);

// Devuelve el numero de bits a uno en un long long.
__builtin_popcountll(n)

// Al realizar la operacion complemento a 2 con el numero i obtienes -i
i & (-i) // Te da todo ceros, salvo un uno en el bit a 1 menos significativo de i
