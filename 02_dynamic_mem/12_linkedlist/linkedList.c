/**
 * File:        linkedList.c
 * Author:      Frank Christopher Kirch
 * Created:     12.04.2024
 * Modified:    30.05.2026
 *
 * Description: Header for the linked list lab task
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedList.h"

int main(void)
{
    list *pHead = NULL;
    int menuOption;
    
    char name[MAX_STR] = {0};
    char name2[MAX_STR] = {0};
    
    while (1)
    {
        menuOption = GetInput();
        switch (menuOption)
        {
            case 0:
                /** case 0 - destroy the list and exits the program **/
                
                Unload(pHead);
                puts("Exiting program...");
                exit(EXIT_SUCCESS);
                break;
            case 1:
                /** case 1 - print the entire list **/ 
                
                PrintList(pHead);
                break;
            case 2:
                /** case 2 - Ask user for the name; use CreateNode() to allocate
                 *          the node. Use InsertNode() to add it.**/
                 
				struct node *a = CreateNode(AskName(name, MAX_STR));
				InsertNode(&pHead, a);
                break;
            case 3:
                /** case 3 - Allows the user to enter a node ID. 
                   Finds a node by the id value using FindNodeById().
                   Returned pointer is passed to PrintNode() to display it **/
				if(pHead != NULL) {
					PrintNode(FindNodeByID(pHead, AskId()));
				} else {
					printf("-- Please Insert a Node beforehand, you cannot retrieve any nodes from a empty Linked List. --");
				}
                break;
            case 4:
                /** case 4 - Allows the user to enter a node name. 
                   Finds a node by the id value using FindNodeByName().
                   Returned pointer is passed to PrintNode() to display it **/
			   if(pHead != NULL) { 
                   PrintNode(FindNodeByName(pHead, AskName(name, MAX_STR)));
				} else {
					printf("-- Please Insert a Node beforehand, you cannot retrieve any nodes from a empty Linked List. --");
				}
                break;
            case 5:
                /** case 5 - Allows the user to enter a node ID.
                   Find and removes the node by that ID (if it exists). **/
				if(pHead != NULL) { 
					/** Node ID validation and linkedList operations**/
					RemoveNodeByID(&pHead, AskId());
				} else {
					printf(" -- Please Insert a Node beforehand, you cannot retrieve any nodes from a empty Linked List. -- ");
				}
				break;
            case 6:
                /** case 6 - Allows the user to enter a node name.
                   Find and removes the node by that name (if it exists). **/
				if(pHead != NULL) {
					RemoveNodeByName(&pHead, AskName(name2, MAX_STR));
				} else {
					printf(" -- Please Insert a Node beforehand, you cannot rremove any nodes from a empty Linked List. -- ");
				}
                break;
            default:
                puts("You should not be here!");
                break;
        }
    }
    return EXIT_SUCCESS;
}
/**
void isListEmpty(list *pHead){
	return pHead == NULL;
}
**/

int GetInput(void)
{
    int input;
    puts("");
    while (1)
    {
        puts("Make your selection. Press the corresponding number and the enter key");
        puts("1 - Print list");
        puts("2 - Insert a node");
        puts("3 - Find a node by ID");
        puts("4 - Find a node by name");
        puts("5 - Erase a node by ID");
        puts("6 - Erase a node by name");
        puts("0 - Exit");
        printf("> ");
        scanf("%d", &input);
        puts("");
        if (input <= 6 && input >= 0)
            return input;
        fprintf(stderr, "Input out of bounds!\n");
    }
}




void PrintList(list *pHead)
{
    list *pTemp;
    
    if (pHead) // shortened version of : 'if (pHead != NULL)'
        for (pTemp = pHead; pTemp; pTemp = pTemp->pNext) //  (pTemp != NULL)' <== pTemp'
            PrintNode(pTemp);
    else
        fprintf(stderr, "-- Linked list is empty. Nothing to print. --");
}

/** 
 * Seda funktsiooni kasutame ühe elemendi väljastamiseks. 
 * Kasuta seda kõikjal kus sul on vaja elemendi sisu väljastada – nt ka otsingufunktsioonides. 
 * Eraldi väljastusfunktsiooni eeliseks on, et kui elemendi sisu muutub, siis muudatus väljastuseks tuleb teha vaid ühes kohas.

Kontrolli, et funktsiooni poleks edastatud NULL-viita. NULL-viida puhul väljasta veateade, kehtiva viida puhul väljasta elemendi sisu.
* **/

void PrintNode(list *pNode)
{
	if (pNode)
	{
		printf("ID: %d\n", pNode->id);
		printf("Name: %s\n", pNode->name);
		printf("pNext: %p\n", pNode->pNext);
		printf("pCurr: %p\n", pNode);
		putchar('\n');
	}
	else // if (pNode == NULL) // 	//~ if (!pNode)
	{
		fprintf(stderr, "No such Node exists in the list.\n\n");
	}
}

int AskId(void)
{
	printf("Enter ID: \n");
	int num;
	scanf("%d", &num);
	return num;
}

char *AskName(char str[MAX_STR], int max)
{
	printf("Enter a name: \n");
    while(1)
    {
		//~ scanf("%[^\n]", str);
		fgets(str, max, stdin);
		if (strcmp(str, "") == 0)
			continue;
		else if (strcmp(str, "\n") == 0)	
			continue;
		else 
			break;
			
	}
	size_t len = strlen(str);
	
	/** Write the string terminator in place of the newline to fix the string **/
	str[len-1] = '\0'; // Between ' ' (bc \0 is 1 byte, char; DO NOT " ")
	
	#ifdef DEBUG
	DebugString(str);
    #endif

    
	#ifdef DEBUG
    printf("String is '%s'. Pointer: %p.\n", str, str); /** ASK **/
    #endif
    
	return str;
}


struct node *CreateNode(char *name)
{
	
	#ifdef DEBUG /** **/
	printf("name is '%s'. Pointer: %p.\n", name, name); /** ASK **/
	#endif
	
	if (name == NULL)
		return NULL;
	else 
	{	
		#ifdef DEBUG
		printf("strlen(%s)=%ld\n", name, strlen(name));
		#endif
		
		/** Loo ja anna mälu uuele elemendile **/
		struct node *pNew = (struct node *)malloc(sizeof(struct node));
		if (pNew == NULL)
		{
			perror("Error allocating memory");
			return NULL;
		}
		
		 /**  Küsi mälu ja kopeeri struktuuri nimi **/
		pNew->name = (char *)calloc(strlen(name) + 1, sizeof(char));
		if (pNew->name == NULL)
		{
			printf("Not enough memory for name '%s'.\n", name);
			SafeFree((void **)&pNew);
			return NULL;
		}
		strcpy(pNew->name, name);

		/**  Määra ära ID väärtus (järjestikuline suurenev täisarv, 
		* 	kasuta  static  märksõna)**/
		pNew->id = (int) GetSequence(); // todo: tõsta tagasi ettepoole?
		pNew->pNext = NULL;
		return pNew;
	}
}

/**
 * Selle funktsiooni eesmärgiks on lisada eelmise funktsiooni poolt
 *  loodud uus element  pNode  ahelloendisse, millele viitab ppHead.
 *  Topeltviit on vajalik, et lisada uus element loendi algusesse.

Baasülesandes lisame uue elemendi loendi algusesse. 
* Selleks on vaja ainult 2 omistuslauset kirjutada!
NB! Enne lisamist kontrolli, et  pNode  poleks NULL -viit!
 **/
void InsertNode(list **pHead, struct node *pNode)
{
	if (pNode == NULL)
	{
		puts("Cannot Insert a node. pNode is NULL. Will exit function.\n");
		return;
	}
	else if (pHead == NULL)
	{
		puts("Cannot Insert a node. pHead is NULL. Will exit function.\n");
		return;
	}
	
	/** Stsenaarium 0: Node-list on tühi. Lisatakse tühja listi loodav Node. **/
	if (*pHead == NULL)
	{
		/** Sea loodud elemendi viit järgmisele elemendile (pNext) näitama senise loendi algusele (*pHead)**/
		pNode->pNext = *pHead;

		/** Sea loendi algus viitama vastloodud elemendile (pNode)**/
		*pHead = pNode;
		return;
	}
	
	
	struct node *pCurrent = NULL;
	pCurrent = *pHead; // works like i = 0
	
	/** Stsenaarium 1: Algusesse lisamine. Lisatava node'i nimi on leksiograafiliselt väiksem (str1 ASCII väärtus on väiksem) kui esimese node'i nimi. **/
	if (strcmp(pNode->name, pCurrent->name) < 0)
	{
		/** Sea loodud elemendi viit järgmisele elemendile (pNext) näitama senise loendi algusele (*pHead)**/
		pNode->pNext = *pHead;
		
		/** Sea loendi algus viitama vastloodud elemendile (pNode)**/
		*pHead = pNode;
		return;
	}
	
	
	/** Stsenaarium 2: Keskele lisamine. **/
	/** Traverse the list while pCurrent->pNext is not NULL, until pNext->id == id **/
	while (pCurrent->pNext && (strcmp(pNode->name, pCurrent->pNext->name) >= 0))
	{
		pCurrent = pCurrent->pNext; /** Landing on pCurrent, that is one before id == id **/
	}
	
	if (pCurrent->pNext && (strcmp(pNode->name, pCurrent->pNext->name) < 0))
	{
		/** Sea loodud elemendi viit pNext viitama järgmisele elemendile**/
		pNode->pNext = pCurrent->pNext;
		
		/** Sea praeguse elemendi viit näitama loodud elemendile**/
		pCurrent->pNext = pNode;
		return;
	}
	/** Stsenaarium 3: Lõppu lisamine**/ 
	else if (pCurrent->pNext == NULL) // rethink // if (pCurrent->pNext = NULL || (strcmp(pNode->name, pCurrent->pNext->name) > 0))
	{
		/** Sea loodud elemendi viit pNext viitama NULL, muutmaks selle pNode'i lõpp node'iks.**/
		pNode->pNext = NULL;
		
		/** Sea praeguse elemendi viit näitama loodud elemendile**/
		pCurrent->pNext = pNode;
		return;
	}
	/** Stsenaarium 3: Lõppu lisamine**/
}

/**
 * Seda funktsiooni kutsutakse hävitajaks (destructor),
 *  	mille eesmärk on andmestruktuur mälust vabastada.
 * Vabastamise käigus vabastatakse ka struktuuri liikmed,
 *  mis on dünaamiliselt loodud – meie puhul on selleks nimi.
 **/
void Unload(list *pHead)
{
	if (pHead == NULL)
		//~ fprintf(stderr, "Unload : pHead is NULL. Will exit function.\n");//~ return;
		fprintf(stderr, "No memory allocation to be free()-d for pointer.\n");//~ return;
	else 
	{
		list *pCurrent = pHead; // works like i = 0
		list *pTemp;
		while(pCurrent)  // for (pTemp = pHead; pTemp; pTemp = pTemp->pNext) // ''works like i < 0''
		{
			/** 1. Praeguse elemendi aadressist koopia tegemine (seda koopiat kasutame vabastamiseks) **/
			pTemp = pCurrent;
			
			/** 2. Järgmise elemendi juurde liikumine ( pCurrent = pCurrent->pNext )**/
			pCurrent = pCurrent->pNext; // works like i++;
			
			/** 3. Praeguse elemendi ja selle liikmete vabastamine.**/
			SafeFree((void**) &pTemp->name);
			SafeFree((void**) &pTemp);
			puts("Memory free()-d.\n");
		}
	}
}
/**
 *Selles osas loome otsingufunktsiooni, otsib nime väärtuse järgi.
 *  Kui otsing annab tulemust (st loendis on selline element),
 *  tagastatakse viit leitud elemendile. 
 * Kui elementi loendis ei ole, tagastatakse NULL-viit.
 * */
struct node *FindNodeByName(list *pHead, char *name)
{
	struct node *pTemp = NULL;
	if (!pHead || !name)
	{
		fprintf(stderr, "Invalid input given to, thus cannot find node by name.\n");
		//~ return pTemp;
	}
	else
	{
		for (pTemp = pHead; pTemp; pTemp = pTemp->pNext)
		{
			int strcmpVal = strcmp(pTemp->name, name);
			if (strcmpVal == 0)
			{
				return pTemp;
			}
			else if(strcmpVal > 0)
			{
				printf("'%s' cannot be found. Breaking out to optimize find / search.\n", name);
				pTemp = NULL;
				return pTemp;
			}
		}
	}
	return pTemp;
}

/**
 *Selles osas loome otsingufunktsiooni, otsib ID väärtuse järgi.
 *  Kui otsing annab tulemust (st loendis on selline element),
 *  tagastatakse viit leitud elemendile. 
 * Kui elementi loendis ei ole, tagastatakse NULL-viit.
 * */
struct node *FindNodeByID(list *pHead, int id)
{
	struct node *pTemp = NULL;
	if (pHead)
	{
		for (pTemp = pHead; pTemp; pTemp = pTemp->pNext)
		{
			if (pTemp->id == id)
				return pTemp;
		}
	}
	return pTemp; /** works like else (pHead==NULL) returning NULL OR, not no match, returns NULL**/
}

/**
 *Realiseeri  RemoveNodeByName()  funktisoon, mis eemaldab elemendi nimelise vaste korral.
 **/
void RemoveNodeByID(list **pHead, int id)
{
	if (pHead)
	{
		struct node *pCurrent = NULL;
		pCurrent = *pHead; // works like i = 0
		/** Esimese elemendi eemaldamine, juhul kui ühtib esimese ID-ga**/
		if (pCurrent->id == id)
		{
			/** Algusviit viitab edaspidi järgmisele, kuna algupärane vabastatakse **/
			*pHead = pCurrent->pNext;
			
			SafeFree((void **) &(pCurrent->name));
			SafeFree((void **) &pCurrent); /** pNext will be set NULL. **/
			return;
		}
			
		/** Traverse the list (to right position) while pCurrent->pNext is not NULL, until pNext->id == id **/
		while (pCurrent->pNext && pCurrent->pNext->id != id)
		{
			/**2. Järgmise elemendi juurde liikumine ( pCurrent = pCurrent->pNext )**/
			pCurrent = pCurrent->pNext; /** Landing on pCurrent, that is one before id == id **/
		}

		/** Check if node with the ID was found **/
		/** Viit järgmisele hüppab ülejärgmisele, enne mälu vabastamist **/
		if (pCurrent->pNext && pCurrent->pNext->id == id)  /** must check pCurrent->Next (!= NULL), end-node might still not have id==id.**/
		{
			struct node *temp = pCurrent->pNext;
			
			pCurrent->pNext = temp->pNext;
			
			SafeFree((void **)&(temp->name));
			SafeFree((void **)&temp); /** pNext will be set NULL. **/
			return;
		}
	}
	else
	{
		fprintf(stderr, "No such node can be found with id: '%d'", id);
	}
	// return; /** works like else (pHead==NULL) returning NULL OR, not no match, returns NULL**/
}


/**
 * Realiseeri RemoveNodeByID()  funktsioon, mis eemaldab elemendi ID vaste korra.
 **/
void RemoveNodeByName(list **pHead, char *name)
{
	
	if (pHead)
	{
		struct node *pCurrent = NULL;
		pCurrent = *pHead; // works like i = 0
		
		if (strcmp(pCurrent->name, name) == 0)
		{
			// Adjust head pointer to point to the next node
			*pHead = pCurrent->pNext;

			SafeFree((void **)&(pCurrent->name));
			SafeFree((void **)&pCurrent); /** pNext will be set NULL. **/
			return; // Node removed, exit loop
		}

		/** Traverse the list (to right position) while pCurrent->pNext is not NULL, until pNext->id == id **/
		while (pCurrent->pNext && (strcmp(pCurrent->pNext->name, name) != 0))
		{
			pCurrent = pCurrent->pNext; /** Landing on pCurrent, that is one before id == id **/
		}

		/** Check if node with the ID was found **/
		/** Viit järgmisele hüppab ülejärgmisele, enne mälu vabastamist **/
		if (pCurrent->pNext && (strcmp(pCurrent->pNext->name, name) == 0)) /** must check pCurrent->Next (!= NULL), end-node might still not have name==name.**/
		{
			struct node *temp = pCurrent->pNext;

			/** Skip the node by setting pCurrent->pNext to the node after it **/
			pCurrent->pNext = temp->pNext;

			SafeFree((void **)&(temp->name));
			SafeFree((void **)&temp); /** pNext will be set NULL. **/
			return;
		}
	}
	else
	{
		fprintf(stderr, "No such node can be found with name '%s'", name);
	}
}


/**
 * Realiseeri RemoveNodeByID()  funktsioon, mis eemaldab elemendi ID vaste korra.
 **/
void RemoveNodeByName2(list **pHead, char *name)
{
	struct node *pCurrent = NULL;
	if (pHead)
	{
		for (pCurrent = *pHead; pCurrent; pCurrent = pCurrent->pNext)
		{
			  // Check if at the head and names match
			  if (pCurrent == *pHead && (strcmp(pCurrent->name, name) == 0))
			  {
					// Adjust head pointer to point to the next node
					*pHead = pCurrent->pNext;

					SafeFree((void **)&(pCurrent->name));
					SafeFree((void **)&pCurrent); /** pNext will be set NULL. **/
					break; // Node removed, exit loop
			  }

			  // Traverse the list while pCurrent->pNext is not NULL
			  while (pCurrent->pNext && (strcmp(pCurrent->pNext->name, name) != 0))
			  {
				pCurrent = pCurrent->pNext; /** Landing on pCurrent, that is one before id == id **/
			  }

			  // Check if node with the name was found
			  //~ if (pCurrent->pNext && pCurrent->pNext->name && (strcmp(pCurrent->pNext->name, name) == 0))
			  if (pCurrent->pNext && (strcmp(pCurrent->pNext->name, name) == 0))
			  {
					struct node *temp = pCurrent->pNext;

					// Skip the node by setting pCurrent->pNext to the node after it
					pCurrent->pNext = temp->pNext;

					SafeFree((void **)&(temp->name));
					SafeFree((void **)&temp); /** pNext will be set NULL. **/
				}
		}
	}
	else
	{
		fprintf(stderr, "No such node can be found with name '%s'", name);
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
