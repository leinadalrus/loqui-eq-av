#include "nmt_ffnn.h"
#include "nmt_ffnn_data.h"
#include <cstring>
#include <string>

NMTFeedForwardPrototype_t *NMTFeedForwardImpl_v::create_on_demand(
  NMTFeedForwardPrototype_t *self) {
  // self = memset(self, sizeof(NMTFeedForwardPrototype_t));
  *self = {
    .product_uuid = 0,
    .product_name = "User",
    .stop_words = ""
  };
  // Undefined behavior, source object type 'NMTFeedForwardPrototype_t' is
  // not TriviallyCopyable:
  // memmove(known_memory, &nmt_t, sizeof(NMTFeedForwardPrototype_t));
  return self;
}

char *NMTFeedForwardImpl_v::run_input(NMTFeedForwardPrototype_t *self, char
*input) {
  NMTFeedForwardPrototype_t *nmt_t = create_on_demand(self);
  char *pt;
  char *ret_value;
  const char *str;
  std::string args = nmt_t->stop_words;

  for (auto idx = 0; idx < 26; idx++) {
    str = &args.at(idx);
    pt = input;
    while (*str != '\0' || *str != EOF) {
      if ((*str | 0x20) != (*pt | 0x20)) {
        break;
      } else {
        ret_value = &args[idx]; // NOTE: similar to: str = &args.at(idx);
      }
    }
  }

  return ret_value;
}

int NMTFeedForwardImpl_v::stopwords_update_data(NMTFeedForwardData_t *data,
                                                    const char *args[]) {
  int ret_value = 0;
  char text_lines[64];

  FILE *f = fopen(args[1], "r");

  if (f == nullptr) {
    printf("File is inaccessible or in error: %s", args[1]);
    ret_value = 1;
  }

  fgets(text_lines, 64, f);
  while (fgetc(f)) {
    strtok(text_lines, data->stop_words);
  }

  fclose(f);

  return ret_value;
}
