
#ifndef MY_VECTOR
#define MY_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// BEG_my_vector
typedef struct Vector{
  int count;
  int limit;
  void** data;
  void (*push_back)(struct Vector*, void*);
  void (*remove)(struct Vector *, int);
  void (*free)(struct Vector *);
} Vector;

// typedef struct my_vector Vector;

void vector_init(Vector*);
void vector_push_back(Vector* self, void* data);
void vector_remove(Vector* self, int index);
void vector_free(Vector* self);

// KEY: realloc
void vector_push_back(Vector* self, void* data){
  if(self -> count == self -> limit){
	self -> limit = self -> limit * 2;
	self -> data = (void**)realloc(self -> data, sizeof(void*) * self -> limit);
  }
  self -> data[self -> count] = data;
  self -> count++;
}

void vector_remove(Vector* self, int index){
  if(index > -1 && index < self -> count){
	// swap the index element and last element
	self -> data[index] = self -> data[self -> count - 1];
	self -> data[self -> count - 1] = NULL;
	self -> count--;
  }
}

void vector_free(Vector* self){
  if(self -> data){
	free(self -> data);
	self -> data = NULL;
  }
}

void vector_init(Vector* self){
  self -> count = 0;
  self -> limit = 4;
  self -> data = (void**)malloc( sizeof(void *) * self -> limit);
  self -> push_back = vector_push_back;
  self -> remove = vector_remove;
  self -> free = vector_free;
}


#endif /* MY_VECTOR */
