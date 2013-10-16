/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
       /*
	 Gets sign bit and takes the complement.
	 This gives an int of all 1's and an int
	 of all 0's. Exploiting ~x + 1 gives the
	 negative of x. Exploiting & with x and (~x+1)
	 for oppSignExt and ~oppSignExt generates 
	 the absolute value.
	*/
       int sign = x >> 31;
       int oppSignExt = ~sign;
       int q = oppSignExt & x;
       int r = ~oppSignExt & (~x + 1);

       return q | r;
}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /*
    Generates all 1's if x is negative or if x + TMAX is negative.
    If either of these is all 1's, | give all 1's, and ~ gives
    all 0's. If x is 0, adding TMAX leaves the sign bit 0,
    so right shifting gives all 0's still. So | gives all 0's, ~ 
    gives all 1's. Taking & 0x1 gives 1 for 0 and 0 for anything 
    else. 
   */

  int neg = x >> 31;

  int pos = (x + ~(0x1 << 31)) >> 31;

  int ans = ~(neg | pos) &  0x1;

  return ans;

}


/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  return 2;
}


/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) { 
  /*
    Exploits left shifting by 3 to multiply both m and n by 8.  
    Left shift a byte of all 1's (0xFF) by the shifted m
    and another by the shifted n; the & operation separates
    the mth and nth bytes from x, stored separately.

    Right shifting and left shifting by the opposite values 
    switches the m and n positions.

    Using XOR and ~ the nonswitched bytes are selected and
    the & stores these bytes. 

    Finally, adding the not switched bytes with the ^ of the
    switched bytes yields the result with bytes m and n swapped.
   */

  int result;
  int FF = 0xFF;

  int mShifted = m << 3; //1
  int nShifted = n << 3; //1

  int byteM = FF << mShifted; //1
  int byteN = FF << nShifted; //1
  int switchedBytes = byteM ^ byteN; //1
  int notSwitchedBytes = ~switchedBytes; //1

  byteM = byteM & x; //1
  byteN = byteN & x; //1

  byteM = byteM >> mShifted; //1
  byteN = byteN >> nShifted; //1

  byteM = byteM & FF; //1
  byteN = byteN & FF; //1
  byteM = byteM << nShifted; //1
  byteN = byteN << mShifted; //1

  notSwitchedBytes = notSwitchedBytes & x; //1

  result = notSwitchedBytes + (byteM ^ byteN); //2
  return result;
  
  return 2;
}


/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
    Exploits ! to get either 0 or 1. Uses left shift/right 
    shift to copy the LSB to every other bit (32 total).
    
    Uses & and ~ to get all 0's for one operation (either
    p or ~p will be all 0's) and either y or z (depending on x)
    for the other. Using | on the two results (one is all 0's)
    will return the nonzero argument.
   */
  
  int p = !x << 31 >> 31; // all 0's or all 1's
  int q = p&z; // z if p is all 1's, 0 otherwise
  int r = ~p&y; // y if p is all 0's, 0 otherwise
  int result = q | r;

  return result;
}


/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

  /* Exploits fact that right shifting divides by 
     powers of 2 correctly for positive values.
     For negative values, checks divisibility
     by checking the first n bits. Exploits 
     ~ to subtract n from 31, left shifting
     and right shifting to get 
     1's for last n bits, then uses & to check
     if any of the first n bits are nonzero.
     Uses !! to give 0 if all are 0 and 1 if any
     are nonzero. Using & with sign gives 1 if 
     negative and not evenly divisible, 0 otherwise.
     Then adds to the right shifted x value.
   */
 
  int sign = (x >> 31);
  int div = x >> n; // evenly divisible?
  int shift = 31 + (~n+1); // 31-n
 
  int checkBit = ~((0x01 << 31) >> (shift));
  
  int addTo = sign & !!(x & checkBit);
  int result = div + (addTo);

  return result;
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /*
    Exploits fact that return same value every time.

    Starts with 0x55, shifts left 1 byte and exploits ^
    to copy the byte. Repeats shifting by 2 bytes.
   */
  int result = 0x55;
  result = result ^ (result << 8);
  result = result ^ (result << 16);
 
  return result;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*
    Exploits left shift to copy the sign bit.
    Uses ! to differentiate between zero and nonzero.
    Exploits ^ to make zero and negative the same case (all 1's)
    and to make positive all 0's. 
    
    Exploits ! to make positive 1, negative and 0 become 0. 
   */
  int X = (x >> 31);
  int Y = !x;
  int result = X ^ Y;
  return !result;
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  /*
    exploits fact that !0 returns a nonzero value (1), while 
    ! any other value returns 0;
   */
  
  return !x;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  /*
    Exploits the fact that the pattern repeats after 
    12 bites. Exploits left shifts to make into groups of
    12 bits, ^ puts parts together. 
    Last byte is equal to the first byte, so
    use that for last ^ operation. 
   */

  int firstGroup = 0x49;
  int secondGroup = 0x2;
  int result = (firstGroup << 4) ^ secondGroup;

  result = (result << 12) ^ result;

  result = (result << 8) ^ firstGroup;
  return result;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  /*
    Exploits left shift to put 1 in sign bit, 
    0's everywhere else.
    Taking ~ switches sign to 0 and all others to 
    1. 
   */
  int result = 0x80;

  result = result << 24;
  result = ~result;

  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*
    Exploits left shifting to move 1 to sign bit,
    have 0's everywhere else.
   */
  return (0x80<<24);
}
