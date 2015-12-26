gc_lib
======

this is a gc library for c language.


struct
-------
    gc头

```c
#define GC_HEADER \
    char marked;  \
    char listener_idx;   \
    void* _gc_next;
```


global variables
-------
    __gc_root: gc树的根节点;

functions
-------
    void gc_init();
    void gc_destroy();
    void* gc_malloc();
    void gc_free(void* ptr);
    gc_obj gc_obj_new(void *value);
    gc_ref gc_ref_new(gc_obj* src, gc_obj* des);
    void gc_mark(gc_obj* obj);
    void gc_sweep();
    void gc_collect();
