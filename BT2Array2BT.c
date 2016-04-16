#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 1024
#define max(i,j) ((i > j)? i : j  )

typedef struct node {
    void *value;
    struct node *left;
    struct node *right;   
}BTNode;

BTNode *root, *n[6], *root2, *n2[6];

/*
* We can store the void * objects in an array, eg It can be stored as obj[] & can pass it. If the objects are of different 
* type we can either maintain  structures at both ends or need to write code accordingly where we can fetch the objects and
* store in array before sending across. Below code is simplified to focus mainly on how to convert Tree to Array and back to Tree
*/
long obj[6] = {30,20,40,10,5,50};
BTNode *Tarray[MAX_SIZE+1], *temp;

// Get the Height of the tree using recursive function call
int getHeight(BTNode *rootTemp) {
    return ( (rootTemp==NULL) ? 0 :  1+ max(getHeight(rootTemp->left),getHeight(rootTemp->right)));
}

// Created BT for the testing purpose
void createBT(int numberOfNode) {
	int i = 0;
	for(i=0; i<numberOfNode;i++) {
		n[i] = (struct node *)malloc(sizeof(struct node));
		n[i]->value = (void *)obj[i];		
	}
	// below is the assignment creates given tree in question
		root = n[0];
		root->left = n[1];
		n[1]->left = NULL;
		n[1]->right = n[3];
		n[3]->left = n[4];
		n[3]->right = NULL;
		n[4]->right = NULL;
		n[4]->left = NULL;
		root->right = n[2];
		n[2]->left = NULL;
		n[2]->right = n[5];
		n[4]->right = NULL;
		n[4]->left = NULL;
}

// Inorder display of the tree
void inorder(struct node *root1) {
	if(root1->left)
		inorder(root1->left);
	else
		printf("NULL--");
	if(root1)
		printf("[%ld]--",(long)root1->value);
	if(root1->right)
		inorder(root1->right);
	else
		printf("NULL--");
}


/*
BT : arr[]
parent : i
left child arr[2i]
right child arr[2i+1]

height = n
number of nodes = ((2^n)-1)

                    30
                    |
               |             |
              20             40
          |       |        |    |
         NULL    10       NULL  50
               |    |
               5   NULL
             
i=1;
Tarray:  - 30 20 40 NULL 10 NULL 50 NULL 5 ...
       i 0  1  2  3  4    5   6   7  8   9 ...        
           30: return--> 
           				1+ max(3), 2)
*/


/*
Function to convert the BT to the array 
BT with root :=> Tarray
*/
void BTtoArray (BTNode *rootTemp) {

    if(rootTemp == NULL)
        return;

    int i, j=1;
    int totalNodes = pow(2,getHeight(root))-1;
	for(i=0; i<=totalNodes;i++) {
		Tarray[i] = (struct node *)malloc(sizeof(struct node));
		Tarray[i] = NULL;
	}
    i=2;
   	Tarray[1] = rootTemp;
    temp = Tarray[1];
    while(j <= totalNodes)
    {
        if(temp != NULL && temp->left!=NULL )
            Tarray[i++] = temp->left;
        else
        	i++;			// maintains order, if we want only NOT-NULL continuousel, dont do i++
        if(temp != NULL && temp->right!=NULL)
            Tarray[i++] = temp->right;
        else
        	i++;			// maintains order, if we want only NOT-NULL continuousel, dont do i++
        j++;
        temp = Tarray[j];
    }
}

/*
Function to convert the array back to BT
Tarray:=> BT with root2
*/
void ArrayToBT(int numberOfNode) {
	int i=0, j;
    int totalNodes = pow(2,getHeight(root))-1;
    if(totalNodes == 0)
    	return;

	for(i=0; i<numberOfNode;i++) {
		n2[i] = (struct node *)malloc(sizeof(struct node));
		n2[i]->right = NULL;
		n2[i]->left = NULL;
	}

/*
if Parent is at index : i of Tarrat
==> Left child index  : 2*1,
==> right child index : 2*1 +1
*/
 	n2[0] = Tarray[1];
	for(j=2; j<=totalNodes/2; j++) {
		if(Tarray[j]!=NULL && Tarray[j*2] !=NULL)
		{
	    	n2[j]->left = Tarray[i*2];
	    }
		if(Tarray[j]!=NULL && Tarray[j*2+1] !=NULL)
		{
	    	n2[j]->right = Tarray[i*2];
	    }
	}
	root2 = n2[0];
}


void DisplayArray()
{
	int i=0;
    int totalNodes = pow(2,getHeight(root))-1;
	printf("BT converted to array: \n----------------------\n");
	for(i=1; i<=totalNodes;i++) {
		if(Tarray[i] != NULL)
			printf("[%ld], ",  (long)Tarray[i]->value );
		else
			printf("[NULL], ");
	}
	printf("\n");	

}

int main() {

	int numberOfNode = 6, i=0;

	createBT(numberOfNode);
	printf("\nAT SOURCE\n----------------------\nInorder traversal of BT with root: [%ld]\n",(long)root->value);
	inorder(root);
	printf("\n\n");

	BTtoArray(root);

	DisplayArray();

	ArrayToBT(numberOfNode);
	printf("\nAT DESTINATION\n----------------------\nInorder traversal of BT with root: [%ld]\n",(long)root2->value);
	inorder(root2);
	printf("\n\n");	

	return 0;
}
