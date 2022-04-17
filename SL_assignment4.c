#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
    int value;
    bool mark;                          //for marking the nodes 
    int ref_cnt;                       //for reference count method
    struct node *Adjacent_1;
    struct node *Adjacent_2;
    struct node *Adjacent_3;
                                       //Maximum three links are shown in the diagram ( for 1)
    
}Node;

 Node *ptr_arr[8];

void display_node_func(int i)
{
	printf("value=%d\t reference_count=%d freed_size=%d\n",ptr_arr[i]->value,ptr_arr[i]->ref_cnt,sizeof(Node));
}                                                           //function to display reference count and freed size of node after garbage collection

void set_edge(int one,int dest1,int dest2,int dest3)            //modifying the list as per the scheme
{
	if(dest1!=-1)                                             //-1 node not connected                             
	{
		ptr_arr[one]->Adjacent_1=ptr_arr[dest1];
		ptr_arr[dest1]->ref_cnt+=1;
	}
	if(dest2!=-1)
	{
		ptr_arr[one]->Adjacent_2=ptr_arr[dest2];
		ptr_arr[dest2]->ref_cnt+=1;
	}
	if(dest3!=-1)
	{
		ptr_arr[one]->Adjacent_3=ptr_arr[dest3];
		ptr_arr[dest3]->ref_cnt+=1;
	}
	
}

void display_allnodes_func(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:ref_cnt=%d\n",root->value,root->ref_cnt);
	}
	if(root==NULL)
	{
		return;
	}
	display_allnodes_func(root->Adjacent_1);
	display_allnodes_func(root->Adjacent_2);
	display_allnodes_func(root->Adjacent_3);
}

void Adjacency_Lst()                                                //prints all adjacent next nodes
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(ptr_arr[i]!=NULL)
		{
			printf("Value=%d: ",ptr_arr[i]->value);
			if(ptr_arr[i]->Adjacent_1!=NULL)
			{
				printf("%d ->",ptr_arr[i]->Adjacent_1->value);
			}
			if(ptr_arr[i]->Adjacent_2!=NULL)
			{
				printf("%d ->",ptr_arr[i]->Adjacent_2->value);
			}
			if(ptr_arr[i]->Adjacent_3!=NULL)
			{
				printf("%d ->",ptr_arr[i]->Adjacent_3->value);
			}
			printf("NULL\n");
		}
	}
}

int RootIsPresent(Node* root1,Node* temp)       //if root is present we return true
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->value==temp->value)
	{
		return 1;
	}
	
	if(RootIsPresent(root1->Adjacent_1,temp))
	{
		return 1;
	}
	
	if(RootIsPresent(root1->Adjacent_2,temp))
	{
		return 1;
	}
	if(RootIsPresent(root1->Adjacent_3,temp))
	{
		return 1;
	}
 return 0;
}


void Adjacent_Mtx()
{
	int adm[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)		          //initialising all indices values to 0
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(ptr_arr[j]!=NULL&&ptr_arr[i]!=NULL)
		{
			
			if(ptr_arr[i]->Adjacent_1!=NULL)
			{
				if(ptr_arr[i]->Adjacent_1->value==ptr_arr[j]->value&&i!=j)          //if connected ( if ith index node is connected with jth index node)
				{
					adm[i][j]=1;
				}
			}
			if(ptr_arr[i]->Adjacent_2!=NULL)
			{
				if(ptr_arr[i]->Adjacent_2->value==ptr_arr[j]->value&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(ptr_arr[i]->Adjacent_3!=NULL)
			{
				if(ptr_arr[i]->Adjacent_3->value==ptr_arr[j]->value&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);		          //printing the adjacency matrix
		}
		printf("\n");
	}
}


void Mark_Method(Node* root)                       //marks all nodes which are accesible from the root
{
	
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	Mark_Method(root->Adjacent_1);
	Mark_Method(root->Adjacent_2);
	Mark_Method(root->Adjacent_3);
}

void Sweep_Method()                           //changes the false node to NULL
{
	int i;
	for(i=0;i<8;i++)
	{
		if(ptr_arr[i]->mark==false)
		{
			if(ptr_arr[i]->Adjacent_1!=NULL)
			{
				ptr_arr[i]->Adjacent_1->ref_cnt-=1;
			}
			if(ptr_arr[i]->Adjacent_2!=NULL)
			{
				ptr_arr[i]->Adjacent_2->ref_cnt-=1;
			}
			if(ptr_arr[i]->Adjacent_3!=NULL)
			{
				ptr_arr[i]->Adjacent_3->ref_cnt-=1;
			}
			printf("Garbage:");
			display_node_func(i);
			free(ptr_arr[i]);
			ptr_arr[i]=NULL;
		}
	}
}

int main()
{
	
	//Node valueber  		   	   0,1,2,3,4,5,6,7	
	//value		
	int val[]={1,2,3,5,7,8,9,10};
	
	
	int i;
	
	for( i=0;i<8;i++)
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->value=val[i];
		newNode->Adjacent_1=NULL;
		newNode->Adjacent_2=NULL;
		newNode->Adjacent_3=NULL;
		newNode->ref_cnt=0;
		newNode->mark=false;		
		ptr_arr[i]=newNode;
	}
	
	Node*root1=ptr_arr[3];     // connected to root
	ptr_arr[3]->ref_cnt+=1;       // increased ref count by one
	Node*root2=ptr_arr[0];
	ptr_arr[0]->ref_cnt+=1;
	
	set_edge(0,1,6,7);       // accessing array by index
	set_edge(2,5,7,-1);
	set_edge(3,0,-1,-1);
	set_edge(4,0,5,-1);
	set_edge(5,6,-1,-1);

	
	printf("\nAll nodes through Root-1:\n");
	display_allnodes_func(root1);
	
		
	printf("\nAll nodes through Root-2:\n");
	display_allnodes_func(root2);
	
	printf("\n\nAdjacency list :\n");        //Displaying Adjacency list of the nodes with corresponding value or vertex
	Adjacency_Lst();
	
	printf("\n\nAdjacency matrix:\n");   //Displaying Adjacency Matrix of the nodes rather than root 1 and root 2
	Adjacent_Mtx();
	

	
	printf("\nCalling the mark and sweep garbage collector\n");
	//MarkTheNodes(root1,0,1);
	Mark_Method(root1);
	Sweep_Method();


	
	printf("\n\nAdjacency list after removal of garbage:\n");
	Adjacency_Lst();
	
	printf("\n\nAdjacency matrix after removal of garbage:\n");
	Adjacent_Mtx();
	
}
