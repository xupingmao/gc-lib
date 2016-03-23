
#include "oopc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Number {
    long value;
    struct _NumberProto * prototype;
} Number;

typedef struct _NumberProto {
    Number* (*add)(Number*, Number*);
    Number* (*mul)(Number*, Number*);
    void (*inc)(Number*, long value);
} NumberProto;

Number* NumberNew();

Number* Number_add(Number*self, Number* b) {
    Number* n = NumberNew();
    n->value = self->value + b->value;
    return n;
}

void Number_inc(Number*self, long v) {
    self->value += v;
}

Number* Number_mul(Number*self, Number* tar) {
    Number* n = NumberNew();
    n->value = self->value * tar->value;
    return n;
}

struct _NumberProto numberProto = {
    Number_add,
    Number_mul,
    Number_inc};

Number* NumberNew() {
    oopc_new(Number, number, &numberProto);
    return number;
}

int main(int argc, char* argv[]) {
    Number* a = NumberNew();
    Number* b = NumberNew();
    a->value = 10;
    b->value = 20;
    Number* c = call1(a, add, b);
    printf("c=%d\n", c->value);

    free(a);
    free(b);
    free(c);
    return 0;
}
