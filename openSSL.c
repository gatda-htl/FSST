/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Name: Gatt David, Betreuer: Lezuo, Klasse: 5bHEL, durchgeführt im Maerz 2021, abgegeben am 10.03.2021
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Aufgabe: Programm, das aus einem hardgecodeten Cyphertext mit Hilfe von Dateieneingelesenem Key und IV zu decrypten
//auszugeben
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Github: 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define Buf_size 16     //Bufsize wird benoetigt zum Datein oeffnen 

unsigned char key[16];  //global nicht guenstig kenne aber keine andere Moeglichkeit
unsigned char iv[16];

int Input(char* FileKey, char* FileIv)  //Aufgabe von der Funktion Input ist es aus 2 Files den Key und IV heraus zu lesen
{
    int DES_open_key, DES_open_iv, DES_read_key, DES_read_iv;   
    DES_open_key = open(FileKey, O_RDONLY);
        if (DES_open_key < 0)
        {
            perror("Failed at opening Key");
        }

    DES_read_key = read(DES_open_key, key, Buf_size);       //key wird auf die globale Variable key geschrieben
        if (DES_read_key < 0)
        {
            perror("Failed at reading Key");
        }

    DES_open_iv = open(FileIv, O_RDONLY);
        if(DES_open_iv < 0)
        {
            perror("Failed at opening Iv");
        }

    DES_read_iv = read(DES_open_iv, iv, Buf_size);          //iv wird auf die globale variable iv geschrieben
        if(DES_read_iv < 0)
        {
            perror("Failed at reading iv");
        }
        
    if(close(DES_open_key))
    {
        perror("Failed at closing Key");
    }

    if(close(DES_open_iv))
    {
        perror("Failes at closing Iv");
    }
}


int main(int argc, char** argv)
{
Input(*(argv+1), *(argv+2));   //Einlesen von Key und iv
unsigned char text[128];    //decryptet text

unsigned char cyphertext[128] = {0xAA, 0xE3, 0x65, 0x27, 0x2C, 0x81, 0x07, 0x8A, 0xB6, 0x11, 0x6B, 0x36, 0x18, 0x31, 0xD0, 0xF6, 0xA5, 0xD3, 0xC8, 0x58, 0x7E, 0x94, 0x6B, 0x53, 0x0B, 0x79, 0x57, 0x54, 0x31, 0x07,0xF1, 0x5E};
//cxphertext vorgegeben in der Aufgabenstellung

AES_KEY dec_key;        //Ersellen von dec_key mit dem Datentyp AES_KEY
AES_set_decrypt_key(key, sizeof(key)*8, &dec_key);  //key wird umgeschrieben?

AES_cbc_encrypt(cyphertext, text, sizeof(cyphertext)/4, &dec_key, iv, AES_DECRYPT); //Cyphertext wird decryptet 
// AES_cbc_encrypt beinhaltet decrypt Unterscheidung de-encrypt mit if (enc)

printf("-Nachricht: %s\n", text);   //ausgeben des Texts
}
            