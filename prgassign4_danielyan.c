/*
Student : Georgiy Danielyan
Professor : George Lazik
Programming Assingment 4 : Virutal Address Mapping
Due : Monday November 30th 2015 @ 11PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*********************
Function Prototypes
*********************/
void displayMenu();
void setParameters();
void mapVirtualAddress();
void printNodes();


/*********************
Variable Declarations
*********************/
char ESC = 27;			//Used for bold printing of messages
int mainMemorySize;	//Size of main memory size
int pageSize;			//Size of page/frame size
int replacementType;	//Type of replacement algorithm
int physicalAddress;	//Physical address
int virtualAddress;	//Virtual address
int pageNumber;		//Page number
int frameNumber;		//Frame number
int numOfNodes;		//The number of nodes


/***************************************
Struct to store Virtual page and Frame
***************************************/
struct node {
	int vPage;
	int pFrame;
} *ptrToNodes = NULL;


/*********************
Main Method
*********************/
int main(){
	int choice;
	do{
		choice = 0;		//reset the choice before getting new input.
		displayMenu();
		scanf("%d", &choice);
		switch(choice){
			case 1:
            setParameters();
				break;
			case 2:
            mapVirtualAddress();
				break;
			case 3: 
            //Free any allocated memory
				free(ptrToNodes);
				exit(0);
				break;
			default:
				printf("Invalid selection\n\n");
				//Clear the input stream in case of extraneous inputs.
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;
		}

	}while(choice != 3);
	return 0;
}


/*********************
Function Declarations
*********************/

/*
@return none
display the menu to the user
*/
void displayMenu(){
	printf("\nGeorgiy Danielyan\n");
	printf("Virtual Address Mapping\n");
	printf("-----------------------\n");
	printf("1) Set Parameters\n");
	printf("2) Map Virtual Address\n");
	printf("3) Quit Program\n");
	printf("4) printtbale\n");
	printf("Enter Selection: ");
}

/*
@return none
get the parameters from the user
*/
void setParameters(){
   printf("Enter main memory size (words): ");
   scanf("%d", &mainMemorySize);
   printf("Enter page size (words/page): ");
   scanf("%d", &pageSize);
   printf("Enter replacement policy (0=LRU, 1=FIFO): ");
   scanf("%d", &replacementType);

   //Allocate space for the nodes/pages
   numOfNodes = (mainMemorySize/pageSize);
   ptrToNodes = (struct node*)malloc(sizeof(struct node)*numOfNodes);

   int i = 0;
   while(i < numOfNodes){
   	ptrToNodes[i].vPage = -1;
   	i++;
   }
}

/*
@return none
display the physical address
*/
void mapVirtualAddress(){

	printf("Enter virtual memory address to access: ");
	scanf("%d", &virtualAddress);

	int virtualPage = virtualAddress/pageSize;
	int wordOffset = virtualAddress%pageSize;

	/*- turn on bold */
   printf("%c[1m",ESC);
	int i = 0;
	while((i < numOfNodes) && (ptrToNodes[i].vPage != -1) && (ptrToNodes[i].vPage != virtualPage)){
		i++;
	}
	//if we get i == numOfNodes then we need to maintain the queue
	if(i == numOfNodes){
		frameNumber = ptrToNodes[0].pFrame;
		int j;
		for(j=0; j < numOfNodes; j++){
			ptrToNodes[j].vPage = ptrToNodes[j+1].vPage;
			ptrToNodes[j].pFrame = ptrToNodes[j+1].pFrame;
		}
		ptrToNodes[numOfNodes-1].vPage = virtualPage;
		ptrToNodes[numOfNodes-1].pFrame = frameNumber;
		printf("\n\n*** Page fault!\n");
	}
	else if(ptrToNodes[i].vPage == -1){
		ptrToNodes[i].vPage = virtualPage;
		ptrToNodes[i].pFrame = i;
		printf("\n\n*** Page fault!\n");
	}
	//If we get here then we need to replace nodes and display the physical address!
	else {
		frameNumber = ptrToNodes[i].pFrame;
		physicalAddress = frameNumber*pageSize+wordOffset;
		if(replacementType == 0){
			int j;
			for(j=0; j < numOfNodes; j++){
				ptrToNodes[j].vPage = ptrToNodes[j+1].vPage;
				ptrToNodes[j].pFrame = ptrToNodes[j+1].pFrame;
			}

			ptrToNodes[numOfNodes-1].vPage = virtualPage;
			ptrToNodes[numOfNodes-1].pFrame = frameNumber;
		}
		printf("\n\n*** Virtual address %d maps to physical address %d\n", virtualAddress, physicalAddress);
	}
	printNodes();
   printf("%c[0m",ESC);

}

/*
Helper method to printing out the nodes with Virtual page and Frame Number
@return none
*/
void printNodes(){
	int j;
	for(j = 0; j < numOfNodes; j++){
		if(ptrToNodes[j].vPage != -1){
   		printf("%c[1m",ESC);
			printf("*** VP: %d -> PF: %d\n", ptrToNodes[j].vPage, ptrToNodes[j].pFrame);
			printf("%c[0m",ESC);
		}
	}
}