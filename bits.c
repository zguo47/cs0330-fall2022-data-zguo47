#if 0
INTEGER CODING RULES:

	Complete the body of each function with one
	or more lines of C code that implements the function. Your code
	must consist of a sequence of variable declarations, followed by
	a sequence of assignment statements, followed by a return statement.

	The general style is as follows:

	int funct(...) {
		/* brief description of how your implementation works */
		int var1 = expr1;
		...
		int varM = exprM;

		varJ = exprJ;
		...
		varN = exprN;

		return exprR;
	}

	Each "expr" is an expression using ONLY the following:
	1. Integer constants 0 through 255 (0xFF), inclusive. You are
	   not allowed to use big constants such as 0xFFFFFFFF.
	2. Function arguments and local variables (no global variables).
	3. Unary integer operations ! ~
	4. Binary integer operations & ^ | + << >>

	Some of the problems restrict the set of allowed operators even further.
	Each "expr" may consist of multiple operators. You are not restricted to
	one operator per line.

	You are expressly forbidden to:
	1. Use any control constructs such as if, do, while, for, switch, etc.
	2. Define or use any macros.
	3. Define any additional functions in this file.
	4. Call any functions.
	5. Use any other operations, such as &&, ||, ==, -, or ?:
	6. Use any form of casting.
	7. Use any data type other than int.  This implies that you
	   cannot use arrays, structs, or unions.


	You may assume that your machine:
	1. Uses 2s complement, 32-bit representations of integers.
	2. Performs right shifts arithmetically.
	3. Has unpredictable behavior when shifting an integer by more
	   than the word size.

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
#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 9.0.0.  Version 9.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, fourth edition, plus
   Amd. 1  and Amd. 2 and 273 characters from forthcoming  10646, fifth edition.
   (Amd. 2 was published 2016-05-01,
   see https://www.iso.org/obp/ui/#iso:std:iso-iec:10646:ed-4:v1:amd:2:v1:en) */
/* We do not support C11 <threads.h>.  */

/*
 * bit_and - Compute x&y using only ~ and |
 *   Examples: bit_and(6, 5) = 4
 *             bit_and(3, 12) = 0
 *   Legal ops: ~ |
 *   Illegal ops: ! & ^ + << >>
 *   Max ops: 8
 *   Points: 2
 */
int bit_and(int x, int y) {
	// We OR NOT x and NOT y, so we set in the result 1s for either NOT x and 
	// NOT y has a 1 there. Then, we NOT the result to get both x and y has a 
	// a 1 there. 
	return ~(~x|~y); 
}

/*
 * negate - Return -x
 *   Examples: negate(1) = -1
 *             negate(0) = 0
 *             negate(-33) = 33
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Points: 4
 */
int negate(int x) {
	// When we add the NOT x and x together, we find that the result is -1,
	// so we add 1 to get the negation of x. 
	return (~x) + 1; 
}

/*
 * is_equal - Return 1 if x == y, else return 0
 *   Examples: is_equal(5, 5) = 1
 *             is_equal(4, 5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Points: 4
 */
int is_equal(int x, int y) {
	// If x and y are the same, x^y should return 0 because there is no 
	// difference. We LOGICAL NOT x^y, so it will return 1 when x^y is 0, and
	// return 0 otherwise.  
	return !(x^y);
}

/*
 * div_pwr_2 - Compute x/(2^n), for 0 <= n <= 30
 *   Round toward zero
 *   Examples: div_pwr_2(15, 1) = 7
 *             div_pwr_2(-33, 4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Points: 4
 */
int div_pwr_2(int x, int n) {
	// When x is negative, we will add n and then minus one so that it will 
	// round up instead of round down; then we shift to right n bits. 
	return (x + ((x >> 31) & ((1 << n) + ~0))) >> n;
}

/*
 * conditional - Compute the result of x ? y : z
 *   Examples: conditional(2, 4, 5) = 4
 *             conditional(0, 1, 2) = 2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Points: 6
 */
int conditional(int x, int y, int z) {
	// when x is not 0, we double LOGICAL NOT x to make it 1, and we NOT it to
	//get -2, and add 1 to get -1, so the left side will keep y and right side 
	// 0. The rightside works the same way, but reverse. 
	return (y & (~(!(!x))+1)) + (z & (~(!x)+1));
}

/*
 * add_ok - Return 0 if x+y will overflow, resulting in an incorrect computation.
 *			Return 1 otherwise
 *   Examples: add_ok(0x80000000, 0x80000000) = 0
 *             add_ok(0x80000000, 0x70000000) = 1
 * 			   add_ok(0xFFFFFFFF, 0x00000001) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Points: 6
 */
int add_ok(int x, int y) {
	// We shift the sum of x and y, and x and y themselves to check 
	// their sign. When x and y have different signs, the sum will not overflow.
	// When x and y have same signs and different sign with their sum, there
	// is an overflow occur. 
	int z = x + y;
	int a = x >> 31;
	int b = y >> 31;
	int c = z >> 31;
	return !!(a^b)|(!(a^c)&!(b^c));
 
}

/*
 * leastBitPos - Return a mask that marks the position of the
 *   least significant 1 bit. If x == 0, return 0
 *   Examples: leastBitPos(96) = 0x20
 * 			   leastBitPos(7) = 0x01
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Points: 8
 */
int leastBitPos(int x) {
	// NOT x will have a 0 corresponding to the position of least significant 1
	// bit, and all 1s to its right. So we add 1 to NOT x, which will make that
	// position 1. We AND x with the result, except for that digit, everywhere
	// else will become zero because they're different, so we get the mask. 
	return x & ((~x)+1); 
}

/*
 * abs_val - Return the absolute value of x
 *   Examples: abs_val(-1) = 1
 *             abs_val(33) = 33
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Points: 10
 */
int abs_val(int x) {
	// If x is negative, we add it with -1 and XOR it with -1 to get the 
	// negation, if x is 0 or positive, it will return the orginal x. 
	return (x + (x >> 31)) ^ (x >> 31); 
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0
 * 			   bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 * 	 Illegal ops: !
 *   Max ops: 12
 *   Points: 10
 */
int bang(int x) { 
	// When x is positive or negative, any of one side will evaluate to 0 and
	// the otherside 1, so we get the final result 0; when x is 0, both side
	// evaluate to 1, so we get the final result 1. 
	return ((x >> 31) + 1) & ((((~x)+1) >> 31) + 1);
}
