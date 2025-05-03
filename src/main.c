#include "./main.h"

#include <stdio.h>
#include "./logicarrows/logicarrows.h"

void print_bits(char c) {
  for (int i = 8 - 1; i >= 0; i--) { // идём от старшего бита к младшем
    putchar((c & (1 << i)) ? '1' : '0');
  }
  putchar('\n');
}

int main (int argc, char *argv[]) {
  printf("Run Democracy Logic Arrows\n");
  print_bits(0b00000001);
  print_bits(0b00000011 + (0b00000011 << 3));
  return 0;
}
