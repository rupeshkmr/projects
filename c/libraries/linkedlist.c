#include<stdio.h>
#include<stdlib.h>
//Linked list start
//Data structure to store linked list node
//To find length of list
	// Find index value of Head
struct node{
		int data, index,size;//index to store the current node location in the list O(1) complexity while determining length of the list in stack
		//Index starts from 0
		//size to store length of list
		struct node* next;
		struct node*prev;
};

//Print the list
void printList(struct node* head){
	printf("The list is \n" );

	if(head==NULL || head->index== -1)
		printf("Empty\n");
	else{
	while(head!=NULL){
		if(head->next == NULL)
			printf("|%d|",head->data);
		else
			printf("|%d|->",head->data);
		head = head->next;
	}}
	printf("\n");
}

//Create the head node for linked list
//createHead(value);
struct node* createHead(int value){
		struct node* head;
		head = (struct node*)malloc(sizeof(struct node));
		head->data = value;
		head->prev= NULL;
		head->next = NULL;
		head->index = 0;
		head->size = 0;
		return head;
}
//Create a node
//createNode(value);
struct node* createNode(int value){
		struct node *temp;
		temp = (struct node*)malloc(sizeof(struct node));
		temp->data = value;
		temp->next = NULL;
		temp->prev= NULL;
		temp->index = 0;
		temp->size = 0;
		return temp;
}
//Delete a node
//deleteNode(head,index) index specifies which node to delete

struct node* deleteNode(struct node* head,int index){
		if(head == NULL)
			{printf("Error: Cannot delete\nError: Null input\n" );
			 return NULL;
		}

		struct node* temp = head;
		struct node* temp1,*temp2;
		temp1 = temp;
		while(temp->index != index){
			temp1 = temp;
			temp = temp->next;
		if(temp == NULL){
			printf("Error: Element not found in the list!! Please backoff\n" );
			return NULL;
			}
		}//if only head is in the list
		if(temp == temp1){
			head = temp->next;
			free(temp1);
			// free(temp);		what's the problem here
			return head;
		}
		temp2 = temp->next;
		while(temp2 != NULL){ //&& temp2->next != NULL){
			temp2->index -= 1;
			temp2 = temp2->next;
			}
		temp1->next = temp->next;
		// prevnode = temp->next;
		//prevnode->prev= temp->prev;
		// free(temp2);
		// free(temp1);
		// free(temp);

		return head;





}

//Linked list end




//safety check whether the dequed or popped list is not full yet
//if not full and deletion makes it empty create an empty node as head and return
// struct node* safetyCheck(struct node *head){
// 	if(head->next == NULL){
//
//
// 	}
// 	else
// 	return head;
// }


//end
//StacK
//Create Stack
//Arguments: length,
struct node* initStack(int value,int length){
	if(length<=0){
		printf("Error: null size\n");
		return NULL;}
	struct node* tos;//to store top of stack
	tos = createHead(1);
	tos->index = -1;
	tos->size = length;
	struct node* first;
	first = createNode(value);
	first->size = tos->size;
	first->index= tos->index+1;
	tos->next = first;
	first->prev = tos;
	return first;
}

//Push
//Arguments: value,top of stack
struct node* push(int value,struct node* top){

	//if stack is empty
	if(top->index== -1)
		{
			struct node* first;
			first = createNode(value);
			first->prev = top;
			top->next = first;
			first->index = 0;
			first->size = top->size;
			return first;

		}//if stack is full
	else if(top->index + 1 == top->size)
{		printf("Error: Cannot push\nError: Stack overflow\n");
		return top;
}
	else{	printf("Push Request\n");
		printf("Value = %d top of stack = %d index = %d\n",value,top->data,top->index);
		struct node* temp = createNode(value);
		temp->next = top;
		temp->index = top->index+1;
		temp->size = top->size;
		printf("Push successful\n");
		return temp;
		}
}
//Pop
//Arguments: top of stack
struct node* pop(struct node* top){

	if(top->index == -1)
		{
		printf("Error: Cannot pop\nError: Stack underflow\n");
		return top;
		}
	else{
		printf("The popped value is %d\n",top->data);
		struct node* head;
		head = top->prev;
		struct node* temp = deleteNode(top,top->index);
		if(temp==NULL){
			return head;
		}
		return temp;
		}
}
//Stack finished

//Queue
//Initialize queue
struct node* initQ(int value,int length){
	return initStack(value,length);
	}

//[T| | | | | H]
//[n ,.....1, 0] n = index of current node
//Enqueue
//Arguments: value, tail node
struct node* enqueue(int value,struct node* tail){

	printf("Enqueue Request\n");
	if(tail->index== -1)
		{
			struct node* first;
			first = tail->next;
			if(first->index == tail->size)
			{	printf("Error: Cannot Enqueue\nError: Queue FUll\n");
				return tail;}
			else
			{	first->data = value;

				return first;
				}
		}
	else	if(tail->index +1 == tail->size){
		printf("Error: Cannot Enqueue\nError: Queue FUll\n");
		return tail;
	}
	else{
	printf("Value = %d Tail = %d index = %d\n",value,tail->data,tail->index);

	struct node* temp;
	temp = createNode(value);
	temp->next = tail;
	temp->index = tail->index+1;
	temp->size = tail->size;
	printf("enqueue successful\n");
	return temp;}
}
//Dequeue operation
struct node* dequeue(struct node* tail){


	struct node* temp;
	struct node* prevnode;
	temp = tail;
	prevnode = tail;

	if(temp->index ==-1)
		{printf("Error: Queue Empty\n");
		 return temp;
			}

	while( temp->next != NULL){
		prevnode = temp;
		temp = temp->next;
	}
	prevnode->prev = temp->prev;
	printf("The dequeued value is %d\n",temp->data);
	struct node* base,*first;
	if(tail->prev!=NULL){
		base = tail->prev;
		first = createNode(0);
		first->prev= base;
		first->size = base->size;
		first->index = tail->index+1;
		tail = deleteNode(tail,temp->index);
		return first;
	}
	else
	{ tail = deleteNode(tail,temp->index);

		return tail;
}
}

int main(){
	struct node* stack = initStack(5,6);
	printf("The value of TOS is %d and Length of the stack is %d, Position of TOS is %d\n",stack->data,stack->size,stack->index);
	for(int i=0;i<6;i++){
		stack = push(i,stack);
		}
		printList(stack);
	for(int i=0;i<7;i++){
		stack = pop(stack);
		printList(stack);
		}

		stack = push(6,stack);

		stack = push(7,stack);
		printList(stack);
	printf("Calling Queue operations\n");
	struct node* queue = initQ(5,6);
	for(int i=0;i<6;i++){
		queue = enqueue(i,queue);
		printList(queue);
		}
	printList(queue);
	for(int i=0;i<7;i++){
		queue = dequeue(queue);
				printList(queue);

		}

		printf("Finish---------------------------------\n" );
		struct node* queue1 = initQ(5,6);
				queue1 = dequeue(queue1);
		for(int i=0;i<6;i++)
		{
			queue1 = enqueue(5,queue1);
			printList(queue1);
			queue1 = dequeue(queue1);
			printf("Iterarion: %d\n",i+2 );
		}
		printList(queue1);


	return 0;
}
