#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

void va_test(int i, ...)
{
  va_list args_ptr;
  int j = 0;
  va_start(args_ptr, i);
  while(i-->0) {
    j = va_arg(args_ptr, int);
    printf("%d => %d\n", i, j);
  }
  va_end(args_ptr);
  return;
}

int main(int argc, char *argv[])
{
  va_test(4, 3, 34, 213, 2100, 34);
}
