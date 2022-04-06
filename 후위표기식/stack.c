#include "stack.h"

struct node {
	Item data;
	Node next;
};

struct stack {
	Node top;
};

Node Create_node()
{
	Node new_node = (Node)malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in Create_node : node could not be created.");
	new_node->data = NULL;
	new_node->next = NULL;

	return new_node;
}

Stack Create_stacK()
{
	Stack new_stack = (Stack)malloc(sizeof(struct stack));
	if (new_stack == NULL)
		terminate("Error in create_stack : stack oould not be created.");
	new_stack->top = NULL;

	return new_stack;
}

bool Is_empty(Stack stack)
{
	return stack->top == NULL;
}

void Push(Stack stack, Item data)
{
	Node new_node = Create_node();
	new_node->data = data;

	if (Is_empty(stack))
		stack->top = new_node;

	else {
		new_node->next = stack->top;
		stack->top = new_node;
	}
}

Item Peek(Stack stack)
{
	if (Is_empty(stack))
		terminate("Error in Peek : Stack is empty.");
	return stack->top->data;
}

Item Pop(Stack stack)
{
	if (Is_empty(stack))
		terminate("Error in Pop : Stack is empty.");
	Node old_node = stack->top;
	int old_data = old_node->data;

	stack->top = old_node->next;

	Remove_node(old_node);
	if (Is_empty(stack))
		Remove_stack(stack);

	return old_data;
}

void Remove_node(Node old_node)
{
	free(old_node);
	old_node->data = NULL;
	old_node->next = NULL;
}

void Remove_stack(Stack stack)
{
	free(stack);
	stack->top = NULL;
}

void Print_stack(Stack stack)
{
	if (Is_empty(stack))
		printf("stack is empty.\n");
	else {
		Node node = stack->top;

		printf("Stack : ");
		while (node != NULL) {
			printf("%d", node->data);
			node = node->next;

			if (node == NULL)
				printf("\n\n");
			else
				printf(" --> ");
		}
	}
}

void terminate(char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}