#include "oopc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _PersonProto {
    void (*greet)(struct _Person*, char*);
    void (*grow)(struct _Person*, int age);
} PersonProto;

typedef struct _Person {
    char name[20];
    int age;
    PersonProto* prototype;
} Person;

void person_greet(struct _Person *person, char* name) {
    printf("hello, %s, my name is %s\n", name, person->name);
}

void person_grow(struct _Person *person, int age) {
    person->age += age;
    printf("waho! I am %d years old now!", person->age);
}

PersonProto p_proto = {person_greet, person_grow};

int main(int argc, char* argv) {
    oopc_new(Person, person, p_proto);
    
    strcpy(person->name, "test");
    call1(person, greet, "jhon");
    call1(person, grow, 10);
    free(person);
}
