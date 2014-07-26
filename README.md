gc_lib
======

this is a gc library for c language.


struct
-------

    typedef struct gc_object
    {
      int marked;
      void* value;
    }gc_object;


functions
-------
    void gc_init() :init gc_lib
    void gc_track(void*value) : track object
