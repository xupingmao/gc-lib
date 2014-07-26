gc_lib
======

this is a gc library for c language.


struct
-------
    gc树
    typedef struct gc_root{
        int obj_cap;
        int obj_size;
        int ref_cap;
        int ref_size;
        struct gc_obj* obj_root;
        struct gc_obj* obj_tail;
        struct gc_ref* ref_root;
        struct gc_ref* ref_tail;
    }gc_root;
    gc对象
    typedef struct gc_obj
    {
      int marked;
      void* value;
      gc_obj* next;
    }gc_obj;
    引用关系
    typedef struct gc_ref
    {
        struct gc_obj* src;
        struct gc_obj* des;
        struct gc_ref* next;
    }gc_ref;


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
