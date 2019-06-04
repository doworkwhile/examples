#include <stdio.h>
#include <stdlib.h>

typedef struct HuffmanLeaf {
	char c;
	int f;
	struct HuffmanLeaf* left;
	struct HuffmanLeaf* right;
	char* p;
	int pLen;
} HuffmanLeaf;

HuffmanLeaf* createLeaf(char c, int f)
{
	HuffmanLeaf* temp = (HuffmanLeaf*) calloc(1, sizeof(HuffmanLeaf));
	temp->c = c;
	temp->f = f;
	temp->left = NULL;
	temp->right = NULL;
	temp->p = NULL;
	temp->pLen = 0;
	return temp;
}


typedef struct HuffmanLLNode {
	struct HuffmanLLNode* next;
	HuffmanLeaf* data;
} HuffmanLLNode;

HuffmanLLNode* insertAt(HuffmanLLNode* head, HuffmanLeaf* h)
{
	HuffmanLLNode* temp = (HuffmanLLNode*) calloc(1, sizeof(HuffmanLLNode));
	temp->data = h;

	if (head == NULL) {
		return temp;
	}

	if (h->f < head->data->f) {
		temp->next = head;
		return temp;
	}

	HuffmanLLNode* search = head;
	while (search->next && search->next->data->f < h->f) {
		search = search->next;
	}
	temp->next = search->next;
	search->next = temp;
	return head;
}

void freeTree(HuffmanLeaf* top)
{
	if (top == NULL) {
		return;
	}

	freeTree(top->left);
	freeTree(top->right);
	free(top->p);
	free(top);
}

void printTree(HuffmanLeaf* top, int depth)
{
	if (top == NULL) {
		return;
	}
	printTree(top->right, depth + 1);
	for (int i = 0; i < depth; i++) {
		printf("-----|");
	}
	printf("(%c %d %s)\n", top->c, top->f, top->p);
	printTree(top->left, depth + 1);
}

void printList(HuffmanLLNode* head)
{
	if (head == NULL) {
		printf("\n");
		return;
	}

	printf("[ %d", head->data->f);
	HuffmanLLNode* search = head->next;
	if (search) {
		printf(", ");
	}
	while (search) {
		printf("%d", search->data->f);
		search = search->next;
		if (search) {
			printf(", ");
		}
	}
	printf(" ]\n");
}


HuffmanLeaf* buildTree(HuffmanLLNode* head)
{
	HuffmanLeaf* ret = NULL;
	while (head) {
		HuffmanLLNode* popFirst = head;
		HuffmanLLNode* popSecond = head->next;

		if (popSecond == NULL) {
			break;
		}
		head = popSecond->next;

		int insVal = popFirst->data->f + popSecond->data->f;
		HuffmanLeaf* comboLeaf = createLeaf(*"$", insVal);
		comboLeaf->left = popFirst->data;
		comboLeaf->right = popSecond->data;
		head = insertAt(head, comboLeaf);

		free(popFirst);
		free(popSecond);
	}
	if (head) {
		ret = head->data;
		free(head);
	}
	return ret;
}

void buildPrefixes(HuffmanLeaf* top, HuffmanLeaf* last, int wasRight)
{
	if (top == NULL) {
		return;
	}

	if (last) {
		top->pLen = last->pLen + 1;
		top->p = (char*) calloc(top->pLen + 1, sizeof(char));
		top->p[top->pLen] = '\0';
		top->p[top->pLen - 1] = wasRight ? '1' : '0';
		for (int i = 0; i < last->pLen; i++) {
			top->p[i] = last->p[i];
		}
	}

	buildPrefixes(top->left, top, 0);
	buildPrefixes(top->right, top, 1);
}

// void gatherPrefixes(HuffmanLeaf* head, int* )

int main()
{
	int alphabetLen = 26;
	// sorted by freq asc
	char c[alphabetLen]; // char
	int f[alphabetLen]; // freq
	char* p[alphabetLen]; // prefix

	// create linked list of sorted nodes
	// prefer linked list to array because:
	// insertions will be much faster, the new items are usually added
	// within the first few indexes so we don't have to shift array items
	// by most of N
	HuffmanLLNode* head = NULL;
	for (int i = 0; i < alphabetLen; i++) {
		c[i] = 97 + i;
		f[i] = i + 1;
		p[i] = "";
		head = insertAt(head, createLeaf(c[i], f[i]));
	}
	printList(head);

	// build the tree with the linked list
	// the buildTree function deallocates the items in the list
	HuffmanLeaf* top = buildTree(head);

	// traverse the tree to create the prefixes
	buildPrefixes(top, 0, 0);

	printTree(top, 0);
	freeTree(top);

	return 0;
}