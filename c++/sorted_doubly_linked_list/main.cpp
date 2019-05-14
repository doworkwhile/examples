#include <stdio.h>
#include "sorted_double_linked_list.h"


void printListTwice(SortedDoubleLinkedList* list) {
  DoubleLink* cur = list->head;
  for (int i = 0; i < (list->size * 2); i++) {
    printf("%d: (%p) = %d\n", i, cur, cur->value);
    cur = cur->next;
  }
}

void printList(SortedDoubleLinkedList* list) {
  DoubleLink* cur = list->head;
  for (int i = 0; i < list->size ; i++) {
    printf("%d: (%p) = %d\n", i, cur, cur->value);
    cur = cur->next;
  }
}

void printDoubleLink(DoubleLink* link) {
  printf("I = %p (%d); NEXT = %p; PREV = %p;\n",
    link, link->value, link->next, link->prev
  );
}

int main() {

  DoubleLink link1 = DoubleLink(1);
  DoubleLink link2 = DoubleLink(2);
  DoubleLink link3 = DoubleLink(3);
  DoubleLink link4 = DoubleLink(4);
  DoubleLink link5 = DoubleLink(5);
  SortedDoubleLinkedList list = SortedDoubleLinkedList();

  printf("Create the list with missing link at index 1\n");
  list.addLinkAtEnd(&link1);
  list.addLinkAtEnd(&link3);
  list.addLinkAtEnd(&link4);
  list.addLinkAtEnd(&link5);
  printList(&list);

  printf("\nAdd in the missing link at index 1\n");
  list.insertLinkAtIndex(&link2, 1);
  printList(&list);

  printf("\nSwap indexes 1 and 3\n");
  list.swapLinks(1, 3);
  printList(&list);

  printf("\nSwap indexes 2 and 3\n");
  list.swapLinks(2, 3);
  printList(&list);

  printf("\nSwap indexes 3 and 2\n");
  list.swapLinks(3, 2);
  printList(&list);

  printf("\nSwap indexes 0 and 4\n");
  list.swapLinks(0, 4);
  printList(&list);

  printf("\nSwap indexes 3 and 1\n");
  list.swapLinks(3, 1);
  printList(&list);

  printf("\nSwap indexes 4 and 0\n");
  list.swapLinks(4, 0);
  printList(&list);

  printf("\nShuffle the list\n");
  list.shuffle();
  printList(&list);
}