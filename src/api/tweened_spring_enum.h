#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

typedef struct TweenedSpringItem_t {
  unsigned long long product_id;
  std::string product_name;
  char *product_offset;
} TweenedSpringItem_t; // this was made over a parameterised (struct*)

typedef struct TweenedSpringItem_v {
  char (*create)(TweenedSpringItem_t *self, char *offset_spec);
  char (*destroy)(TweenedSpringItem_t *self);
} TweenedSpringItem_fn; // : virtual table
/*
(void*)
: is raw, unknown memory. [!] do not prefer this over (char*) ---cast

(char*)
: is a block of memory. [!] preferable cast

Virtual Table
: an allocated array of memory. Great for functions
*/
