// Attribution: Dale Stanbrough (RMIT) - Advanced Programming Techniques
// Author: Daniel Surla

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <vector>

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // int currentNode(Node *nodePtr);

  LinkedList *getHead() { return head; }
  LinkedList *getTail() { return tail; }

  LinkedList *clearNode();
  LinkedList *nextNode();
  void previousNode();

  void displayList();

  //   int find();

private:
  LinkedList *head;
  // NOTE(Daniel): Treat individual index as a value.
  LinkedList *tail; // last/back-of-list value

  LinkedList *nextIdx;
  LinkedList * previousIdx; // treat these as like cursor functions

  LinkedList * node; // current node

  char key;
  int value;
  // NOTE(Daniel): private member-based functions are great for recursion
  LinkedList *get(LinkedList *linked_list);
  int currentNode(int index);
  void displayList(LinkedList *linked_list);
  void notationsInput();

  std::vector<char> fileConstraints = std::vector<char>();
  // std::vector<char> playerInputs = std::vector<char>();

  const int GAME_BOARD_GRID_MAX_SIZE = 100;
};

#endif // LINKED_LIST_H
