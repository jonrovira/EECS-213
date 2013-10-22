/* 
 * CS:APP Data Lab 
 * 
 * Curtis Wiese (cjw279)
 * Jon Rovira (jmr566)
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
  /*
    Exploits shifting and & to get all bytes to far right.
    Exploits fact that ^ gives:
    - even number of 0's if both operands have even number of 0's
    - odd otherwise (both odd, one even one odd)

    Divides bytes and repeates until only operating on single bit,
    will be 0 if original had odd number of 0's, 1 if original
    had even number of 0's.
   */

  int ones = 0xFF;

  int first = ones & (x >> 24);
  int second = ones & (x >> 16);
  int thirdByte = ones & (x >> 8);
  
  int evenOdd = first ^ second ^ thirdByte ^ x;  
  
  first = 0xF & (evenOdd >> 4);

  evenOdd = first ^ evenOdd;

  first = 0x3 & (evenOdd >> 2);

  evenOdd = first ^ evenOdd;

  first = 0x1 & (evenOdd >> 1);
  second = 0x1 & evenOdd;

  evenOdd = first ^ second;

  return evenOdd;
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

  int mShifted = m << 3;
  int nShifted = n << 3; 

  int byteM = FF << mShifted; 
  int byteN = FF << nShifted; 
  int switchedBytes = byteM ^ byteN; 
  int notSwitchedBytes = ~switchedBytes; 

  byteM = byteM & x; 
  byteN = byteN & x; 

  byteM = byteM >> mShifted;
  byteN = byteN >> nShifted; 

  byteM = byteM & FF; 
  byteN = byteN & FF; 
  byteM = byteM << nShifted; 
  byteN = byteN << mShifted; 

  notSwitchedBytes = notSwitchedBytes & x; 
  result = notSwitchedBytes + (byteM ^ byteN); 
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
  
  /*
    Exploits the structure of floating points in 32 bit machines.
    Checks exponent bits and fraction bits. If exponent is all 1's and 
    some fraction bit is a 1, then result is NaN and the input is returned unchanged.
    Otherwise, uses & to set the sign bit to 0 and returns the value.
   */

  unsigned exponent = 0x7f800000;
  unsigned frac = 0x007fffff;
  if (((uf & exponent) == exponent) && ((uf & frac) != 0x0)){
    return uf;
  }
  return uf & 0x7fffffff;

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
 
  /*
    Exploits the bit representation of floating point numbers. First checks two 
    extreme cases (0 and TMIN), determines the sign,
    then uses a loop and & to find the most significant 1,
    stores the position. 
    Then uses left shifting to put most significant 1 in the most location (furthest left).
    Takes the next 23 bits as the fraction, checks the bit immediately after the fraction
    to see if rounding needs to occur. If that bit is 1, checks for any other 1's in the remaining
    bits. If one, sets variable to add 1 to total. If all 0s, checks last fraction bit for 
    rounding: sets to add 1 if it is a 1, does nothing if a 0.

    Utilizes the location of most significant 1 to determine E, calculates exp using this value and
    127 for the bias ((2^7)-1). Uses shifting to get all of these peices in the correct location, adds
    them together and adds 1 if rounding up required.

   */  
  
 
  unsigned sign = x & 0x80000000;
  unsigned checker = 0x40000000;
  int magnitude = 31;
  unsigned spot = 0;
  int leftShift;
  unsigned leftShifted;
  unsigned twentyThreeBits;
  unsigned twentyFifthBit;
  unsigned addOne;
  unsigned lastSeven;
  unsigned result;
  unsigned twentyFourthBit;
  unsigned exponent;

  // tmin case
  if(x == 0x80000000) 
    return 0xcf000000;
  if(!!sign) {
    x = ~x + 1;
   }

  //Zero case
  if((x ^ 0x0) == 0x0) return 0x0;

  //Finds number by which to shift left
  while(spot == 0){    
    if((checker & x) == checker) {
      spot = magnitude;
    }
    checker = checker >> 1;
    magnitude = magnitude + (0xFFFFFFFF);
  }

  // Shifts x left until the most significant 1 is on the left
  leftShift = 33 + (~spot);
  leftShifted = x << leftShift;

  // Twenty-three on far left, zeros on right
  twentyThreeBits = leftShifted & 0x7fffff00;

  // Basic case to check if round up is even possibility
  twentyFifthBit = leftShifted & 0x00000080;
  addOne = 0;
  

  if(twentyFifthBit == 0x80) {
    lastSeven = leftShifted & 0x0000007f;
        
    // Round up
    if(lastSeven) {
      addOne = 1;
      // twentyThreeBits = ((twentyThreeBits >> 8) + 1) & 0x007FFFFF;
      //twentyThreeBits = twentyThreeBits + 0x00000100;
    }
    else {
      twentyFourthBit = twentyThreeBits & 0x00000100;
      // Round up
      if(twentyFourthBit) {
	//twentyThreeBits = ((twentyThreeBits >> 8) + 1) & 0x007FFFFF;
        addOne = 1;
      }
    }
  }
  // Fraction
  twentyThreeBits = twentyThreeBits >> 8;

  // Exponent
  exponent = (spot + 0xFFFFFFFF) + 127;
  exponent = exponent << 23;

  //twentyThreeBits = twentyThreeBits & 0x007FFFFF;
  result =  twentyThreeBits + sign + exponent;
  if(addOne)
    result = result + 1;
  return result;
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
