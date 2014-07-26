
#ifndef gc_h
#define gc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gc_obj
{
  int marked;
  void* value;
  struct gc_ref* ref_head;
  struct gc_ref* ref_tail;
}gc_obj;

typedef struct gc_ref
{
  gc_obj* parent;
  gc_ref* next;
}gc_ref;
  
/*
typedef struct gc_root
{
  int obj_used; // 已使用的对象数量
  int ref_used; // 已使用的引用数量
  int obj_total; // 全部对象的数量
  int ref_total; // 全部引用的数量
  gc_obj* obj_pool; // 存放对象的内存池
  gc_ref* ref_pool; // 存放引用的内存池
}gc_root;
*/

gc_obj* __gc_root;

gc_obj* gc_init();
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
