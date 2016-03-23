#include "oopc.h"


typedef struct _Array {
    struct _ArrayProto prototype;
    int size;
    int capacity;
    void* elements;
}Array;

typedef struct _ArrayProto {
    int (*size)(Array*);
    void* (*get)(Array*, int);
    void (*set)(Array*, int, void*);
    int (*insert)(Array*, int, void*);
    void (*remove)(Array*, void*);
} ArrayProto;

ArrayProto array_proto = {
    Array_size,
    Array_get,
    Array_set,
    Array_insert,
    Array_remove
};
