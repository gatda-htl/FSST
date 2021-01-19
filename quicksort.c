/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Author: Gatt David, Class: 5bHEL, Year: 2020/2021, Subject: FSST, Supervisor: Lezuo
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Project: FSST
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Funktion: Der Quicksort Algorithmus sortiert ein Array nach der Größe. Dazu wird ein zufälliger Wert(pivot) genommen (in unserem Fall nicht zufällig sondern letzte Zahl im Array),
//danach wird das Array in 2 Arrays aufgeteil kleinere Werte wie der pivot Wert kommen in das eine, Werte die größer sind in das andere. Danach wird ein neuer pivot Wert genommen und 
//der ganze Prozess läuft erneut ab. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>

//Diese Funktion wird benutzt um Arrays auszutauschen
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

//Pivot wird richtig gesetzt, alle kleineren Elemete werden links von pivot geschrieben, alle größeren rechts
int partition (int a[], int us, int os) 
{ 
    int pivot = a[os];     
    int i = (us - 1);   
  
    for (int j = us; j <= os- 1; j++) 
    { 
        if (a[j] <= pivot) 
        { 
            i++;    
            swap(&a[i], &a[j]); 
        } 
    } 
    swap(&a[i + 1], &a[os]); 
    return (i + 1); 
} 

//Die Funktion ruft sich solange selbst auf, bis die Abbruchbedinung auftritt
void qs(int *a, int us, int os)
{
	if (us < os) 
    { 
        int pi = partition(a, us, os); 
        qs(a, us, pi - 1); 
        qs(a, pi + 1, os); 
    } 
}

// creates a array of size size and fills it with random ints in range 0 to max_int
int *create_array(int size, int max_int)
{
	int *b = (int*)malloc(size * sizeof(int));

	for (int i=0; i<size; i++) {
		b[i] = rand() % max_int;
	}

	return b;
}

#define MY_SIZE 100000

int main(int argc, char **argv)
{
	// create random ints based in current time
	srand(time(NULL));

        int *a = create_array(MY_SIZE, 100);

    struct timeval tv_begin, tv_end, tv_diff;
	gettimeofday(&tv_begin, NULL);
	qs(a, 0, MY_SIZE);
    gettimeofday(&tv_end, NULL);
    timersub(&tv_end, &tv_begin, &tv_diff);
	int old = -1;
	for (int i=0; i<MY_SIZE; ++i)      {
		if (old != -1) assert(old <= a[i]);
		printf("%d ", a[i]);
		old = a[i];
	}
	printf("\n");
    printf("%i elements sorted in %ld seconds %ld microseconds\n", MY_SIZE, tv_diff.tv_sec, tv_diff.tv_usec);
    /* Zeiten immer zwischen 74ms und 100ms fpr 900 Elemente sortieren*/
    
    }