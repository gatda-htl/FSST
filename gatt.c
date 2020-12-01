/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Author: Gatt David, Klasse: 5bHEL, Aufgabe bearbeitet November 2020, Abgabe: 29.11.2020, Betreuer: Lezuo
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Task: Implementiere binäre Suche in C, benutze die Funktion strcmp(3)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Funktionsweise: siehe Kommentare
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define Buf_Size 50000000   //Groeße des Buffers muss groß genug fur den wortbuffer sein

#define handle_error(msg)\                                         
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

char** binary_search(char* Wort, char** search_index, int mitte, int diff, int iUg, int iOg)
{
    int iAbbr=0;    //Abbruchbedinung
     while(1)
    {        

        mitte = (iUg+iOg)/2;    //mitte ist der Wert an welchem abgefragt werden soll iUg = Untergrenze vom Bereich in dem das Wort sein kann, iOg = Obergrenze in dem Bereich wo das Wort sein kann
        diff=strcmp(Wort, *(search_index+mitte));   //strcmp vergleicht 2 strings miteinander (Wort welches eingegeben wurde)(Searchindex an der Stelle mitte)
        iAbbr++;                //Abbruchbedinung wird nach jedem mal hochgezählt

        if(iAbbr==20)           //bei 20 durchläufen ist jedes Wort im searchindex abgesucht worden
        {
            
            return(NULL);       //wenn die Schleife 20 mal durchgelaufen ist und das Wort nicht gefunden wurde ist es nicht im buffer
        }
        if(diff < 0)            //ist das eingegebene Wort kleiner als das verglichene Wort, dann wird die Obergrenze verschoben
        {
            iOg = (iUg+iOg)/2;  //die neue Obergrenze ist dann der Wert wo zuvor das Wort verglichen wurde
            
        }
        else if(diff > 0)       //siehe Zeile 39 & 41
        {
            iUg = (iUg+iOg)/2;
        
        }
        else
        {
            printf("Wort gefunden: %s\n", *(search_index+((iUg+iOg)/2)));
            return(search_index+((iUg+iOg)/2)); //das gefundene Wort wird zurückgegbenen
        }
    }
}
char** index_bin(char* Wort)
{
    
    char* Buf=malloc(Buf_Size); //weist dem Buffer einen Speicherplatz mir der Größe Buf_size zu
    int iOpen, iRead,i = 0; //Rückgabewerte/Laufvariablen

    iOpen = open("wortbuffer", O_RDONLY);   //öffnet die wordbuffer datei
    if(iOpen == -1)                         //bei -1 ist das öffnen gefailt
    {
        handle_error("FILE open failed");   
    }

    iRead = read(iOpen, Buf, Buf_Size);     //liest die Datei aus und schreibt den inhalt auf den buffer
    if(iRead == -1)
    {
        handle_error("FILE read failed");
    }
    
    char** search_index=malloc(iRead);      //es wird ein Array initialisiert 
    search_index[i] = Buf;                  //das erste Wort des Buffers wird auf die 0 Stelle des search_index geschrieben

    for(int x=0; x<iRead; x++)              //iRead ist die Anzahl ausgelesenen Elemente x ist eine Lauftvariable 
    {
        if (*(Buf+x) == 0)                  //es wird bis zur 0 gegangen und anschließend wird alles bis fahin übertragen
        {
            search_index[++i] = Buf+(++x);
            printf("%s, %i\n", (char*)search_index[i], i);  //Alle Wörter die übertragen wurden, werden ausgegeben
        }
    }
   return binary_search(Wort, search_index, 0, 0, 0, i); //bin_search liefert das gefundene Wort wenn es in der Liste steht, steht es nicht in der Liste steht wird nichts übergeben
}






int main(int argc, char** argv)
{

    for (;;) {
                char input[100];    //Input Wort, welches verglichen werden soll größe von 100 is ausreichend
                fgets(input, sizeof(input), stdin);     //eingegebener Wert wird auf input geschrieben
                input[strlen(input)-1] = 0;     //Letzte Stelle bei input wird auf 0 gesetzt
                if (!strlen(input)) break;      //wird kein Input eingegeben wird abbgebrochen

                struct timeval tv_begin, tv_end, tv_diff;
               
                gettimeofday(&tv_begin, NULL);
             
                void *res = index_bin(input);   //index_bin wort_buffer wird in den search_index geschrieben Rückgabe ist das Wort wenn es gefunden wurde
             
                gettimeofday(&tv_end, NULL);

                timersub(&tv_end, &tv_begin, &tv_diff);

                if (res != NULL) {              //wird ein Wort zurückgegeben ist es != NULL daher wurde das Wort gefunden
                        printf("found\n");
                } else {                        //kein Wort gefunden
                        printf("not found\n");
                }
                printf(" in (%ld seconds %ld microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec); 
        }


    return 0;
}