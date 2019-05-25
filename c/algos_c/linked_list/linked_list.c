#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
} LinkedList;

Node* Node_Create(int v, Node* next)
{
	Node* ret = (Node*) calloc(1, sizeof(Node));
	ret->value = v;
	ret->next = next;
	return ret;
}

LinkedList* LinkedList_Create()
{
	return (LinkedList*) calloc(1, sizeof(LinkedList));
}

void LinkedList_AddSorted(LinkedList* ll, int value)
{
	if (!ll->head) {
		ll->head = Node_Create(value, NULL);
		return;
	}

	if (value < ll->head->value) {
		ll->head = Node_Create(value, ll->head);
		return;
	}

	Node* current = ll->head;
	while (current->next && current->next->value < value) {
		current = current->next;
	}
	current->next = Node_Create(value, current->next);
}

void LinkedList_Free(LinkedList* ll)
{
	Node* current = ll->head;
	while (current) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}
	free(ll);
}

Node* LinkedList_Find(LinkedList* ll, int findVal)
{
	Node* current = ll->head;
	while (current) {
		if (current->value == findVal) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

int main()
{
	LinkedList* ll = LinkedList_Create();
	LinkedList_AddSorted(ll, 30);
	LinkedList_AddSorted(ll, 20);
	LinkedList_AddSorted(ll, 10);
	printf("%p %d\n", ll->head, ll->head->value);
	printf("%p %d\n", ll->head->next, ll->head->next->value);
	printf("%p %d\n", ll->head->next->next, ll->head->next->next->value);
	Node* toFind = ll->head->next;
	Node* found = LinkedList_Find(ll, toFind->value);
	printf(
		"finding node with value %d (%p): %p %s\n",
		toFind->value,
		toFind,
		found,
		found == toFind ? "Success!" : "Failure!"
	);
	LinkedList_Free(ll);
}