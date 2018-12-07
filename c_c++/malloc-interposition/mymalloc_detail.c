/*
15213 lec13 linking

C library interpositioning at linker level
    i.e. intercept/interpose system/library function calls without changing the library source code

    Example purposes:
    facebook fishhook all posix write functions, 
    malloc track number of calls, detect leaked, 
        generate address traces(i.e. record addresses n sizes malloc is returning)
    fork() avoid recusive calling for security,
    statistics, error checking, check arguments

The task is to write our own malloc() and make sure our own malloc() is called inplace of library malloc().
Examples of run-time, link-time, and compile-time library interposition

http://www.cs.cmu.edu/afs/cs/academic/class/15213-s03/src/interposition/
http://www.geeksforgeeks.org/function-interposition-in-c-with-an-example-of-user-defined-malloc/
https://gist.github.com/ecki/77cc3249437fdefad073261b6e93de7c


gcc -Idir
    => run include directory of header files first
    => or include headers in subdirectories
        e.g. gcc -Iproj/src myfile.c -o myfile
        header files in proj/src/myheader.h
    http://www.rapidtables.com/code/linux/gcc/gcc-i.htm

Conditional compilation
    => i.e. the selection of lines of source code to be compiled and those to be ignored
    => avoid or include certain part of code 
    => -DCOMPILETIME => define COMPILETIME into 1 so code is included
    => #ifdef MARCO: if there is a definition available for the macro, run the code        
    
        #define AVOID // definition available: if exists, then 2nd printf, if comment out then no
        printf("1");
        #ifdef AVOID
        printf("2");
        #endif

    => if macro AVOID exists, then 2nd printf avaiable for compiler,
    => otherwise c preprocessor will remove 2nd printf
    => #define AVOID => definition AVOID exists
    https://www.youtube.com/watch?v=YIlyb2S_wuE
    http://ee.hawaii.edu/~tep/EE160/Book/chap3/subsection2.1.3.4.html

*/
#include <stdio.h>
#include <stdlib.h>

#ifdef COMPILETIME
/* 
 * C PREPOSSESSOR:
 *      => malloc.h #define malloc(size) mymalloc(size)
 *      => c prepocessor to replace main.c malloc 
 *          => with your wrapper malloc
 *          => your wrapper malloc lib is separately compiled
 *          => so real malloc inside wrapper malloc wont get translated
 *      => -I. + mymalloc.o 
 *      
 * 
 * 1. in your own library, mymalloc wrapper calls real malloc
 * 2. malloc.h #define malloc(size) mymalloc(size)
 *      => A local malloc.h file defines malloc (free) as wrappers mymalloc
 * 3. compile mymalloc.c into mymalloc.o SEPARATELY
 *      => real malloc inside your wrapper malloc will not get translated
 *      => gcc -Wall -DCOMPILETIME -c mymalloc.c
 * 4. gcc -Wall -I. -o main main.c mymalloc.o 
 *      => -I. look for "include lib functions" in current directory first
 *      => gcc compiler gets confused about malloc, ask c prepcessor to find malloc.h, then translate all the malloc into mymalloc
 *      => after compilation, linker found mymalloc as unresolved reference, look into linked relocatable object file as library and found mymalloc()  
 */

void *mymalloc(int size){
    printf("call from wrapper mymalloc %d", size);
    void* ptr = malloc(size);
    return ptr;
}

#endif


#ifdef LINKTIME
/*     
 * 
 * LINKER API: linker (i.e. ld) "--wrap symbol" flag
 *      => linker's api for wrapped function if you follow format
 *          => Any undefined reference to symbol will be resolved to “wrap_symbol”. 
 *          => Any undefined reference to “real_symbol” will be resolved to symbol.
 *      => intercept function: __wrap_symbol
 *      => inside intercept define real call as: __real_symbol
 * 
 * Actual call to malloc => Fake call to __wrap_malloc
 * Fake call __real_malloc => Actual call to malloc
 * 
 * 1. DO NOT #include <stdlib.h> in main.c ??
 *      => unresolved reference to malloc
 *      => fake call to __wrap_malloc
 * 2. gcc -Wall -DLINKTIME -c mymalloc.c
 * 3. gcc -c main.c
 * 4. gcc -Wall -W1,--wrap,malloc, -W1,--wrap,free -o main main.o mymalloc.o
 *      => NO NEED #include <stdlib.h> in mymalloc.c
 *      => -W1 passes arguments to linker, replacing comma with a space
 *          => ld --wrap malloc
 *      => --wrap,malloc arg instruct linker to resolve reference in special way
 *          => ref to malloc should be resolved as __wrap_malloc
 *          => ref to __real_malloc should be resolved as malloc
 * 5. 
 * 
 * http://samanbarghi.com/blog/2014/09/05/how-to-wrap-a-system-call-libc-function-in-linux/
 * man 1 ld
 * can't run on mac, must linux
 */
void * __real_malloc(size_t t);
void *__wrap_malloc(size_t size){
    void *ptr = __real_malloc(size); // libc malloc
    return ptr;
}

 #endif



#ifdef RUNTIME
/*
 * DIRECT CALL: set dynamic linker's (ld-linux.so) LD_PRELOAD mechanism to wrapper shared object file
 *      => prioritize your library over syslib
 *      => inside wrapper malloc
 *          => dlsym(RTLD_NEXT, "malloc")
 *      => LD_PRELOAD $ENV environment variable => execute main
 *          => tells dynamic linker to resolve unresolved ref by looking in mymalloc.c first
 *          => (LD_PRELOAD="./mymalloc.so" ./main)
 *           
 * 1. name wrapper function malloc + dylsm
 *      => mallocp = dlsym(RTLD_NEXT, "malloc") # libc malloc addr
 * 2. gcc -Wall -DRUNTIME -shared -fpic -ldl -o mymalloc.so mymalloc.c
 * 3. (LD_PRELOAD="./mymalloc.so" ./main)
 *      => initialize it in bash then run ./main
 *      => ask gcc to look into our wrapper malloc first
 *      => all reference to malloc turn into ref to wrapper 
 * 
 * 
 * 
 * 
 * TCSH vs BASH (Assume a.out calls malloc and free):
 *   linux> gcc -O2 -Wall -o mymalloc.so -shared mymalloc.c
 *
 *   tcsh> setenv LD_PRELOAD "/usr/lib/libdl.so ./mymalloc.so"
 *   tcsh> ./a.out
 *   tcsh> unsetenv LD_PRELOAD
 * 
 *   ...or 
 * 
 *   bash> (LD_PRELOAD="/usr/lib/libdl.so ./mymalloc.so" ./a.out)	
 */


#endif




