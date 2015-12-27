#include "gc.h"

#include <stdlib.h>
#include <assert.h>

void gc_marker(GC* gc, GCObject* obj) {
    obj->marked = 1;
}

void gc_destroyer(GC* gc, GCObject* obj) {
    gc_free(gc, obj, sizeof(GCObject));
}

GC* gc_init() {
    GC* gc = malloc(sizeof(GC));
    gc->allocated = 0;
    gc->threshold = 100; // 5 MB;
    gc->obj_cnt = 0;

    gc->listener_cnt = 0;
    int i = 0;
    for(i = 0; i < 10; i++) {
        gc->markers[i] = NULL;
        gc->destroyers[i] = NULL;
    }
    // root object.
    gc->root = NULL;

    gc->_init_obj.marked = 0;
    gc->_init_obj._gc_next = NULL;
    gc->_init_obj.listener_idx = 0;
    gc->first = &gc->_init_obj;
    gc->last = &gc->_init_obj;

    gc_add_listener(gc, gc_marker, gc_destroyer);
    return gc;
}

int gc_add_listener(GC *gc, void (*marker)(GC*, GCObject*), void (*destroyer)(GC *, GCObject*)) {
    assert(gc->listener_cnt < GC_LISTENERS_MAX);
    assert(destroyer != NULL);
    gc->markers[gc->listener_cnt] = marker;
    gc->destroyers[gc->listener_cnt] = destroyer;
    gc->listener_cnt++;
    return gc->listener_cnt-1;
}

void gc_info(GC* gc) {
    printf("sizeof(GC)=%d\n", sizeof(GC));
    printf("sizeof(GCObject)=%d\n", sizeof(GCObject));
    printf("gc->allocated=%d\n", gc->allocated);
    printf("gc->threshold=%d\n", gc->threshold);
    printf("gc->obj_cnt=%d\n", gc->obj_cnt);
    printf("gc->listener_cnt=%d\n", gc->listener_cnt);
    int i;
    for(i=0;i<gc->listener_cnt;i++) {
        printf("gc->markers[%d]=%p\n", i, gc->markers[i]);
        printf("gc->destroyers[%d]=%p\n", i, gc->destroyers[i]);
    }
}

void gc_deinit(GC* gc) {
    // gc_info(gc);
    // start from second object.
    GCObject* obj = gc->first->_gc_next;
    while (obj != NULL) {
        GCObject* next = obj->_gc_next;
        gc_destroy(gc, obj);
        obj = next;
    }
    gc->obj_cnt = 0;

    if (gc->allocated != 0) {
        fprintf(stderr, "memeory leaks");
    }

    free(gc);
}

void gc_mark(GC *gc, void *_obj) {
    GCObject* obj = (GCObject*) _obj;
    if (obj->marked == 1) {
        return;
    }
    obj->marked = 1;
    if (gc->markers[obj->listener_idx] != NULL) {
        gc->markers[obj->listener_idx] (gc, obj);
    }
}

void gc_destroy(GC* gc, GCObject* obj) {
    gc->destroyers[obj->listener_idx](gc, obj);
}

void gc_collect(GC* gc) {
    if (gc->root == NULL) return;

    GCObject* obj = gc->first;
    while (obj != NULL) {
        obj->marked = 0;
        obj = obj->_gc_next;
    }

    // first object will never be deleted.
    gc->first->marked = 1;
    gc_mark(gc, gc->root);
}

void gc_sweep(GC* gc) {
    GCObject* obj = gc->first;

    // first object is a hidden object in gc.
    // will never be destroyed.
    GCObject* next = obj->_gc_next;

    while (next != NULL) {
        if (next->marked == 0) {
            gc->obj_cnt--;
            obj->_gc_next = next->_gc_next;
            gc_destroy(gc, next);
            next = obj->_gc_next;
        } else {
            obj = next;
            next = next->_gc_next;
        }
    }
    // last object may change after sweep.
    // first object will never change.
    gc->last = obj;
}

void* gc_malloc(GC* gc, size_t size){
  void* block = malloc(size);
  if(block == NULL) {
    return NULL;
  }
  gc->allocated += size;
  if (gc->allocated > gc->threshold) {
      gc_collect(gc);
      gc_sweep(gc);
      gc->threshold = gc->allocated * 2;
  }
  return block;
}

void gc_free(GC* gc, void* ptr, size_t size) {
  free(ptr);
  gc->allocated -= size;
}

GCObject* gc_new_obj(GC *gc, int size, int listener){
    GCObject* obj = gc_malloc(gc, size);
    obj->marked = 1;
    obj->listener_idx = listener;
    obj->_gc_next = NULL;
    gc->last->_gc_next = obj;
    gc->last = obj;
    gc->obj_cnt++;
    return obj;
}

GCObject* gc_root_obj(GC* gc, int size, int listener) {
    GCObject *obj = gc_new_obj(gc, size, listener);
    gc->root = obj;
    return gc->root;
}
