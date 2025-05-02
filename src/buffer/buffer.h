struct Buffer {
  void* ctx;
  int size;
  void* (*get)(struct Buffer*, int);
  void (*set)(struct Buffer*, int, void*);
  void (*add)(struct Buffer*, void*);
  void (*insert)(struct Buffer*, int, void*);
  void (*remove)(struct Buffer*, int);
  void (*free)(struct Buffer*);
};
struct Buffer* Buffer_new();

