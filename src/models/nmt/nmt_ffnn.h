#ifndef NMT_FFNN_H
#define NMT_FFNN_H

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include "nmt_ffnn_data.h"

/* date = November 19th 2022 0:34 pm */
typedef struct NMTFeedForwardPrototype_t {
  unsigned long long product_uuid;
  const char *product_name; // std::string
  std::string stop_words;
} NMTFeedForwardPrototype_t; // data-structure

class NMTFeedForwardImpl_v {
public:
  NMTFeedForwardPrototype_t *create_on_demand(NMTFeedForwardPrototype_t *self);
  char *run_input(NMTFeedForwardPrototype_t *self, char
  *input);
  int stopwords_update_data(NMTFeedForwardData_t *data,
                            const char *args[]);
  void *destroy(struct interal_t *self);
}; // virtual table

#endif //NMT_FFNN_H
