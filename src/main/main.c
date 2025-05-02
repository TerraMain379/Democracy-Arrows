#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../base64/base64.h"
#include "../buffer/buffer.h"
#include "../mapcoder/mapcoder.h"
#include "../world/world.h"

int main2(int argc, char *argv[]) {
  char* str = "Hello world123";
  size_t len = 0;
  char* result = base64_encode(str, strlen(str), &len);
  printf("%s\n", result);
  char* t = base64_decode(result, len, &len);
  printf("%zu:%s\n", len, t);
  return 0;
}
int main(int argc, char *argv[]) {
  struct World* world = malloc(sizeof(struct World));
  world->chunks = Buffer_new();
  struct Chunk* chunk = calloc(1, sizeof(struct Chunk));
  chunk->x = 2;
  chunk->y = 5;
  struct WorldArrow a1 = {0};
  a1.type = 1;
  a1.diraction = 1;
  chunk->arrows[0] = a1;
  struct WorldArrow a2 = {0};
  a2.type = 4;
  a2.diraction = 6;
  chunk->arrows[2] = a2;
  struct WorldArrow a3 = {0};
  a3.type = 4;
  a3.diraction = 7;
  chunk->arrows[40] = a3;
}
