#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int value;
	struct Node* prev;
	struct Node* next;
} Node;

// calloc a Node* with these values
Node* createNode(int v, Node* n, Node* p)
{
	Node* created = (Node*) calloc(1, sizeof(Node));
	created->value = v;
	created->next = n;
	created->prev = p;
	return created;
}

// attach a node along the double linked list, the new value should be between
// its neighbors
Node* addSorted(Node* head, int v)
{
	if (head == NULL) {
		Node* c = createNode(v, NULL, NULL);
		c->next = c;
		c->prev = c;
		return c;
	}

	if (v < head->value) {
		Node* c = createNode(v, head, head->prev);
		head->prev->next = c;
		head->prev = c;
		return c;
	}

	Node* search = head->next;
	while (search != head) {
		if (v < search->value) {
			break;
		}
		search = search->next;
	}
	Node* c = createNode(v, search, search->prev);
	search->prev->next = c;
	search->prev = c;
	return head;
}

// traverse the list freeing all the nodes from memory
void freeList(Node* head)
{
	if (head == NULL) {
		return;
	}

	Node* search = head->next;
	while (search != head) {
		search = search->next;
		free(search->prev);
	}
	free(head);
}

// print the list using printf
void printList(Node* head)
{
	if (head == NULL) {
		printf("[]\n");
		return;
	}

	printf("[ %d", head->value);

	Node* search = head->next;
	if (search != head) {
		printf(",");
	}
	while (search != head) {
		printf(" %d", search->value);
		search = search->next;
	}
	printf(" ]\n");
}

// find a Node* by the value of the Node
Node* find(Node* head, int v)
{
	if (head == NULL) {
		return NULL;
	}
	if (head->value == v) {
		return head;
	}

	Node* search = head->next;
	while (search != head) {
		if (search->value == v) {
			return search;
		}
		search = search->next;
	}
	return NULL;
}

// return a new head to the right
Node* rotate(Node* head) {
	return head->next;
}

// delete a Node* by the value of the Node
Node* delete(Node* head, int v) {
	Node* found = find(head, v);

	if (found == NULL) {
		return found;
	}

	found->prev->next = found->next;
	found->next->prev = found->prev;

	if (found == head) {
		Node* oldNext = found->next;
		free(found);
		return oldNext;
	}

	free(found);
	return head;
}

// find a Node* by its index in relation to the head
Node* findByIndex(Node* head, int i) {
	if (head == NULL) {
		return NULL;
	}

	if (i == 0) {
		return head;
	}

	int count = 1;
	Node* current = head->next;
	while (count != i) {
		current = current->next;
	}
	return current;
}

// get the index of a Node, found by value,in relation to the head
int getIndex(Node* head, int v) {
	if (head == NULL) {
		return -1;
	}

	if (head->value == v) {
		return 0;
	}

	int count = 1;
	Node* current = head->next;
	while (current != head)  {
		if (current->value == v) {
			return count;
		}
		count++;
	}
	return -1;

}

int main()
{
	Node* head;
	head = addSorted(NULL, 20);
	head = addSorted(head, 10);
	head = addSorted(head, 30);
	printList(head);
	head = rotate(head);
	printList(head);
	head = find(head, 30);
	printList(head);
	head = delete(head, findByIndex(head, getIndex(head, 30))->value);
	printList(head);
	freeList(head);
	return 0;
}