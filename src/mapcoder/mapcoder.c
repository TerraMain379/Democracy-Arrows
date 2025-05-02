#include "./mapcoder.h"

#include <stdint.h>

#include "../base64/base64.h"
#include "../world/world.h"
#include "../buffer/buffer.h"

size_t Chunk_size = 16;
size_t Chunk_len = 16*16;

char* encodeWorld(struct World* world, size_t* resultLen) {
  struct Buffer* bytes = Buffer_new();

  struct Buffer* chunks = world->chunks;
  for (int i = 0; i < chunks->size; i++) {
    struct Chunk* chunk = chunks->get(chunks, i);
    bytes->add(bytes, (char) chunk->x);
    bytes->add(bytes, (char) (chunk->x >> 8));
    bytes->add(bytes, (char) chunk->y);
    bytes->add(bytes, (char) (chunk->y >> 8));

    struct Buffer* loaddedArrows = Buffer_new();
    for (size_t i = 0; i < Chunk_len; i++) {
      struct WorldArrow* arrow = chunk->arrows[i];
      char type = arrow->type;

      // проверяем, была ли стрелочка уже обработана
      int loadded = (int) loaddedArrows->get(loaddedArrows, i);
      if (char == 0) {
        // необработана
        bytes->add(bytes, type);
        bytes->add(bytes, 0);
        size_t num = bytes->size-1;
        for (int j = i; j < Chunk_len; j++) {
          struct WorldArrow* arrow2 = chunk->arrows[i];
          char type2 = arrow->type;
          if (type == type2) {// обрабатываем стрелочку
            
            // увеличиваем счётчик стрелочек
            int numVal = bytes->get(bytes, num);
            bytes->set(bytes, num, numVal+1);

            // представляем позицию в виде байта
            char y = (char) (size_t) j / Chunk_size;
            char x = (char) (size_t) j % Chunk_size;
            char pos = x + (y << 4);

            bytes->add(bytes, pos);
            bytes->add(bytes, arrow2->diraction);

            // регестрируем, что стрелка была добавлена
            if (loaddedArrows->size == j) {
              loaddedArrows->add(loaddedArrows, 1);
            }
            loaddedArrows->set(loaddedArrows, j, 1);
          }
          else {
            // регестрируем, что стрелка НЕ была добавлена
            if (loaddedArrows->size == j) {
              loaddedArrows->add(loaddedArrows, 0);
            }
          }
        }
      }
      else {
        // обработана
      }
    }
    loaddedArrows->free(loaddedArrows);
  }

  *resultLen = bytes->size;
  char* bytesC = malloc(sizeof(char[bytes->size]));
  for (int i = 0; i < bytes->size; i++) {
    bytesC[i] = bytes->get(bytes, i);
  }
  return bytesC;
}
struct World* decodeWorld(char* base64, size_t base64len);
