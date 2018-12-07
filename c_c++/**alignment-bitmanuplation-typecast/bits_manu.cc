/*
^ => binary XOR operator
~ => binary ones complement operator
! => return 1 if 0, return 0 otherwise

https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
https://stackoverflow.com/questions/6373093/how-to-print-binary-number-via-printf/6373450
https://www.geeksforgeeks.org/stack-in-cpp-stl/

g++ -std=c++14 bits_manu.cc -o bits_manu

*/

#include <iostream>
#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include <math.h>       /* pow */
#include <stack>
using namespace std;

/*************************************************************/
//
//         
/*************************************************************/

int allZeros(int x){
  int y = (x & 0x02 ) >> 1 | (x & 0x01);
  cout << ~y << endl;
  return ~y;
}

void signedCast(){
  printf("maximum unsigned int %u\n", -1); // 2^32 - 1 == 4294967295 == 11111111 11111111 11111111 11111111
  printf("%u\n", -2); // 2^32 - 2 == 4294967294 == 11111111 11111111 11111111 11111110
  printf("minimum signed int %u\n", -2147483647); // 2^32 - 2^31 == 2147483648 == 10000000 00000000 00000000 00000000
  printf("maximum signed int %u\n", 2147483647); // 2^31 - 1  == 2147483647 == 01111111 11111111 11111111 11111111
}

int getMinMax(){
  cout << (~0) << 31 << endl;
  int min = (~0) << 31; 
  int max = ~((~0) << 31);
  int test = 60;
  printf("%x\n", test);  // 
  printf("%x\n", min);  // 
  printf("%d\n", min); // INT RANGE: 2^31-1 (MAX) -2^31 (MIN) 
  printf("%x\n", max);
  printf("%d\n", max);
  return (~0) << 31;
}

// ucla 118 networking udp to tcp
void sixteenToEightBytes(){
  uint16_t fields[4] = {300, 301, 302, 303}; // 0000 0001 0010 1101, 0000 0001 0010 1110 ...
  uint8_t *byte_array = new uint8_t(8); // recvfrom() uses byte/char array
  for (int i = 0; i < 8; i+=2)
  {
    byte_array[i] = fields[i/2] >> 8; // upper 8 bits
    byte_array[i+1] = fields[i/2] & 0xFF; // lower 8 bits, actually no need 0xFF
  }
  byte_array[8] = '\0';

  for (int i = 0; i < 4; ++i){
      binaryPrint3(fields[i]);
  }
  
  for (int i = 0; i < 8; ++i){
    binaryPrint3(byte_array[i]);
  }

  // 8 bytes back to 16 bytes
  for (int i = 0; i < 4; ++i){
      fields[i] = (byte_array[i*2] << 8) | (byte_array[i*2+1]);
  }

  // fields has not changed
  for (int i = 0; i < 4; ++i){
      binaryPrint3(fields[i]);
  }
}


void sixteenToEightBytes2(){
    uint16_t value = 0xAAFF;
    uint8_t hi_lo_big_endian[] = { (uint8_t)(value >> 8), (uint8_t)value }; // { 0xAA, 0xFF }
    uint8_t lo_hi_little_endian[] = { (uint8_t)(value & 0xFF), (uint8_t)(value >> 8) }; // { 0xFF, 0xAA }
    // cout << int(hi_lo_big_endian) << endl;
    // cout << unsigned(hi_lo_big_endian) << endl;
    // printf("%#010x\n", value);
    // printf("%#010x\n", hi_lo_big_endian);
}

/*************************************************************/
//
//         
/*************************************************************/

void printstack(stack <int> gq)
{
    stack <int> g = gq;
    while (!g.empty())
    {
        cout << g.top();
        g.pop();
    }
    cout << '\n';
}

/*************************************************************/
// Binary print
/*************************************************************/

/*
print binary bits of any data type
i.e. convert bits into any data type
*/
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

void binaryPrint(int num){
  // printf("print 1 byte data type " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY('a'));
  printf(BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n",
  BYTE_TO_BINARY(num>>24), BYTE_TO_BINARY(num>>16), BYTE_TO_BINARY(num>>8), BYTE_TO_BINARY(num));
}

/* cannot print -ve ?? */
template<class T>
void binaryPrint2(T n){
  int count = 0;
  std::stack<int> bits;
  while(n){
    // (n & 0x01) ? '1' : '0';  
    bits.push(n & 0x01);
    // printf("%d", n & 0x01); // TODO: store in int/char stack
    n >>= 1;    
    count ++;
  }
  for (int i = 0; i < (sizeof(T)*8 - count); ++i)
  {    
    bits.push(0);
  }
  printstack(bits);
}

template<class T>
void binaryPrint3(T x)
{
    size_t s = sizeof(T); // sizeof(x) same
    char b[s*8];
    b[0] = '\0';
    char *p = b;

    size_t t = pow(2, s*8) - pow(2, s*8-1); // 10000000 00000000 00000000 00000000
        
    for (size_t z = t ; z > 0; z >>= 1) 
    {
        // strcat(b, ((x & z) == z) ? "1" : "0");
        *p++ = (x & z) ? '1' : '0';        
    }
    *p++ = '\0';
    cout << b << endl;
    // printf("%s\n", b);
}

/*
http://www.cplusplus.com/reference/cstdlib/itoa/
not supported by c++
integer value to a null-terminated string using the specified base 
*/
void binaryPrint5(int i){
  // char buffer [33];
  // itoa (i,buffer,2);
  // printf ("binary: %s\n",buffer);
}

/**/
void littleEndianBinaryPrint(size_t const size, void const * const ptr)
{    
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--) // each byte
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void binary2decimal(long long bin){
  int dec = 0;
  int remindar;
  int power = 0;
  while(bin){
    remindar = bin % 10;
    bin /=10;
    dec += pow(2, power) * remindar;
    power ++;
  }
  cout << dec << endl;
}


/*************************************************************/
// Rate 1  
/*************************************************************/

/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  // 85 == 01010101 => odd bits
  // 170 == 10101010 => even bits
  int a = ((170) | (170)<<8);
  a = a | a << 16;  
  cout << a << endl;
  return a;
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  int a = ~(1<<31);   
  return a;
}

/*************************************************************/
// Rate 2
/*************************************************************/

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {

  // return ((x | y) == y) ? 1 : 0;
  return !((x | ~y) + 1);
}

/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2 => i think shd be 3-4
 hint: >> any negative number => -1 i.e. 11111111 11111111 11111111 11111111
 => only if its signed number
 signed right shifts preserve the sign, unsigned right shifts puts zeroes in the top bits. So -1 >> 1 = -1 (signed) and 0xFFFFU >> 1 = 0x7FFF (unsigned).
 */
int sign(int x) {
  int firstBit = (x >> 31) & 1; 
  int neg = (firstBit <<31)>>31; // shift any negative number => -1     
  int result = neg | (!!x); // 1111| 0 if 0 1, if non-zero
  return result;  

  // return !(x >> 31);
}


/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 hint: 
 extract bit => & 1 bit mask
 overwrites bit => &0 then |
 
 1 byte mask to extract byte 
 0 byte mask to clear byte prepare to write w 1 byte mask

 1st byte: 255
 2nd byte: 2^16 - 2^8 = 65280
 e.g. byteSwap(789323999, 2, 4); 
 */
void byteSwap(int x, int n, int m) {
  int result;
  // 1st byte mask
  int one_byte_mask1 = 255 << (n-1) * 8;
  int zero_byte_mask1 = ~(255 << ((n-1) * 8)); // 3rd bytes all 0, rest of 1 => &
  int one_byte_mask2 = 255 << (m-1) * 8;
  int zero_byte_mask2 = ~(255 << ((m-1) * 8)); // 3rd bytes all 0, rest of 1 => &

  int extracted_byte_n = (x & one_byte_mask1); // extract w 1 byte mask
  int extracted_byte_m = (x & one_byte_mask2); // extract w 1 byte mask
  binaryPrint(x);
  binaryPrint(one_byte_mask1);
  binaryPrint(one_byte_mask2);  
  
  extracted_byte_n <<= (m-n) * 8;
  extracted_byte_m >>= (n-m) * 8;
  

  result = (x & zero_byte_mask2);
  result = (result & zero_byte_mask1);  
  result = (result | extracted_byte_n);
  result = (result | extracted_byte_m);
  binaryPrint(result);
}

/*************************************************************/
// Rate 3
/*************************************************************/
/* 
 * rotateRight - Rotate x to the right by n bits
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
void rotateRight(int x, int n) {
  int mask = pow(2,n) - 1;
  int captured = (x & mask);
  x >>= n;
  binaryPrint(x);
  captured <<= (32-n);
  binaryPrint(captured);
  int result = (x | captured);
  printf("%x\n", result);
}

/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 hint: 
 2 ways either way yes then yes, sign is extra just for practice
 difference between x and y => x + (~y+1); 
 sign: 1 if x +ve, y -ve, 0 otherwise => draw a table to decide which bit to ! &

 CANNOT => whichever number has highest most significant bit => w only operation above
 */
void isGreater(int x, int y) {
  int x_sign = x >> 31;
  int y_sign = y >> 31; 
  int x_pos_y_neg = (!x) & y; // draw table visualize => 1 only if x +ve, y -ve, 

  // int diff = x + (~y) + 1; // // +ve if x>=y, -ve if x < y
  int diff = x + (~y); // +ve only if x>y, -ve if x <= y
  int pos_diff = !(diff >> 31);
  cout << (pos_diff | x_pos_y_neg) << endl;
}

/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 

 NEGATIVE OVERFLOW
 0x80000000 == 10000000 00000000 00000000 00000000
 == unsigned int 2147483648 == int -2147483647 

 0x70000000 == 01110000 00000000 00000000 00000000
 == unsigned int 1879048192 == int 1879048192

turn +ve num to -ve num then addition
 ~, then +1

 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3

 hints:
 only same sign addition could overflow => x must be -ve
 x + y => signed bit become 0

 */
void subOK(int x, int y) {
  int x_neg = !(~x >>31); // -ve left shift => 1111111 ... not 00000001
  int overflow = !((x - y) >> 31); // if 000000 return 1 if 111111 return 0
  int result = x_neg & overflow; // x is negative + 2-ve become +ve
  cout << result << endl;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  /* if the first bit is 1,
   * try to change the new leading 1s to 0s.
   * use XOR to eliminate the extra 1s.
   */
  int shift = ((1 << 31) >> n) << 1;
  return ((x >> n) ^ shift) & (x >> n);
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /* it is easy to use 1 to represent x > 0 and 0 otherwise
   * after changing x to -x
   */
  int bit = (x >> 31) & 1;
  x = ~x + 2 + ~bit;
  return (x >> 31) & 1;
}
/*
 * isLess - if x < y  then return 1, else return 0
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  /*
   *1. x < y , x and y have the same sign
   *2. x < 0 && y > 0
   */
  /* second method
  int bit1 = (x >> 31) & 1;
  int bit2 = (y >> 31) & 1;
  int diff = bit1 ^ bit2;
  int res = x + ~y + 1;
  int bit = (res >> 31) & 1;
  return (diff & bit1) + (bit & !diff);*/
  int bit1 = (x >> 31) & 1;
  int bit2 = (y >> 31) & 1;
  int flag1 = bit1 & !bit2;

  int res = x + ~y + 1;
  int bitOfRes = (res >> 31) & 1;
  int flag2 = ~(bit1 ^ bit2) & bitOfRes;
  return (flag1 | flag2);

}


/*************************************************************/
// Rate 4
/*************************************************************/

/* 
 * logicalNeg - implement the ! operator using any of 
 *              the legal operators except ! 
i.e. except 0 retunrs 1, all other int return 0
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {  
 
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  /* use binary_search to get all the 1s in bit representation
   * and add their positions.
   */
  int left = x >> 16;
  int isZero = !!left & 1;
  int count = 0;
  int tempShift = isZero << 4;
  count += tempShift;
  x = x >> tempShift;

  left = x >> 8;
  isZero = !!left & 1;
  tempShift = isZero << 3;
  count += tempShift;
  x = x >> tempShift;

  left = x >> 4;
  isZero = !!left & 1;
  tempShift = isZero <<  2;
  count += tempShift;
  x = x >> tempShift;

  left = x >> 2;
  isZero = !!left & 1;
  tempShift = isZero << 1;
  count += tempShift;
  x = x >> tempShift;

  left = x >> 1;
  isZero = !!left & 1;
  tempShift = isZero << 0;
  count += tempShift;
  x = x >> tempShift;

  return count;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  /* consider normalized, denormalized and special cases.
   */
  unsigned sign = (uf >> 31) & 1;
  unsigned newUf = uf & 0x7fffff;
  unsigned exponent = (uf >> 23) & 0xff;


  if (!newUf && !exponent) // all zeros
      return uf;
  if (exponent == 0xff) // NaN
      return uf;

  if (exponent > 1) {
    exponent --;
  } else if (exponent == 1) {
    exponent --;
    newUf += 1 << 23;
    if ((newUf & 0x3) == 0x3) // round to even
        newUf = (newUf >> 1) + 1;
    else //round to even and truncate directly
        newUf = newUf >> 1;
  } else { //round to even
    if ((newUf & 0x3) == 0x3)
        newUf = (newUf >> 1) + 1;
    else //round to even and truncate directly
        newUf = newUf >> 1;
  }

  return (sign << 31) | ((exponent << 23) & 0x7f800000) | newUf;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
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
  /* first convert x to unsigned in order to do logical right shift
   * then find the first 1 and get the exponent and mantissa
   * count the actual exponent and do truncation
   */
  int xx = x;
  unsigned sign, exp, mantissa;
  int first = 0;
  int temp;
  int left;
  unsigned tempM, tail;

  sign = (xx >> 31) & 0x1;

  if (sign == 1)
      xx = ~xx + 1;
  temp = xx;
  while (first != 32 && !(temp & 0x80000000)) { //find the first 1
      first ++;
      temp = temp << 1;
  }
  if (first == 32) { //can not find 1, means zero
      exp = 0x00;
      mantissa = 0x0;
  } else {
      left = 31 - first; //count how many bits are left
      exp = left +  127;
      mantissa = xx << (first + 1);
      tempM = mantissa >> 9;
      tail = mantissa & 0x1ff;
      if (tail > 0x100) { //round up
          mantissa  = tempM + 1;
      } else if (tail < 0x100){ //round down
          mantissa = tempM;
      } else {
          if ((mantissa & 0x200) >> 9) //round up
              mantissa = tempM + 1;
          else
              mantissa = tempM; //round down
      }
      if (mantissa >> 23) { //mantissa becomes 0 after round up
         exp ++;
         mantissa = 0;
      }
  }
  return (sign << 31) | (exp << 23) | mantissa;

}




int main(int argc, char const *argv[])
{
  // byteSwap(789323999, 2, 4);
  rotateRight(0x87654321,4);

	return 0;
}