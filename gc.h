
#ifndef gc_h
#define gc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gc_obj
{
  int marked;
  void* value;
  struct gc_obj* next;
}gc_obj;

typedef struct gc_ref
{
  gc_obj* src;
  gc_obj* des;
  gc_ref* next;
}gc_ref;
  
typedef struct gc_root
{
  gc_obj* obj_head;
  gc_obj* obj_tail;
  gc_ref* ref_head;
  gc_ref* ref_tail;
}gc_root;


gc_root* __gc_root;

gc_root* gc_init();
void gc_destroy();
void* gc_malloc(size_t size);
void gc_free(void* ptr);
gc_obj* gc_obj_new(void* value);
gc_ref* gc_ref_new(gc_obj*src, gc_obj*des);
gc_obj* gc_global_obj_new(void* value);
void gc_mark(gc_obj* obj);
void gc_collect();
void gc_sweep();

#endif
