/* 
 * CS:APP Data Lab 
 * 
 * Gao Ning   github ID:Jacky-Ning-yyqz   St ID:25303050027 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x >> 31;
  return mask & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int s = src << 3;                    /* src * 8，用左移代替乘法 */
  int d = dst << 3;
  int byte = (x >> s) & 0xFF;          /* 取出 src 字节 */
  int clearMask = ~(0xFF << d);        /* dst 字节位置清零掩码 */
  return (x & clearMask) | (byte << d);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int m = (1 << 31) >> n << 1;   /* 高 n 位全 1 */
  return (x >> n) & ~m;          /* 擦掉算术右移补进来的符号位 */
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int t = 0x0F | (0x0F << 8);
  int lo = t | (t << 16);
  return ((x & lo) << 4) | ((x >> 4) & lo);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int z1 = (~x) & (x + 1);
  int x2 = x | z1;
  return (~x2) & (x2 + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int m  = n & 31;                        /* n mod 32 */
  int hi = (1 << 31) >> m << 1;           /* 高 m 位全 1 */
  int lo = (x >> m) & ~hi;                /* 逻辑右移 m 位 */
  int up = x << ((~m + 1) & 31);          /* 低 m 位挪到高位 */
  return lo | up;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half = 1 << (n + ~0);                    /* 2^(n-1)，用 n+(-1) 避开减号 */
  int q    = x >> n;
  return ((x + half + ~0 + (q & 1)) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int d     = x + ~y + 1;                    /* x - y（可能回绕） */
  int s     = (x ^ y) >> 31;                 /* 同号→0，异号→-1 */
  int lt    = ((d >> 31) & ~s) | ((x >> 31) & s);  /* x<y ? -1 : 0 */
  int ge    = lt + 1;                        /* x>=y ? 1 : 0 */
  int bias  = (x ^ y) & 1;                   /* x+y 奇数 ? 1 : 0 */
  int fl    = (x & y) + ((x ^ y) >> 1);      /* floor((x+y)/2) */
  return fl + (bias & ge);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int d1 = x + ~a + 1;                          /* x - a */
  int d2 = x + ~b + 1;                          /* x - b */
  int s1 = (x ^ a) >> 31;
  int s2 = (x ^ b) >> 31;
  int la = ((d1 >> 31) & ~s1) | ((x >> 31) & s1);   /* x < a ? -1 : 0 */
  int lb = ((d2 >> 31) & ~s2) | ((x >> 31) & s2);   /* x < b ? -1 : 0 */
  return ((la ^ lb) & 1) | (!d1) | (!d2);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4  = x << 2;                         /* 4x */
  int r   = x4 + x;                         /* 5x（可能回绕） */
  int o4  = (x4 >> 2) ^ x;                  /* 非零 ⟺ 4x 溢出 */
  int oa  = ((x4 ^ r) & (x ^ r)) >> 31;     /* -1 ⟺ 加法溢出 */
  int ovf = ((!o4) + ~0) | oa;              /* ← 这里改了 */
  int sat = (1 << 31) ^ ~(x >> 31);         /* 饱和值 */
  return r ^ ((r ^ sat) & ovf);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int c1 = ((x & y) | ((x | y) & ~s1)) >> 31;      /* x+y 的进位 */
  int s2 = s1 + z;
  int c2 = ((s1 & z) | ((s1 | z) & ~s2)) >> 31;    /* (x+y)+z 的进位 */

  int carry  = ~(c1 + c2) + 1;                     /* 进位总数 */
  int negSum = (x >> 31) + (y >> 31) + (z >> 31);
  int negCnt = ~negSum + 1;                        /* 负数个数 */
  int signAdj = (s2 >> 31) & 1;                    /* s<0 ? 1 : 0 */

  return carry + ~negCnt + 1 + signAdj;            /* k */
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  int E = (uf >> 23) & 0xFF;              /* 隐式转换，不是 cast */
  int F = uf & 0x7FFFFF;
  int sign = uf & 0x80000000;
  int M, X, M2, e, sh, rb, st;

  if (E == 0xFF) return uf;                    /* NaN / ±Inf */
  if (E == 0 && F == 0) return uf;             /* ±0 */

  if (E == 0) {                                /* 非规格化 → 规格化 */
    e = -126;
    M = F;
    while ((M & 0x800000) == 0) { M <<= 1; e--; }
  } else {
    e = E - 127;                               /* ← 这里原本是 (int)E */
    M = F | 0x800000;
  }

  X = M * 3;
  if (X >= 0x2000000) { sh = 2; st = X & 1; }  /* 用 if 代替三目，更保险 */
  else                { sh = 1; st = 0; }
  rb = (X >> (sh - 1)) & 1;
  M2 = X >> sh;
  e = e + sh - 1;

  if (rb && (st || (M2 & 1))) M2++;
  if (M2 >= 0x1000000) { M2 >>= 1; e++; }

  if (e > 127) return sign | 0x7F800000;       /* 上溢 → ±Inf */
  if (e >= -126) return sign | ((e + 127) << 23) | (M2 & 0x7FFFFF);
                                               /* ↑ 这里原本是 (unsigned)(e+127) */

  sh = -126 - e;                               /* 下溢到非规格化 */
  rb = (M2 >> (sh - 1)) & 1;
  st = (M2 & ((1 << (sh - 1)) - 1)) != 0;
  M2 = M2 >> sh;
  if (rb && (st || (M2 & 1))) M2++;
  return sign | M2;
}
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  int E = (uf >> 23) & 0xFF;
  int F = uf & 0x7FFFFF;
  int sign = uf & 0x80000000;
  int M, ip, rest, half, e, sh;

  if (E == 0xFF) return uf;                    /* NaN / Inf */

  if (E < 127) {                               /* |f| < 1 */
    if (E < 126) return sign;                  /* |f| < 0.5 → ±0 */
    if (F == 0)  return sign;                  /* 恰好 ±0.5 → 取偶得 ±0 */
    return sign | 0x3F800000;                  /* → ±1.0 */
  }

  e = E - 127;                                 /* ← 原本是 (int)E */
  if (e >= 23) return uf;                      /* 已是整数 */

  M    = F | 0x800000;
  sh   = 23 - e;
  ip   = M >> sh;
  rest = M & ((1 << sh) - 1);
  half = 1 << (sh - 1);

  if (rest > half || (rest == half && (ip & 1))) ip++;

  if (ip >> (e + 1))                           /* 进位到 2^(e+1) */
    return sign | ((e + 128) << 23);           /* e+1+127 = e+128 */
  return sign | ((e + 127) << 23) | ((ip - (1 << e)) << sh);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned u, sign, mag, M;
  int e, sh;
  unsigned rest, half;

  if (x == 0) return 0;
  u = x;
  if (x < 0) { sign = 0x80000000u; mag = -u; }   /* 用无符号取负，INT_MIN 也正确 */
  else       { sign = 0u;          mag = u;  }

  e = 31;
  while ((mag >> e) == 0u) e--;                  /* e = 最高位位置 */

  if (e <= 23) {
    M = mag << (23 - e);                          /* 直接左移补零 */
  } else {
    sh   = e - 23;
    M    = mag >> sh;
    rest = mag & ((1u << sh) - 1u);               /* 被丢弃的位 */
    half = 1u << (sh - 1);
    if (rest > half || (rest == half && (M & 1u))) M++;   /* round-to-even */
  }
  if (M >= 0x1000000u) { M >>= 1; e++; }          /* 舍入进位 */
  return sign | ((e + 127) << 23) | (M & 0x7FFFFFu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1, m2, m4;
  m1 = 0x55 | (0x55 << 8);        /* 0x5555 */
  m1 = m1 | (m1 << 16);           /* 0x55555555 */
  m2 = 0x33 | (0x33 << 8);        /* 0x3333 */
  m2 = m2 | (m2 << 16);           /* 0x33333333 */
  m4 = 0x0F | (0x0F << 8);        /* 0x0F0F */
  m4 = m4 | (m4 << 16);           /* 0x0F0F0F0F */

  x = (x & m1) + ((x >> 1) & m1);   /* 2 位计数 */
  x = (x & m2) + ((x >> 2) & m2);   /* 4 位计数 */
  x = (x + (x >> 4)) & m4;          /* 8 位计数 */
  x = x + (x >> 8);                 /* 16 位 */
  x = x + (x >> 16);                /* 32 位 */
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask = 0xFF | (0xFF << 8);              /* 0x0000FFFF */
  x = ((x >> 16) & mask) | (x << 16);         /* 半字交换 */

  mask = mask ^ (mask << 8);                  /* 0x00FF00FF */
  x = ((x >> 8) & mask) | ((x & mask) << 8);  /* 字节交换 */

  mask = mask ^ (mask << 4);                  /* 0x0F0F0F0F */
  x = ((x >> 4) & mask) | ((x & mask) << 4);  /* 半字节交换 */

  mask = mask ^ (mask << 2);                  /* 0x33333333 */
  x = ((x >> 2) & mask) | ((x & mask) << 2);  /* 位对交换 */

  mask = mask ^ (mask << 1);                  /* 0x55555555 */
  x = ((x >> 1) & mask) | ((x & mask) << 1);  /* 相邻位交换 */

  return x;
}