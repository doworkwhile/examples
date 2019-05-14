#include <stdio.h>
#include <cstdlib>
#include <ctime>
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
  srand(time(NULL));
  int maxRand = 100;

  int v1 = rand() % maxRand;
  int v2 = rand() % maxRand;
  int v3 = rand() % maxRand;
  int v4 = rand() % maxRand;
  int v5 = rand() % maxRand;
  printf(
    "Create 5 random values: %d - %d - %d - %d - %d\n",
    v1, v2, v3, v4, v5
  );

  DoubleLink link1 = DoubleLink(v1);
  DoubleLink link2 = DoubleLink(v2);
  DoubleLink link3 = DoubleLink(v3);
  DoubleLink link4 = DoubleLink(v4);
  DoubleLink link5 = DoubleLink(v5);
  SortedDoubleLinkedList list = SortedDoubleLinkedList();

  printf("Insert the items into a list\n");
  printf("The function should ensure ascending order!\n");
  list.insert(&link1);
  list.insert(&link2);
  list.insert(&link3);
  list.insert(&link4);
  list.insert(&link5);
  printList(&list);

  printf("Swap indexes 1 and 3\n");
  list.swapLinks(1, 3);
  printList(&list);

  printf("Swap indexes 2 and 3\n");
  list.swapLinks(2, 3);
  printList(&list);

  printf("Swap indexes 3 and 2\n");
  list.swapLinks(3, 2);
  printList(&list);

  printf("Swap indexes 0 and 4\n");
  list.swapLinks(0, 4);
  printList(&list);
  printf("The list should now be reversed!\n");

  printf("Swap indexes 3 and 1\n");
  list.swapLinks(3, 1);
  printList(&list);

  printf("Swap indexes 4 and 0\n");
  list.swapLinks(4, 0);
  printList(&list);
  printf("The list should now be back in sorted order!\n");

  printf("Knuth Shuffle the list\n");
  list.shuffle();
  printList(&list);
}