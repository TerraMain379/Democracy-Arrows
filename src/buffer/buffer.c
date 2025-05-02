#include "./buffer.h"

static struct Block {
  void* value;
  struct Block* next;
  struct Block* prev;
};
static struct Header {
  struct Block* first;
  struct Block* last;
};

void* get(struct Buffer* buffer, int index) {
  if (index>=buffer->size) return 0;
  struct Header* header = buffer->ctx;
  struct Block* block = header->first;
  if (index*2<=buffer->size) {
    for (int i = 0; i < index; i++) {
      block = block->next;
    }
  }
  else {
    for (int i = buffer->size-1; i > index; i--) {
      block = block->prev;
    }
  }
  return block->value;
}
void _set(struct Buffer* buffer, int index, void* value) {
  if (index>=buffer->size) return 0;
  struct Header* header = buffer->ctx;
  struct Block* block = header->last;
  if (index*2<=buffer->size) {
    for (int i = 0; i < index; i++) {
      block = block->next;
    }
  }
  else {
    for (int i = buffer->size-1; i > index; i--) {
      block = block->prev;
    }
  }
  block->value = value;
}
void _add(struct Buffer* buffer, void* value) {
  struct Block* block = malloc(sizeof(struct Block));
  struct Header* header = buffer->ctx;
  block->value = value;
  block->prev = header->last;
  header->last->next = block;
  header->last = block;
  buffer->size++;
}
void _insert(struct Buffer* buffer, int index, void* value) {
  if (index>buffer->size) return 0;
  struct Header* header = buffer->ctx;
  struct Block* block = header->last;
  if (index*2<=buffer->size) {
    for (int i = 0; i < index; i++) {
      block = block->next;
    }
  }
  else {
    for (int i = buffer->size-1; i > index; i--) {
      block = block->prev;
    }
  }
  struct Block* newBlock = malloc(sizeof(struct Block));
  newBlock->value = value;

  if (block) {
    if (block->prev) {
      newBlock->prev = block->prev;
    }
    else {
      header->first = newBlock;
    }
    newBlock->next = block;
    block->prev->next = newBlock;
    block->next = newBlock;
  }
  else {
    newBlock->prev = header->last;
    newBlock->next = 0;
    header->last = newBlock;
  }
}
void _remove(struct Buffer* buffer, int index) {
  if (index>=buffer->size) return 0;
  struct Header* header = buffer->ctx;
  struct Block* block = header->last;
  if (index*2<=buffer->size) {
    for (int i = 0; i < index; i++) {
      block = block->next;
    }
  }
  else {
    for (int i = buffer->size-1; i > index; i--) {
      block = block->prev;
    }
  }
  if (block->prev) block->prev->next = block->next;
  if (block->next) block->next->prev = block->prev;
  free(block);
}
void _clear(struct Buffer* buffer) {
  struct Block* block = header->last;
  for (int i = 0; i < index; i++) {
    block = block->next;
    free(block->prev);
  }
  free(block);
  free(buffer);
}

struct Buffer* Buffer_new() {
  struct Buffer* buffer = malloc(sizeof(struct Buffer));
  buffer->size = 0;
  struct Header* header = malloc(sizeof(struct Header));
  buffer->ctx = header;

  buffer->get = _get;
  buffer->set = _set;
  buffer->add = _add;
  buffer->insert = _insert;
  buffer->remove = _remove;
  buffer->clear = _claer;
  return buffer;
}

