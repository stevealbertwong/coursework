/* Some examples of integer casting
 * Bill Zorn <waz@andrew.cmu.edu>
 * 15-122 f12
 https://www.cs.cmu.edu/~rjsimmon/15122-s13/rec/22/signed-casting.c
 http://calc.50x.eu/

 manually added sign extension
 https://stackoverflow.com/questions/6215256/sign-extension-from-16-to-32-bits-in-c

 15213 L2 
  expanding: 
    if original data type is: e.g. int8_t to int32_t
      unsigned: zero added
      signed: sign extension i.e. copying most significant bit

  truncating: e.g. uint32_t to uint8_t
    unsigned: mod
    signed: mod


CS107 lab2 c-string: 
ASCII and ctype
    <ctype.h> offers small utility functions such as isdigit and tolower that operate on single characters. The ctype function isxdigit below reports whether a given character is a valid hex digit.

    int isxdigit(int c)
    {
        return isdigit(c) || ((unsigned)c|32)-'a' < 6;
    }
    Here are a few questions to work out with your partner. If you need an ASCII refresher, use man ascii.

    It seems the first test checks for a digit character, so the second test must be in charge of validating hex letters, but its expression is rather mystifying. What is the purpose of the bitwise OR with 32 and the character subtraction?
    The cast to unsigned is deliberate and necessary. Get into gdb and print the expression where c is '#' both with and without the cast, e.g.:

    (gdb) p ((unsigned)'#'|32)-'a' < 6
    You'll see that the result is different without the cast. Why?

    Use man string to see the list of string functions in the standard library. You could reimplement ixdigit as a single call to one of them. Describe how.


(gdb) p (unsigned)'#'-'a'
$26 = 4294967234
(gdb) p '#'-'a'
$27 = -62

if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z')
strcmp: 
     The strcmp() and strncmp() functions return an integer greater than, equal to, or less than 0, according as the string s1 is
     greater than, equal to, or less than the string s2.  The comparison is done using unsigned characters, so that `\200' is greater
     than `\0'.


static cast vs dyanmic cast vs const cast vs reinterpret cast
 */

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>


void dorabot_rsa_char2long(){
  // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
  
  char charArray[]={'h','e','l','l','o',' ','w','o','r','l','d','\0'};
  char *i = &charArray[0];
  char *j = charArray;
  cout << j;

  const char *char_ptr = "hellow world";
  char* erase_const = const_cast<char*>(char_ptr);
  cout << erase_const;

  unsigned long int *arr = new unsigned long int(100);
  for (int i = 0; i < sizeof(arr); ++i)
  {
    cout << charArray[i] << endl;
    arr[i] = (int)charArray[i];
    cout << arr[i] << endl;
  }
}

/*
https://stackoverflow.com/questions/7504277/int-to-char-casting
http://www.asciitable.com/

If char is unsigned it will wrap around. 
i.e. 8-bit char 259 % 256 = 3

*/
void dorabot_rsa_int2char(){
  
  int d = 359; // 256 + 103(g) same as typecast g
  cout << (char)d;

  int e = 123; // weird symbol {
  cout << (char)e;

  char i = 'g';
  i = i * i;
  cout << (int)i << endl;
  
  int a = (int)i;
  a = (a * a) % 256; // ascii all possible value
  cout << (char)a << endl;
}



int main()
{
  /* What happens when we cast from a 1-byte integer to a 4-byte integer?
   *
   * For clarity, we use the integer types from inttypes.h.
   * Note that int8_t is the same as a (signed) char, and int32_t is
   * (probably) the same as a (signed) int.
   *
   * Also for clarity, we use ridiculous formatting strings so that when
   * we print the values, they reflect the bit representations of the
   * corresponding integers. You do not need to understand how these
   * printf statements work.
   */

  unsigned long addr1;
  unsigned long addr2;
  int8_t c;
  int32_t i;

  uint8_t uc;
  uint32_t ui;

  int64_t l;

  /* We have an uninteresting case when c is positive. */
  c = 0x75;       // 117
  i = (int32_t)c; // cast 1-byte to 4-byte, signed
  addr1 = c;
  addr2 = i;

  printf("casting: 0x75 from int8_t to int32_t\n");
  // hashtag/pound => added 0x 
  // hh = no sign cast in format string => instead of printing 0xfffffff0, it prints 0xf0 i.e. no sign casting when printing format string
  // 0.2 => 2 decimal places
  // https://www.cprogramming.com/tutorial/printf-format-strings.html
  // https://stackoverflow.com/questions/4586962/what-is-the-purpose-of-the-h-and-hh-modifiers-for-printf
  printf("  c was: %#.2hhx, i is now: %#.8x\n\n", c, i);
  printf("  c was: %#lx, i is now: %#lx\n\n", addr1, addr2);
  char b = 0x80; // or f0 etc...
  // i guess casting happens in format string printing
  printf("  b was: %#.2hhx, b was: %#.2x\n\n", b, b);
  printf("  b was: %#x, b was: %#x\n\n", b, b);
  char d = 0x75; // hh wont work on 0x75
  // int e = (int)d;
  // the reason its prints 0x00000075 is because of .8x
  printf("  d was: %#.2hhx, d was: %#.8x\n\n", d, d);

  /* When c is negative, something strange happens to the high bits. */
  /* 
  NEGATIVITY ONLY HAPPENS AT DECIMAL LEVEL 
    e.g. -0x75 decimal is -112, convert into binary then cast as unsigned hex 

    since can't print signed negative hex => -0x75 becomes 0x90
    see: https://stackoverflow.com/questions/9602974/how-to-print-signed-hex-in-c
  */
  c = -0x75;      // -112, or 0x90, but writing it as 0x90 would be overflow    
  c = 0x90; 
  i = (int32_t)c; // cast 1-byte to 4-byte, signed

  printf("casting: 0x90 from int8_t to int32_t\n");
  printf("c in decimal %d\n", c);
  printf("  c was: %#.2hhx, i is now: %#.8x\n\n", c, i);
  

  /* Since there are more bits in an int32_t than there are in an int8_t,
   * something must happen to the high bits. If we make a signed cast,
   * then they are all set to the same value as the sign bit of the integer
   * we are casting from. Note that this preserves the signed value of the
   * number.
   */

  /* As above, with decimal values. */
  c = 117;        // 0x75
  i = (int32_t)c; // cast 1-byte to 4-byte, signed

  printf("casting: 117 from int8_t to int32_t\n");
  printf("  c was: %hhd, i is now: %d\n\n", c, i);
  printf("  c was: %#.2hhx, i is now: %#.8x\n\n", c, i);

  /* As above, with decimal values. */
  c = -112;       // 0x90
  i = (int32_t)c; // cast 1-byte to 4-byte, signed

  printf("casting: -112 from int8_t to int32_t\n");
  printf("  c was: %hhd, i is now: %d\n\n", c, i);
  printf("  c was: %#.2hhx, i is now: %#.8x\n\n", c, i);

  /* If our integer types are not signed, then the high bits are always
   * filled with 0, as this correctly preserves the numerical value.
   */

  /* We now perform the same casts using unsigned integers. */
  uc = 0x75;         // 117
  ui = (uint32_t)uc; // cast 1-byte to 4-byte, unsigned

  printf("casting: 0x75 from uint8_t to uint32_t\n");
  printf("  uc was: %#.2hhx, ui is now: %#.8x\n\n", uc, ui);

  /* The strange sign extension behavior is not observed. */
  uc = 0x90;         // 144
  ui = (uint32_t)uc; // cast 1-byte to 4-byte, unsigned

  printf("casting: 0x90 from uint8_t to uint32_t\n");
  printf("  uc was: %#.2hhx, ui is now: %#.8x\n\n", uc, ui);

  /* Finally, note that the sign extension behavior is only determined by
   * the type we are casting from. If we are casting from a signed type, then
   * we will always sign extend with the value of the sign bit; if we are
   * casting from unsigned, we will always sign extend with 0. The destination
   * type (specifically, whether or not is is signed) does not matter.
   */

  /* Signed to unsigned: still uninteresting. */
  c = 0x75;         // 117
  ui = (uint32_t)c; // cast 1-byte to 4-byte, signed

  printf("casting: 0x75 from int8_t to uint32_t\n");
  printf("  c was: %#.2hhx, ui is now: %#.8x\n\n", c, ui);

  /* The same as the signed to signed behavior. */
  c = -0x70;        // -112, or 0x90
  ui = (uint32_t)c; // cast 1-byte to 4-byte, signed

  printf("casting: 0x90 from int8_t to uint32_t\n");
  printf("  c was: %#.2hhx, ui is now: %#.8x\n\n", c, ui);

  /* Unsigned to signed. */
  uc = 0x75;       // 117
  i = (int32_t)uc; // cast 1-byte to 4-byte, unsigned

  printf("casting: 0x75 from uint8_t to int32_t\n");
  printf("  uc was: %#.2hhx, i is now: %#.8x\n\n", uc, i);

  /* Same as unsigned to unsigned. */
  uc = 0x90;       // 144
  i = (int32_t)uc; // cast 1-byte to 4-byte, unsigned

  printf("casting: 0x90 from uint8_t to int32_t\n");
  printf("  uc was: %#.2hhx, i is now: %#.8x\n\n", uc, i);

  /* As a last aside, we note that casting within a single integer size
   * has no impact on the binary representation of the integer. The only
   * difference is how the integer will be treated by other operations,
   * such as other casts or comparisons.
   *
   * Also, we should note that casting to a smaller integer type will
   * always truncate the integer by simply chopping off the bits on the
   * left. We don't really need examples, as the behavior is consistent,
   * but be aware that it might destroy information about the number.
   * Casting to a larger type does not have this property: we can always
   * cast back down to get the same number. However, if we cast down and
   * then back up, the high bits will be set either all to 0 or all to 1.
   */

  /* deadbeef is deadbeef, signed or unsigned. */
  ui = 0xdeadbeef;
  i = (int32_t)ui;

  printf("casting: 0xdeadbeef from uint32_t to int32_t\n");
  printf("  ui was: %#.8x, i is now: %#.8x\n\n", ui, i);

  /* Cast from unsigned. */
  l = (int64_t)ui;

  printf("casting: 0xdeadbeef from uint32_t to int64_t\n");
  printf("  ui was: %#.8x, l is now: %#.16lx\n\n", ui, l);

  /* Different when we make the same cast from signed. */
  l = (int64_t)i;

  printf("casting: 0xdeadbeef from int32_t to int64_t\n");
  printf("  i was: %#.8x, l is now: %#.16lx\n\n", i, l);

  return 0;
}