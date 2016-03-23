#ifndef _OOPC_H
#define _OOPC_H

#define call0(obj, method) (obj)->prototype->method(obj)
#define call1(obj, method, arg1) (obj)->prototype->method((obj), (arg1))
#define call2(obj, method, arg1, arg2) (obj)->prototype->method((obj), (arg1), (arg2))
#define call3(obj, method, arg1, arg2, arg3) (obj)->prototype->method((obj), (arg1), (arg2), (arg3))

#define oopc_new(type, obj, proto) \
    type * obj = malloc(sizeof(type)); \
    obj->prototype = &(proto);


#endif
