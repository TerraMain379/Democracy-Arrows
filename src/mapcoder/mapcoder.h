#include <stdint.h>

#include "../world/world.h"

char* encodeWorld(struct World* world, size_t* resultLen);
struct World* decodeWorld(char* base64, size_t base64len);
