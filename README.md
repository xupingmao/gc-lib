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
        struct gc_obj* object_pool;
        struct gc_ref* ref_pool;
    }gc_root;
    gc对象
    typedef struct gc_obj
    {
      int type;
      int marked;
      void* value;
    }gc_obj;
    引用对象
    typedef struct gc_ref
    {
        struct gc_object* src;
        struct gc_object* des;
    }gc_ref;


functions
-------
    void gc_init() :init gc_lib
    void* gc_malloc();
    void gc_free(void* ptr);
    void gc_track(void*value) : track object
