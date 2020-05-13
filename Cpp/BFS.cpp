#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

void enqueue(int x)
{

	struct Node* t = (struct Node*)malloc(sizeof(struct Node));

	if(t==NULL)
		printf("memory problem");
	else
	{
		t->data = x;
		t->next = NULL;
		if(front == NULL) //empty
		{
			front = rear = t;
		}
		else
		{
			rear->next = t;
			rear = t;
		}
	}
}

int dequeue()
{
	int x;
	struct Node* t;

	if(front == NULL)
	{
		printf("queue is empty");
		return -1;
	}
	else
	{
		t = front;
		x = t->data;
		front = front->next;
		free(t);
	}

	return x;

}

int isEmpty()
{
	return front == NULL;
}


void BFS(int G[][7], int start, int n)
{
	int i = start;
	int visited[n] = {0};
	printf("%d ",i);
	enqueue(i);
	visited[i] = 1;

	while(!isEmpty())
	{
	
		i = dequeue();

		for(int j = 0; j<n; j++)
		{
			if(G[i][j] == 1 && visited[j] == 0)
			{
				printf("%d ",j);
				enqueue(j);
				visited[j] = 1;
			}
		}
	}

}



int main()
{
	int G[7][7] = {
			{0,1,1,1,0,0,0},
			{1,0,0,1,0,0,0},
			{1,0,0,1,1,0,0},
			{1,1,1,0,1,0,0},
			{0,0,1,1,0,1,1},
			{0,0,0,0,1,0,0},
			{0,0,0,0,1,0,0}
		      };

	BFS(G,3,7);

	return 0;
}
