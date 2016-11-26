/***
 @file   : test.c
 @brief  : c program to show the usage of function pointer
          the program implements a array of function pointer
 @author : bhanujha@gmail.com
 **/
#include <stdio.h>
int add(int a, int b) 
{
  return a+b;
}
int sub(int a, int b)
{
  if (a > b) {
    return a-b;
  } else {
    return b-a;
  }
}
void main()
{
  int (*fp[2])(int, int);
  fp[0] = &add;
  printf("%d\n",(*fp[0])(2,3));
  fp[1] = &sub;
  printf("%d\n",(*fp[1])(2,3));
}
