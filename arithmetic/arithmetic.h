#ifndef _ARITHMETIC
#define _ARITHMETIC

#include <stdio.h>
#include <stdlib.h>

const int DIVIDE_BY_ZERO; 
const int GOOD;
int PREVIOUS_ERROR; 

int add(int x, int y); 
int subtract(int x, int y); //x - y
int mult(int x, int y); 
int divide(int x, int y); //x / y
int modulo(int x, int y); // x % y
int expon(int base, int power); //x^y

#endif
