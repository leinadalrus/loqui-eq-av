#include "tweened_spring_enum.h"

TweenedSpringItem_t *TweenedSpringItem_Create(TweenedSpringItem_t *self) {
  /* &self = new TweenedSpringItem_t{}; */
  std::memset(self, std::sizeof(TweenedSpringItem_t));
  std::move(self); // ? ...
  return (char*)0;
}
