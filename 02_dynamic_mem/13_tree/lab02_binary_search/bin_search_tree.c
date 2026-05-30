/**
 * File:        bin_search_tree.c
 * Author:      Frank Christopher Kirch
 * Created:     29.04.2024
 * Last edit:   30.05.2026
 *
 * Description: Code to demonstrate creation and traversal of binary
 *              search trees. Provided code works with integers read from a file.
 * 
 * Usage:       ./program_name name_of_input_file
 */
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <time.h>


#define MAX_NAME 64
#define FULL_NAME_MAX 129
#define NAME_UNIQUE -1

typedef struct node
{
    char fullname[FULL_NAME_MAX];
    struct node *pLeft;
    struct node *pRight;
    
    int id;
	int count;
} tree;

FILE *fOutStream;

void ReadData(tree **data, char *file);

void InsertToTree(tree **t, char fullName[FULL_NAME_MAX]);

struct node * CreateNode(char fullName[FULL_NAME_MAX]);
void SafeFree(void **p);
unsigned GetSequence(void);
void DebugString(char str[]);

char *AllocateStr(char str[FULL_NAME_MAX]);

void PrintTree(tree *t);
void WriteTree(tree *t);

void FreeBinaryNode(tree *t);

int main(int argc, char *argv[])
{
    tree *data = NULL;

    /* Makes sure that the input file name was passed to the program */        
    if (argc != 2)
    {
        printf("No input file provided!\n");
        exit(EXIT_FAILURE);
    }    


    
	clock_t start, end, startAll, endAll;
    start = clock();
    startAll = clock();
   
    ReadData(&data, argv[1]);
        
    end = clock();
    double timeRead = (double)(end - start) / CLOCKS_PER_SEC;
    
    
	start = clock();
    PrintTree(data);
    
	end = clock();
    double timePrint = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n");
    
	char *filename = "output.txt";
	fOutStream = fopen(filename, "w");
		
    WriteTree(data);
    /** Closing file-stream **/
	fclose(fOutStream);
    
    start = clock();
    
    FreeBinaryNode(data);
    
    end = clock();
    double timeFree = (double)(end - start) / CLOCKS_PER_SEC;

	endAll = clock();
	double timeAll = (double)(endAll - startAll) / CLOCKS_PER_SEC;
	
	

    putchar('\n');
    printf("Time it took to read file: %.6lf seconds.\n", timeRead);
    printf("Time it took to print all lines: %.6lf seconds.\n", timePrint);
	printf("Time it took to free structure: %.6lf seconds.\n", timeFree);
	printf("Time it took to for entire program: %.6lf seconds.\n", timeAll);
	putchar('\n');
    
    return EXIT_SUCCESS;
}

/**
 * Description:    Reads the data from the file provided and stores everything
 *                 in a binary search tree. 
 *
 * Parameters:     data - duoble pointer to a tree (node).
 *                 file - string with the name (path) of the file to read from
 *
 * Return:         void
 */
void ReadData(tree **data, char *file)
{

    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        perror("Opening of input file failed");
        exit(EXIT_FAILURE);
    }
    
	char fullName[FULL_NAME_MAX];

	char fName[MAX_NAME];
	char lName[MAX_NAME];
	
	 /** Skipping these strings when reading. **/

	while (fscanf(fp, "%*s %s %s %*s", fName, lName) == 2)
    {
        snprintf(fullName, FULL_NAME_MAX, "%s %s", fName, lName);
        

		InsertToTree(data, fullName);
    }
    
    fclose(fp);
}


/**
 * Description:    Inserts a new node into a binary search tree. It traverses
 *                 the tree until it finds a correct (and unused) leaf and
 *                 creates and assigns a node into that place.
 *
 * Parameters:     t - duoble pointer to a tree (node).
 *                 value - value to be stored into the tree.
 *
 * Return:       file:///home/frkirc/Downloads/random_people_city_data.txt  void
 */
void InsertToTree(tree **t, char fullName[FULL_NAME_MAX])
{
    tree *currentNode = *t;

    if (currentNode == NULL)
    {
        /* If the current node (child) is NULL, creates a node */
        *t = CreateNode(fullName);
    }
    else
    {
        int strcmpVal = strcmp(fullName, currentNode->fullname);
        
        /* Otherwise continues to traverse the tree */
        if (strcmpVal < 0)
        {
            /* The value to be inserted has a lower value than current node */
            InsertToTree(&(currentNode->pLeft), fullName);
        }
        else if (strcmpVal > 0)
        {
            /* The value to be inserted has a higher value than current node */
            InsertToTree(&(currentNode->pRight), fullName);
        }   
        else if (strcmpVal == 0) /** Problem here!!! every iteration goes to count++**/
        {
			currentNode->count++;
		} 
    }
}

/**
 * Description:    Creates a new tree node and assigns the passed value to it.
 *                 Also initializes the child nodes to NULL.
 *
 * Parameters:     fullName - string for the node being created.
 *
 * Return:         pointer to the newly created node.
 *                 NULL pointer if memory allocation failed.
 */
struct node * CreateNode(char fullName[FULL_NAME_MAX])
{
	#ifdef DEBUG /** **/
	printf("name is '%s'. Pointer: %p.\n", fullName, fullName); /** ASK **/
	#endif
    
    /** Küsi mälu node'i loomiseks. Välju funktsioonist, kui mälu ei jätkunud. **/
    struct node *pNewNode = malloc(sizeof(struct node));
    if (pNewNode == NULL)
    {
        return NULL;
	}
	#ifdef DEBUG
	printf("strlen(%s)=%ld\n", fullName, strFILE *fOutStream;len(fullName));
	#endif
	
	strcpy(pNewNode->fullname, fullName);
	//~ pNewNode->fullname = fullName;
    
	/**  Määra ära ID väärtus (järjestikuline suurenev täisarv, 
	* 	kasuta  static  märksõna)**/
	pNewNode->id = (int) GetSequence();
    
    /** Lisa loenduri algväärtustamine **/
    pNewNode->count = 1; 
    
    /* Initialize the child nodes as not existing */
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    
    /* Returns the pointer to the newly created node */
    return pNewNode;
}

/** Description:	Create a generator for ID.
 *  				Sequence will increment on each call
 *  				
 * 					'static' deklaratsiooniga muutujad
 * 					jäävad mällu alles pärast funktsiooni lõppu
 * 					(global/static mäluala)
 * 
 * 					Algväärtustamine toimub vaid ühekordselt
 * 					Järgneval funktsiooni kutsel varasem väärtus säilib.
 * 
 * **/
unsigned GetSequence(void)
{
	/** Initialization **/
	static unsigned value = 0;
	/** Returns current value **/
	/** Incremented for next call**/
	return value++;
}


/**
 * Description:    Prints out the binary tree, uses a depth-first approach NLR
 *                 (root - left - right) for traversal.
 *
 * Parameters:     t - pointer to a node in the binary tree.
 *
 * Return:         void
 */
void PrintTree(tree *t)
{
    /* only print the node and traverse if the node exists */
    if (t != NULL)
    {
         /* Traversal to the left child node */        
        PrintTree(t->pLeft);
        
		/* Prints the current tree node value */
		printf("(ID: %d) ", t->id);
		printf("Name: %s ", t->fullname);
		printf("count: %d", t->count);
		putchar('\n');
		
		
        /* Traversal to the right child node */        
        PrintTree(t->pRight);
    }
}

void WriteTree(tree *t)
{
    if (t != NULL)
    {
		 /* Traversal to the left child node */        
        WriteTree(t->pLeft);
        
        /** ---------------------------------------------**/
		/* Prints the current tree node value */
		fprintf(fOutStream, "(ID: %d) ", t->id);
		fprintf(fOutStream, "Name: %s ", t->fullname);
		fprintf(fOutStream, "count: %d\n", t->count);
		/** ---------------------------------------------**/

        /* Traversal to the right child node */        
        WriteTree(t->pRight);
	}
}

/**
 * Function to check if allocated memory can be free without memory leaks.
 **/
void SafeFree(void **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}

/**
 * 
 **/
void FreeBinaryNode(tree *t)
{
	/* only print the node and traverse if the node exists */
    if (t != NULL)
    {
		/* Traversal to the left child node */        
		//~ FreeBinaryNode((void **)&(t->pLeft->fullname));
		FreeBinaryNode(t->pLeft);
        
        /* Traversal to the right child node */        
		//~ FreeBinaryNode((void **)&(t->pRight->fullname));
		FreeBinaryNode(t->pRight);
		
		/* Free()s the current node's field "fullName" */
		//~ SafeFree((void **)&(t->fullname));
		
		/* Free()s the current node itself*/
		SafeFree((void **)&t);   
    }
}


/**
 * Description:    Checks if the passed name is already a part of the array
 *
 * Parameters:     db - pointer to the data array
 *                 n - number of members in the data array (at the moment)
 *                 name - string that will be checked if already in the array
 *
 * Return:         integer. Index of the name if it is found in the array.
 *                 NAME_NOT_UNIQUE is returned if it is not found.
 */
int CheckNameUnique(tree *db, int n, char *name)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!strcmp(name, db[i].fullname))
        {
            /* The name was found, thus it's not unique. Returning the indx.*/
            return i;
        }
    }
    
    /* The name was not found in the struct array */
    return NAME_UNIQUE;
}


/**
 * Allocate a string, mostly for demonstrative purposes and compatibility
 */
char *AllocateString(size_t n)
{
    char *pString = (char *)calloc(n, sizeof(char));
    
    if (pString == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    return pString;
} // end of function

char *AllocateStr(char str[FULL_NAME_MAX])
{
	/**------------------------------------------------------------ **/
    /**  Küsi mälu node'i välja "fullName" jaoks ja kopeeri nime väärtus struktuuri **/
	//~ pNewNode->name = (char *)calloc(strlen(fullName) + 1, sizeof(char));
	char *pStr = (char *)calloc(strlen(str) + 1, sizeof(char));
	if (pStr == NULL)
	{
		 /** Tagasta mälu, mis anti node'ile, kui stringile mälu ei jagunud **/
		printf("Not enough memory for string '%s'.\n", str);
		//~ SafeFree((void **)&pNewNode);
		return NULL;
	}
    strcpy(pStr, str); /** Kopeeri nime väärtus väljale. **/
    return pStr;
    /** Ülalolev blokk [...] simuleerib strdup(). 
     * Kopeeri siinset tervikuna**/
     /**------------------------------------------------------------ **/
}

/**
 * Print debug information of string. Each char, it's index and ASCII.
 **/
void DebugString(char str[])
{
    int i = 0;
    printf("String is: '%s'\n", str);
    while (str[i] != '\0')
    {
        printf("str[%d] = %3hhu %c\n", i, str[i], str[i]);
        i++;
    }
    printf("\n");
}
