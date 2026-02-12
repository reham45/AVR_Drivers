#ifndef _STD_TYPES_H 
#define _STD_TYPES_H

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned long int u32;
typedef signed long int s32;
typedef unsigned long long int u64;
typedef signed long long int s64;
 
typedef float f32;
typedef double f64;
typedef long double f128;

typedef enum {
    false = 0,
    true = 1
} bool;

#define NULL 0
/*FUNC States*/
#define BUSY 0
#define IDLE 1
/*My states*/
#define OK 0
#define Nok 1

#endif 
