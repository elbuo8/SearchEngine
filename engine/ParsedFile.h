/*
   ParsedFile.h
   
   Este archivo contiene la clase ParsedFile y los prototipos de algunas 
   funciones adicionales que pueden ser utilizadas en el proyecto 
   final de CCOM 3034. 
*/

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


typedef unsigned int uint;

using namespace std;

class ParsedFile {
private:	
	string name;
public:
	ParsedFile() {};
	ParsedFile(string n) {name = n;}
	string getName() {return name;}
	
	/*
	   Esta funcion lee todos las lineas de un archivo, las 
	   separa en palabras y devuelve como vector de strings.
	   
	   Pre-cond: El objeto de clase ParsedFile ha sido asignado un nombre.
	   Post-cond: Regresa resultados como vector de strings.
	*/
	
	vector<string> readAndTokenize();
};


/*
   getdir:
   Recibe como parametro el nombre de un directorio y devuelve
   (por medio del segundo parametro) un vector de strings que contiene
   los nombres de cada uno de los archivos del directorio. El valor 
   entero que devuelve indica si la operación fue exitosa: 0 indica que
   no hubo error, cualquier otro número indica que hubo error.
   
   Pre-condicion:  Ninguna
   Post-condición: Cambia el contenido del vector pasado 
                   como segundo parámetro.
*/
int getdir (string, vector<string> &);


/*
   tokenize:
   Recibe como parametros dos strings:
     - str: es el string que desamos romper en palabras 
     - delim: es el string delimitador que usaremos para determinar donde 
              partir a str.  Esto casi siempre es un espacion, coma, etc.
   
   Devuelve un vector de strings obtenidos de str.
   
   Pre-condicion:  str y delim no son strings vacios
   Post-condición: No modifica ni a str ni a delim. Devuelve el 
                   vector de strings.
*/

vector<string> tokenize(const string & str, const string & delim);


