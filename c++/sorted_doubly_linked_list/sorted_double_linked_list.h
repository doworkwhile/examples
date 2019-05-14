#ifndef SORTED_DOUBLE_LINKED_LIST_H
#define SORTED_DOUBLE_LINKED_LIST_H

#include "./double_link.h"
#include <string>
#include <cstdlib>
#include <ctime>

class SortedDoubleLinkedList
{
public:
  SortedDoubleLinkedList();
  ~SortedDoubleLinkedList();
  DoubleLink* head;
  int size;

  DoubleLink* tail();
  void addLinkAtEnd(DoubleLink* link);
  DoubleLink* getLinkAtIndex(int index);
  bool insertLinkAtIndex(DoubleLink* link, int index);
  void swapLinks(int i1, int i2);
  void shuffle();
};

SortedDoubleLinkedList::SortedDoubleLinkedList()
{
  head = NULL;
  size = 0;
}
SortedDoubleLinkedList::~SortedDoubleLinkedList() {}

DoubleLink* SortedDoubleLinkedList::tail()
{
  if (head == NULL) {
    return NULL;
  }

  return head->prev;
}

void SortedDoubleLinkedList::addLinkAtEnd(DoubleLink* link)
{
  if (head == NULL) {
    head = link;
    link->prev = link;
    link->next = link;
    size++;
    return;
  }

  link->next = head;
  link->prev = tail();

  tail()->next = link;
  head->prev = link;  

  size++;
}

DoubleLink* SortedDoubleLinkedList::getLinkAtIndex(int index)
{
  if (head == NULL || index < 0) {
    return NULL;
  }

  DoubleLink* found = head;
  for (int i = 0; i < index; i++) {
    found = found->next;
  }
  return found;
}

bool SortedDoubleLinkedList::insertLinkAtIndex(DoubleLink* link, int index)
{
  DoubleLink* at = getLinkAtIndex(index);
  if (at == NULL) {
    return false;
  }

  link->next = at;
  link->prev = at->prev;
  at->prev->next = link;
  at->prev = link;

  size++;

  return true;
}

void SortedDoubleLinkedList::swapLinks(int i1, int i2)
{
  // quick fail conditions
  if (
    i1 == i2 ||
    head == NULL ||
    i1 < 0 ||
    i2 < 0 ||
    i1 % size == i2 % size
  ) {
    return;
  }

  DoubleLink* link1 = getLinkAtIndex(i1);
  DoubleLink* link2 = getLinkAtIndex(i2);

  // 1. store "l2 old prev" and "l1 old next"
  DoubleLink* link2OldPrev = link2->prev;
  DoubleLink* link1OldNext = link1->next;
  bool adjacent = link2OldPrev == link1;

  // -. after each step, follow the link you just set and link back to yourself
  // 2. l2 prev = l1 prev
  // 3. l1 next = l2 next
  link2->prev = link1->prev;
  link2->prev->next = link2;
  link1->next = link2->next;
  link1->next->prev = link1;

  // -. if "l2 old prev" was l1, l2 next = l1, l1 prev = l2. else...
  // -. also no need to follow link and link back (from comment above step 2) 
  // 4. l1 prev = old l2 prev
  // 5. l2 next = old l1 next
  if (adjacent) {
    link2->next = link1;
    link1->prev = link2;
  } else {
    link1->prev = link2OldPrev;
    link1->prev->next = link1;
    link2->next = link1OldNext;
    link2->next->prev = link2;
  }

  // 6. did we swap the head? set it to the other link
  if (i1 == 0) {
    head = link2;
  } else if (i2 == 0) {
    head = link1;
  }
}

void SortedDoubleLinkedList::shuffle()
{
  if (head == NULL) {
    return;
  }

  srand(time(NULL));

  for (int i = size - 1; i > 0; i--) {
    int swapAt = rand() % i;
    swapLinks(swapAt, i);
  }
}

#endif