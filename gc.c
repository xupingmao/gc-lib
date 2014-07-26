#include "gc.h"


void gc_error(char* msg)
{
  printf(msg);
  exit(-1);
}

void* gc_malloc( size_t size )
{
  void* block = malloc( size );
  if( block == NULL )
  {
    gc_error("not enough memery");
  }
  return block;
}

void gc_free( void* ptr) 
{
  free(ptr);
}


gc_root* gc_init()
{
  __gc_root = gc_obj_new("root");
  return __gc_root;
}

gc_obj* gc_obj_new(void* value) 
{
  gc_obj* obj = gc_malloc( sizeof( gc_obj ) );
  obj->marked = 1;
  obj->value = value;
  obj->ref_head = NULL;
  obj->ref_tail = NULL;
  return gc_obj;
}

void gc_ref_new(gc_obj* father, gc_obj* son)
{
  gc_ref* tail = father->ref_tail;
  if( tail == NULL ){
    father->ref_tail = son;
    father->ref_head = son;
  }else{
    tail->next = son;
    father->ref_tail = son;
  }
}

gc_obj* gc_global_obj_new(void* value) 
{
  gc_obj* obj = gc_obj_new(value);
  gc_ref_new(__gc_root, obj);
  return obj;
}
