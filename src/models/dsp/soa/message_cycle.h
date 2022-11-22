#include "linkedlist.h"
#include <corecrt_malloc.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint> // for uint8_t type
#include <fstream>
#include <stdint.h>
#include <memory>
#include <vector>

#ifndef BF3212BB_C8DE_43F8_B2BE_BBABEE88CD4E
#define BF3212BB_C8DE_43F8_B2BE_BBABEE88CD4E

class MessageCycle: public LinkedList {
public:
    MessageCycle(): head(0) {
        auto selfbuf = new MessageCycle();
        selfbuf->head = 0;
        selfbuf->tail = 0;
        selfbuf->buffer = new uint8_t;
    }

    MessageCycle(const char[]);
    ~MessageCycle();

    void messageBuffer(std::string);

private:
    LinkedList *head;
    LinkedList *tail;
    uint8_t *buffer;

    char key;
    int value;

    auto read_cin(std::istream &cinput);
    auto get_read_cin();

    void cycle(LinkedList*);
    void notationsInput(std::istream &strval);
    auto expressionMatch(std::string);

protected:
    int checkAvailableData(uint8_t data, int amount);
    int checkAvailableSpace(uint8_t data, int amount);

    std::vector<std::string> tail_manager;
};

#endif /* BF3212BB_C8DE_43F8_B2BE_BBABEE88CD4E */
