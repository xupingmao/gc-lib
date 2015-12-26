gc_lib
======

A lightweight garbage collector framework for c language.

轻量级C语言垃圾回收框架


## 如何使用

```c
#include "gc.c"

// 自定义类型
typedef struct _Str {
    GC_HEADER
    char name[20];
    int length;
} Str;
typedef struct _List {
    GC_HEADER
    Str *names[10];
    int size;
} List;


// 定义marker函数，标记关联对象
void str_marker(GC* gc, GCObject* obj) {
    obj->marked = 1;
}

void list_marker(GC* gc, GCObject* obj) {
    int i;
    List* list = (List*) obj;
    list->marked = 1;
    for(i=0;i<list->size;i++) {
        str_marker(gc, (GCObject*)(list->names[i]));
    }
}

// 定义destroyer函数，销毁对象
void str_destroyer(GC* gc, GCObject* obj) {
    printf("free str %s\n", ((Str*)obj)->name);
    gc_free(gc, obj, sizeof(Str));
}


void list_destroyer(GC* gc, GCObject* obj) {
    gc_free(gc, obj, sizeof(List));
}

int main(int argc, char* argv[]) {

    // 初始化对象
    GC* gc = gc_init();

    // 使用marker和destroyer接口
    int idx = gc_add_listener(gc, str_marker, str_destroyer);
    int listIdx = gc_add_listener(gc, list_marker, list_destroyer);
    
    // 创建自定义对象
    List *list = (List*) gc_new_obj(gc, sizeof(List), listIdx);
    list->size = 0;
    // 设置跟节点
    gc->root = (GCObject*) list;

    // 完成功能
    
    gc_deinit(gc);
    return 0;
}
```


