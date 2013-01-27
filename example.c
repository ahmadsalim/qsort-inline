#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qsort-inline.h"

struct tagPerson {
  int age;
  char* name;
};

//Needs typedef's for complex types as type is a part of generated function name
typedef struct tagPerson* Person;

//Construct a person
Person make_person(int age, const char *name) {
  Person p = malloc(sizeof(struct tagPerson));
  if (!p) goto ret;
  size_t n = strlen(name);
  p->age = age;
  p->name = malloc(sizeof(char)*n);
  if (!(p->name))
    goto cleanup;
  strcpy(p->name, name);
  goto ret;
cleanup:
  free(p);
  p = NULL;
ret:
  return p;
}

//Delete a person
void delete_person(Person p) {
  if (!p) return;
  if (p->name) free(p->name);
  free(p);
}

//Define comparator as usual (Though notice that it is typesafe. This will sort by age, then by name.)
int Personcmp(Person * pa, Person * pb) {
  int agecmp = (*pa)->age - (*pb)->age;
  if (!agecmp) {
    return strcmp((*pa)->name, (*pb)->name);
  }
  return agecmp;
}

//Define quicksort overload for Person
DEF_QSORT(Person, Personcmp)

int main()
{
#define N 5
  Person arr[N];
  //Construct persons with random names and ages
  arr[0] = make_person(18, "Peter Peterson");
  arr[1] = make_person(20, "Jack Peterson");
  arr[2] = make_person(53, "Hansel Georgeson");
  arr[3] = make_person(18, "Alexander McWright");
  arr[4] = make_person(64, "Elizabeth Reader");

  QSORT(Person, Personcmp) (arr, N);
  int i = 0;

  //Print persons
  for (i = 0; i < N; i++) {
    if (arr[i])
      printf("Person { age: %d, name: %s }\n", arr[i]->age, arr[i]->name);
  }

  //Delete persons
  for (i = 0; i < N; i++) {
    delete_person(arr[i]);
    arr[i] = NULL;
  }
  return 0;
}
