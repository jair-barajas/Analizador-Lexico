#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#define MAX 650
#define MAX_RES 6

using namespace std;

char *PalabrasReservadas[MAX_RES] = {"if","while","return","else","int","float"};
char tokenSimbolos[MAX];
char auxWord[MAX];
string tokenNumeros[MAX];
string tokenIdentificadores[MAX];
string tokenReservadas[MAX];
string tokensNoValidos[MAX];
bool esNumero=true;
bool esIdentificador = true;

//Variables auxiliares para guardar en Tokens
int auxTR=0;
int auxTI=0;
int auxTN=0;
int auxTNV=0;

bool verificarNumero(char palabra[]);
bool verificarIdentificador(char palabra[]);
bool verificarReservada(char palabra[]);
void imprimirTokenNumeros();
void imprimirTokenSimbolos();
void imprimirTokenReservadas();
void imprimirTokenIdentificadores();
void imprimirIdentificadoresNoValidos();

main()
{
   char entrada[MAX];
   char *p = entrada;
   cout << "Ingrese el texto siguiente: ";
   fflush(stdin);
   gets(entrada);
   fflush(stdin);

   char palabra[MAX]; 
   int indexPalabra=0;
   int indexSimbolos = 0;

   //Ciclos para Iniciar diferentes arreglos.
   for(int i=0;i<MAX;i++){tokenReservadas[i] = "";} // Fin del ciclo

   for(int i=0;i<MAX;i++){tokensNoValidos[i] = "";}

   for(int i=0;i<MAX;i++){
		palabra[i] = '\0';
   }

  
   while(*p!='\0')
   {
       if((*p != ' ') && (*p !=','))  	//Primero revisa que sea distinto de un espacio ' ' y una coma ','
       {
            if((*p== ';') || (*p=='"') || (*p=='(') || (*p==')') || (*p=='+') || (*p=='-') || (*p=='*') || (*p=='/') || (*p=='#') || (*p=='<') || (*p=='>') || (*p=='='))
              {
                  tokenSimbolos[indexSimbolos] = *p;
                  indexSimbolos++;
              }
             else
             {
                 palabra[indexPalabra] = *p;
                 auxWord[indexPalabra] = *p;
                 indexPalabra++;
             }
      }
      else if((*p ==' ') || (*p ==','))
      {
         if(verificarReservada(palabra) == true){
                tokenReservadas[auxTR] = palabra;
                auxTR++;
         }else if(verificarIdentificador(palabra) == true){
                tokenIdentificadores[auxTI] = palabra;
                auxTI++;
         }else if(verificarNumero(auxWord)==true){
                tokenNumeros[auxTN] = auxWord;
                auxTN++;
         }
         for(int i=0;i<MAX;i++){palabra[i]='\0';}
         for(int i=0;i<MAX;i++){auxWord[i]='\0';}
         indexPalabra=0;
      }
      p++;
   }
	if(verificarReservada(palabra) == true){
	    tokenReservadas[auxTR] = palabra;
    	auxTR++;
   }else if(verificarIdentificador(palabra) == true){
		tokenIdentificadores[auxTI] = palabra;
		auxTI++;
   }else if(verificarNumero(auxWord)==true){
    	tokenNumeros[auxTN] = auxWord;
        auxTN++;
   }

   cout << "\nEXPRESION: " << entrada << endl;
   imprimirTokenReservadas();
   imprimirTokenSimbolos();
   imprimirTokenIdentificadores();
   imprimirTokenNumeros();
   imprimirIdentificadoresNoValidos();
	getch();
}

//imprimir los resultados.
void imprimirTokenSimbolos(){
	cout << "\n----- TOKENS SIMBOLOS -----" << endl;
	for(int i=0;i<strlen(tokenSimbolos);i++)
        cout << tokenSimbolos[i] << endl;
}

void imprimirTokenReservadas(){
	puts("\n----- TOKENS RESERVADAS -----");
	for(int i=0;i<auxTR;i++)
        cout << i+1 << ") " << tokenReservadas[i] << endl;
}

void imprimirTokenIdentificadores(){
	puts("\n----- TOKENS IDENTIFICADORES -----");
	for(int i=0;i<auxTI;i++)
        cout << i+1 << ") " << tokenIdentificadores[i] << endl;
}

void imprimirTokenNumeros(){
	puts("\n----- TOKENS NUMEROS -----");
	for(int i=0;i<auxTN;i++)
        cout << i+1 << ") " << tokenNumeros[i] << endl;
}

void imprimirIdentificadoresNoValidos(){
   if(auxTNV == 0){
        cout << "\n0 Errores, programa exitoso..." << endl;
   }
   else
   {
       for(int i=0;i<auxTNV;i++)
        cout << "\nERROR, No es Valido el Token: " << tokensNoValidos[i] << endl;
   }
}

bool verificarReservada(char palabra[]){
    int comp;
    bool esReservada=false;
    string str(palabra);
	for(int i=0; i<MAX_RES; i++)
    {
        comp = strcmp(PalabrasReservadas[i],palabra);
        if(comp == 0)
        {
            esReservada = true;
            break;
        }
    }
    return esReservada;
}

bool verificarIdentificador(char palabra[]){
	string auxPalabra = palabra;
    esIdentificador = false;
    short estado = 0;
    char *p = palabra;
    while(*p != '\0')
    {
        switch(estado)
        {
            case 0:
                if((isalpha(*p)) || (*p=='_')){
                    estado = 1;
                   esIdentificador = true;
                }
                else
                {
                    estado = 2;
                    esIdentificador = false;
                }
                p++;
             break;
             case 1:
                if((isalpha(*p)) || (isdigit(*p)) || (*p=='_')){
                    estado = 1;
                   esIdentificador = true;
                }
                else{
                    estado = 2;
                   esIdentificador = false;
                }
                p++;
             break;
             case 2:
                    //No es un identificador
                esIdentificador = false;
                *p = '\0';
             break;
        }
   }
   return esIdentificador;
}

bool verificarNumero(char palabra[]){
	string auxPalabra = palabra;
	esNumero = false;
	short estado = 0,cont=0;
	char *p = palabra;
	while(*p!='\0')
    {
        switch(estado)
        {
            case 0:
                if(isdigit(*p))
                {
                   estado = 0;
                   esNumero = true;
                   cont++;
                }
                else if( ((*p == '.') && (cont==0)) || (isalpha(*p))){
                        estado = 2;
                   esNumero=false;
                }else if(*p=='.'){
                        estado = 1;
                    esNumero = false;
                }
                p++;
             break;
             case 1:
                if(isdigit(*p)){
                    estado = 1;
                   esNumero = true;
                }else
                {
                    estado = 2;
                   esNumero = false;
                }
                p++;
             break;
             case 2:
                    esNumero = false;
                *p = '\0';
             break;
        }
   }
   if(esNumero == false){
      if(auxPalabra != ""){
   	   tokensNoValidos[auxTNV] = auxPalabra;
	      auxTNV++;
      }
   }
 	return esNumero;
}
