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
  __gc_root = gc_malloc( sizeof( gc_root) );
  gc_obj* obj = gc_obj_new(NULL);
  gc_ref* ref = gc_ref_new(obj, obj);
  __gc_root->obj_head = obj;
  __gc_root->obj_tail = obj;
  __gc_root->ref_head = ref;
  __gc_root->ref_tail = ref;
  return __gc_root;
}

gc_obj* gc_obj_new(void* value) 
{
  gc_obj* obj = gc_malloc( sizeof( gc_obj ) );
  obj->marked = 1;
  obj->value = value;
  return gc_obj;
}

void gc_ref_new(gc_obj* father, gc_obj* son)
{
  gc_ref* ref = gc_malloc( sizeof( gc_ref ) );
  ref->father = father;
  ref->son = son;
  ref->next = NULL;
  __gc_root->ref_tail->next = ref;
  __gc_root->ref_tail = ref;
}

gc_obj* gc_global_obj_new(void* value) 
{
  gc_obj* obj = gc_obj_new(value);
  gc_ref_new(__gc_root->obj_root, obj);
  return obj;
}
