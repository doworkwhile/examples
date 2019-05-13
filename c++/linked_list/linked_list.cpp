#include <stdio.h>

class Link
{
public:
  Link(int value);
  ~Link();

  int value;
  Link* next;
};

Link::Link(int value) {
  this->value = value;
}

Link::~Link() {}

class LinkedList
{
public:
  LinkedList();
  ~LinkedList();

  Link* first;
  Link* getIndex(int index);
};

LinkedList::LinkedList() {}
LinkedList::~LinkedList() {}
Link* LinkedList::getIndex(int index) {
  Link* r = this->first;
  for (int i = 0; i < index; i++) {
    r = r->next;
  }
  return r;
}


void printLinkPointerLocation(Link* l) {
  printf(
    "Link @ %p, value = %d, next = %p\n",
    (void*) l,
    l->value,
    (void*) l->next
  );
}

int main() {
  Link l1 = Link(2 << 0);
  Link l2 = Link(2 << 1);
  Link l3 = Link(2 << 2);
  Link l4 = Link(2 << 3);
  Link l5 = Link(2 << 4);
  LinkedList list = LinkedList();

  list.first = &l1;
  l1.next = &l2;
  l2.next = &l3;
  l3.next = &l4;
  l4.next = &l5;
  l5.next = &l1;

  printf("print locations by calling ->next\n");
  printLinkPointerLocation(list.first);
  printLinkPointerLocation(list.first->next);
  printLinkPointerLocation(list.first->next->next);
  printLinkPointerLocation(list.first->next->next->next);
  printLinkPointerLocation(list.first->next->next->next->next);
  printLinkPointerLocation(list.first->next->next->next->next->next);

  printf("print locations by calling .getIndex(i)\n");
  printLinkPointerLocation(list.getIndex(0));
  printLinkPointerLocation(list.getIndex(1));
  printLinkPointerLocation(list.getIndex(2));
  printLinkPointerLocation(list.getIndex(3));
  printLinkPointerLocation(list.getIndex(4));
  printLinkPointerLocation(list.getIndex(5));

  printf("Wrapped?: %s\n", list.first == list.getIndex(5) ? "true" : "false");

  return 0;
}