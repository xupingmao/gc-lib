/*
 * gc_lib for C language.
 * @author: xupingmao
 * @date: 2015-12-26
 *
 */

#ifndef gc_h
#define gc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GC_LISTENERS_MAX 10
#define GC_HEADER \
    char marked;  \
    void* _gc_next;

typedef struct _GCObject {
    GC_HEADER
} GCObject;


typedef struct _GCProto {
    GCObject* (*newObj) (GC*, int);
    void (*mark)(GC*, GCObject*);
    void (*sweep)(GC*, GCObject*);
    void* (*malloc)(GC*, size_t);
    void* (*free)(GC*, size_t);
}GCProto;

typedef struct _GC {
    GCProto* prototype;
    int threshold;
    int allocated;
    int obj_cnt;
    GCObject _init_obj;
    GCObject *root;
    GCObject *first;
    GCObject *last;
}GC;

GC* GC_init();
void GC_finalize(GC* gc);
void* GC_malloc(GC* gc, size_t size);
GCObject* GC_newObj(GC* gc, int size, int listener);
void GC_free(GC* gc, void* ptr, size_t size);
void GC_mark(GC* gc, void* obj);
void GC_delete(GC* gc, GCObject* obj);
void GC_swepe(GC* gc);
void GC_toString(GC* gc);

GCProto gc_proto = {
    gc_new_obj,
    gc_mark,
    gc_sweep
};

#endif
