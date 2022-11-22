#include "message_cycle.h"

MessageCycle::~MessageCycle() {
  free(head);
  delete[] head;
  head = 0;
  free(tail);
  delete[] tail;
  tail = 0;
  free(buffer);
  delete[] buffer;
  buffer = 0;
} // ...(self); // to destroy

void MessageCycle::messageBuffer(std::string) {}

void MessageCycle::cycle(LinkedList *) {}

