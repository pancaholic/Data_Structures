#include<stdio.h>
#include<stdlib.h>

// PUTRA PANCA PRASETYA
// 2502006726

struct tnode
{
	int x;
	tnode *next;
	tnode *prev;//4
} *head, *tail, *curr;

void push_front(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		node->next = NULL;
		node->prev = NULL;//3
	}
	else
	{
		node->next = head;
		head->prev = node;//1
		head = node;
		head->prev = NULL; //2
	}
}

void push_back(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
		tail->prev = NULL;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		tail->next = NULL;
	}
}

void push_mid(int value, int searchKey)
{
	//create node
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	//checking first node
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
		node->next = node->prev = NULL;
	}
	else
	{
		struct tnode *curr = head;
		while (curr != NULL) {
			if (curr->x == searchKey) {
				node->next = curr->next;
				node->prev = curr;

				if (curr->next != NULL) {
					curr->next->prev = node;
				} else {
					push_back(value);
				}
				curr->next = node;
				return;
			}
			curr = curr->next;
		}
		printf("Data %d is not found\n",searchKey);
		
	}
}

void printList()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		return;
	}
	
	//struct tnode *curr = head;
	curr=head;
	while(curr!=NULL)
	{
		printf("%d ",curr->x);
		curr = curr->next;
	}
}

void del_back()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		return;
	}
	else
	{

			struct tnode *del = tail;
			tail = tail->prev;
			if(tail) {
				tail->next = NULL;
			} else {
				free(head);
				head = tail = NULL;
			}
			free(del);
		}
	
}

void del_front()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		return;
	}
	else
	{
		struct tnode *del = head;
		head = head->next;
		if(head) {
			head->prev = NULL;
		} else {
			// free(head);
			head = tail = NULL;
		}
		free(del);
	}
}

void del_mid(int searchKey)
{
	
	if(head==NULL)
	{
		printf("There is no data \n");
		return;
	} else {
		struct tnode *curr = head;
		while (curr != NULL) {
			if (curr->x == searchKey) {
				struct tnode *del = curr;
				// Cek Kalau Di tengah

				if (curr->next != NULL) {
					// Ubah prev node sehabis curr menjadi previous curr
					curr->next->prev = curr->prev;
				} else {
					del_back();
				}

				if (curr->prev != NULL) {
					// Ubah node next sebelum curr menjadi next curr
					curr->prev->next = curr->next;
				} else {
					del_front();
				}
				free(del);
				return;
			}
			curr = curr->next;
		}
		printf("Data %d is not found\n",searchKey);
	}
}

int main()
{
	printf("Linked List\n");
	
	push_front(76); // 76
	push_front(90); // 90 76
	push_front(45); // 45 90 76
	push_mid(80, 90); // 45 90 80 76
	push_mid(78, 76); // 45 90 80 76 78
	del_back(); // 45 90 80 76
	del_front(); // 90 80 76
	del_mid(80); // 90 76
	
	printList();getchar();
	
	return 0;
}
