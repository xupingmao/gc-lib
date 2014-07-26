
#ifndef gc_h
#define gc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gc_obj
{
  int marked;
  void* value;
}gc_obj;

typedef struct gc_ref
{
  gc_obj* parent;
  gc_obj* child;
}gc_ref;
  
typedef struct gc_root
{
  int pool_size;
  int obj_used;
  int ref_used;
  int obj_total;
  int ref_total;
  gc_obj* obj_pool;
  gc_ref* ref_pool;
}gc_root;


gc_root* __gc_root;

gc_root* gc_init();
void gc_destroy();
void gc_error(char*msg);
void* gc_malloc(size_t size);
void gc_free(void* ptr);
gc_obj* gc_obj_new(void* value);
gc_ref* gc_ref_new(gc_obj*parent, gc_obj*child);
gc_obj* gc_global_obj_new(void* value);
void gc_mark(gc_obj* obj);
void gc_collect();
void gc_sweep();

#endif
