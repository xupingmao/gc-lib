#include "gc.c"

typedef struct _Str {
    GC_HEADER
    char name[20];
    int length;
} Str;

void str_marker(GC* gc, GCObject* obj) {
    obj->marked = 1;
}

void str_destroyer(GC* gc, GCObject* obj) {
    printf("free str %s\n", ((Str*)obj)->name);
    gc_free(gc, obj, sizeof(Str));
}

typedef struct _List {
    GC_HEADER
    Str *names[10];
    int size;
} List;

void list_marker(GC* gc, GCObject* obj) {
    int i;
    List* list = (List*) obj;
    for(i=0;i<list->size;i++) {
        gc_mark(gc, list->names[i]);
    }
}

void list_destroyer(GC* gc, GCObject* obj) {
    gc_free(gc, obj, sizeof(List));
}

int main(int argc, char* argv[]) {
    GC* gc = gc_init();

    int idx = gc_add_listener(gc, str_marker, str_destroyer);
    int listIdx = gc_add_listener(gc, list_marker, list_destroyer);
    List *list = (List*) gc_new_obj(gc, sizeof(List), listIdx);
    list->size = 0;
    gc->root = (GCObject*) list;

    Str *obj = (Str*) gc_new_obj(gc, sizeof(Str), idx);
    Str *obj2 = (Str*) gc_new_obj(gc, sizeof(Str), idx);

    strcpy(obj->name, "test1");
    strcpy(obj2->name, "test2");

    list->names[0] = obj;
    list->names[1] = obj2;
    list->size = 2;

    Str* obj3 = (Str*) gc_new_obj(gc, sizeof(Str), idx);
    Str* obj4 = (Str*) gc_new_obj(gc, sizeof(Str), idx);
    strcpy(obj3->name, "garbage1");
    strcpy(obj4->name, "garbage2");

    gc_collect(gc);
    gc_sweep(gc);

    int i;
    for(i=0;i<list->size;i++) {
        printf("list->names[%d]=%s\n", i, ((Str*) list->names[i])->name);
    }

    gc_info(gc);
    gc_deinit(gc);
    return 0;
}
