#include "../buffer/buffer.h"

struct World {
  struct Buffer* chunks;
};

int Chunk_size = 16;
int Chunk_len = 16*16;

struct Chunk {
  uint16_t x;
  uint16_t y;
  struct WorldArrow arrows[Chunk_len];
};
struct WorldArrow {
  char type;
  char diraction; // rotate and flip (and 5 bit for activation)
};





// 2B (x чанка) 2B (y чанка) 1B (Тип стрелочки) 1B (количество) {1B (позиция) 1B - поворот и отражение}(блок повторяется столько, сколько сказано в количестве) 1B (Тип стрелочки) 1B (количество) ...
// Пример:
// 00 01 (чанк 0x1)  00 04 (1 тип 4 раза) 00 00 (координаты 0x0; поворот 0; отражение 0)
