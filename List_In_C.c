#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Define the Node structure
typedef struct Node {
	int value;
	struct Node* next;
} Node;


// Function to add a node at the head of the list
Node* addToHead(Node* head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));	// memory for the new node

	if (newNode == NULL) {
		return head;
	}
	newNode->value = value;
	newNode->next = head;

	return newNode;
}

// Function to add a node at the end of the list
Node* addToEnd(Node* head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Memory allocation error\n");
		return head;
	}
	newNode->next = NULL;
	newNode->value = value;

	if (head == NULL) {
		return newNode;
	}

	Node* current = head;
	while (current->next) {
		current = current->next;
	}
	current->next = newNode;

	return head;
}

// Function to add a node at a specific index in the list
Node* addAtIndex(Node* head, int value, int index) {
	if (index < 0) {
		printf("Incorrect index\n");
		return head;
	}
	if (index == 0) {
		return addToHead(head, value);
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Memory allocation error\n");
		return head;
	}
	newNode->value = value;

	Node* current = head;
	for (int i = 0; i < index; ++i) {
		if (!current) {
			printf("Error: the index is out of the list\n");
			free(newNode);
			return head;
		}
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
	return head;
}

// Function to free the entire list
void freeList(Node* head) {
	Node* current = head;
	Node* next;
	while (current) {
		next = current->next;
		free(current);
		current = next;
	}
}

// Function to delete a node by its value
Node* deleteByValue(Node* head, int value) {
	if (head == NULL) {
		printf("List is empty!\n");
		return head;
	}
	if (head->value == value) {
		Node* temp = head;
		head = head->next;
		free(temp);
		return head;
	}

	Node* current = head;

	while (current->next != NULL && current->next->value != value) {
		current = current->next;
	}
	Node* temp = current->next;
	current->next = current->next->next;
	free(temp);
	return head;
}

// Function to delete a node by its index
Node* deleteByIndex(Node* head, int index) {
	if (head == NULL) {
		return head;
	}
	if (index < 0) {
		printf("Incorrect index\n");
		return head;
	}
	if (index == 0) {
		Node* temp = head;
		head = head->next;
		free(temp);
		return head;
	}

	Node* current = head;

	for (int i = 0; i < index; ++i) {
		if (!current) {
			printf("The index goes beyond the list\n");
			return head;
		}
		current = current->next;
	}
	if (current->next = NULL) {
		printf("Error: node not found\n");
		return head;
	}

	Node* temp = current->next;
	current->next = current->next->next;
	free(temp);
	return head;
}

// Function to find a value by index
int findByIndex(Node* head, int index) {
	if (index < 0) {
		printf("Incorrect index\n");
		return head->value;
	}
	if (index == 0) {
		return head->value;
	}
	Node* current = head;
	for (int i = 0; i < index; ++i) {
		if (current == NULL) {
			printf("The index goes beyond the list\n");
			return head->value;
		}
		current = current->next;
	}
	return current->value;
}

// Function to print the list
void printList(Node* head, int index) {
	if (head == NULL) {
		printf("List is empty\n");
		return;
	}
	
	Node* current = head;
	while (current) {
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

// Function to reverse the list
Node* reverse(Node* head) {
	Node* current = head;
	Node* prev = NULL;
	Node* next;

	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	return prev;
}

// Function to perform bubble sort on the list
void bubbleSort(Node* head) {
	if (head == NULL) return;

	int swap;
	Node* current;
	Node* lastSorted = NULL;

	do
	{
		swap = 0;
		current = head;
		while (current->next != lastSorted) {
			if (current->value > current->next->value) {
				int temp = current->value;
				current->value = current->next->value;
				current->next->value = temp;

				swap = 1;
			}
			current = current->next;
		}
		lastSorted = current;

	} while (swap);
}

// Function to split the list into two halves
void splitList(Node* source, Node** left, Node** right) {
	if (source == NULL || source->next == NULL) {
		*left = source;
		*right = NULL;
		return;
	}

	Node* slow = source;
	Node* fast = source->next;

	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	*left = source;
	*right = slow->next;
	slow->next = NULL;

}

// Function to merge two sorted lists into one sorted list
Node* mergeSortedLists(Node* left, Node* right) {
	if (left == NULL) return right;
	if (right == NULL) return left;

	Node* result = NULL;

	if (left->value <= right->value) {
		result = left;
		result->next = mergeSortedLists(left->next, right);
	}
	else {
		result = right;
		result->next = mergeSortedLists(left, right->next);
	}
	return result;

}

// Function to sort the list using merge sort
void mergeSort(Node** headRef) {
	Node* head = *headRef;
	if (head == NULL || head->next == NULL)return;

	Node* left;
	Node* right;
	splitList(head, &left, &right);
	mergeSort(&left);
	mergeSort(&right);
	*headRef = mergeSortedLists(left, right);
}

void test_addToHead();
void test_addToEnd();
void test_deleteByValue();
void test_findByIndex();
void test_printList();

int main() {
	
	test_addToHead();
	test_addToEnd();
	test_deleteByValue();
	test_findByIndex();
	test_printList();
	return 0;
}

void printListTest(Node* head) {
	Node* current = head;
	while (current != NULL) {
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

void test_addToHead() {
	Node* head = NULL;

	// Test adding to an empty list
	head = addToHead(head, 1);
	assert(head != NULL && head->value == 1);  // Check if the value is correctly added
	printf("addToHead passed\n");

	// Test adding another element to the list
	head = addToHead(head, 2);
	assert(head != NULL && head->value == 2);  // New head should have value 2
	assert(head->next != NULL && head->next->value == 1);  // Check if the next node has value 1
	printf("addToHead passed\n");

	freeList(head);  // Free the memory after the test
}

void test_addToEnd() {
	Node* head = NULL;

	// Test adding to an empty list
	head = addToEnd(head, 1);
	assert(head != NULL && head->value == 1);  // Check if the value is correctly added
	printf("addToEnd (empty list) passed\n");

	// Test adding another element to the end
	head = addToEnd(head, 2);
	assert(head != NULL && head->next != NULL && head->next->value == 2);  // Check if the second node has value 2
	printf("addToEnd passed\n");

	freeList(head);  // Free the memory after the test
}

void test_deleteByValue() {
	Node* head = NULL;
	head = addToEnd(head, 1);
	head = addToEnd(head, 2);
	head = addToEnd(head, 3);

	// Test deleting a node by value
	head = deleteByValue(head, 2);
	assert(head != NULL && head->next != NULL && head->next->value == 3);  // Node with value 2 should be deleted
	printf("deleteByValue passed\n");

	freeList(head);  // Free the memory after the test
}

void test_findByIndex() {
	Node* head = NULL;
	head = addToEnd(head, 1);
	head = addToEnd(head, 2);
	head = addToEnd(head, 3);

	// Test finding a node by index
	int value = findByIndex(head, 1);
	assert(value == 2);  // The second node should have value 2
	printf("findByIndex passed\n");

	freeList(head);  // Free the memory after the test
}

void test_printList() {
	Node* head = NULL;
	head = addToEnd(head, 1);
	head = addToEnd(head, 2);
	head = addToEnd(head, 3);

	// Test printing the list (this is more of a visual test, so it's not assert-based)
	printf("Testing printList:\n");
	printListTest(head);  // It should print: 1 -> 2 -> 3 -> NULL
	freeList(head);  // Free the memory after the test
}
