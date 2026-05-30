#include <stdio.h>
#include <stdlib.h>

// pinu piir
#define STACK_SIZE 3

typedef struct
{
	
	int *data; // pinus olevad andmed
	int size; // pinu praegune suurus / pinuviit
} stack;

void DebugStack(stack st);
void Push(stack *st, int val);

int main(void)
{
	
	stack myStack = {.data = NULL,
					 .size = 0};
					 
	DebugStack(myStack);
	
	Push(&myStack, 25);
	DebugStack(myStack);
	
	Push(&myStack, 93);
	DebugStack(myStack);
	
	Push(&myStack, 4);
	DebugStack(myStack);
	
	Push(&myStack, 192);
	DebugStack(myStack);
					
	return EXIT_SUCCESS;
}

void DebugStack(stack st)
{
    printf("DEBUG\n");
    printf("\tStack size: %d\n", st.size);
    printf("\tData pointer: %p\n", st.data);
    printf("\tValues: ");
    for (int i = st.size - 1; i >= 0; i--)
    {
        printf("%d ", st.data[i]);
    }
    printf("\n\n");
}


void Push(stack *st, int val)
{
	// veendun, et pinu edastati
	if (st == NULL) // pinu ennast ei ole
	{
		fprintf(stderr, "ERROR: No stack!\n");
		return;
	}
	
	// veendu, et pinu ei ole ületäitunud.
	// Pinu ületäitumise kontroll
	if (st->size >= STACK_SIZE)
	{
		fprintf(stderr, "ERROR: Stack overflow!\n");
		return;
	}
	
	// Valmistame pinu ette uue liikme jaoks, s.t laiendamine pinu
	unsigned newSize = (unsigned)st->size + 1;
	int *pTemp = (int *)realloc(st->data, newSize * sizeof(int));
	if (pTemp == NULL)
	{
		fprintf(stderr, "ERROR: Couldn't allocate memory for stack!\n");
		return;
	}
	st->data = pTemp;
	
	// Lisame andmed pinusse ja suurendame pinuviita (toimib indeksina)
	st->data[st->size] = val;
	st->size++;
	
	
} // end of Push
