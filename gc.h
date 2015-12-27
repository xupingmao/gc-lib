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
    char listener_idx;   \
    void* _gc_next;

typedef struct _GCObject {
    GC_HEADER
} GCObject;

typedef struct _GC {
    int threshold;
    int allocated;
    int obj_cnt;
    int listener_cnt;
    void (*markers[GC_LISTENERS_MAX]) (struct _GC* gc, GCObject *obj); // ten listeners at most;
    void (*destroyers[GC_LISTENERS_MAX])(struct _GC* gc, GCObject* obj); // mark functions.
    int obj_sizes[GC_LISTENERS_MAX]; // object size
    GCObject _init_obj;
    GCObject *root;
    GCObject *first;
    GCObject *last;
}GC;

GC* gc_init();
void gc_deinit(GC* gc);
int gc_add_listener(GC* gc, void (*marker)(GC* gc, GCObject* obj), void (*destroyer)(GC* gc, GCObject* obj));

void* gc_malloc(GC* gc, size_t size);
GCObject* gc_new_obj(GC* gc, int size, int listener);
void gc_free(GC* gc, void* ptr, size_t size);
void gc_mark(GC* gc, void* obj);
void gc_destroy(GC* gc, GCObject* obj);
void gc_sweep(GC* gc);

void gc_info(GC* gc);

#endif
