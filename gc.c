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
  __gc_root = gc_malloc( sizeof( gc_obj ));
  char *description = "gc_lib_root"
  char *value = gc_malloc( strlen(description) + 1);
  strcpy(value, mem);
  __gc_root->ref_head = NULL;
  __gc_root->ref_tail = NULL;
  __gc_root->value = value;
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

void gc_ref_new(gc_obj* parent, gc_obj* child)
{
  gc_ref* ref = gc_malloc(sizeof(gc_ref));
  
  if( parent->ref_tail == NULL ){
    ref->ref = parent;
    ref->next = NULL;
    parent->ref_tail = ref;
    parent->ref_head = ref;
  }else{
    ref->ref = child;
    ref->next = NULL;
    parent->ref_tail->next = ref;
    parent->ref_tail = ref;
  }
}

gc_obj* gc_global_obj_new(void* value) 
{
  gc_obj* obj = gc_obj_new(value);
  gc_ref_new(__gc_root, obj);
  return obj;
}
