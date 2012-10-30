#include "ParsedFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include <tr1/unordered_map>
#include "Book.h"
#include "Histogram.h"
#include <vector>
#include <algorithm>
#include <locale>
#include <string>

using namespace std;

/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main() {
    //Engine requirements
    string dir = string("./test/");
    vector<string> files = vector<string>();
    getdir(dir,files); //Anade los files del directorio al vector
    tr1::unordered_map<string, Histogram> engine;
    
    locale filter;
    
    //Stopwords requirements
	vector<string> stopWords;//Lista esta sorted, so binary search for the win.
    ifstream stopFile("../stopwords.txt");
    
    do {
        string parse;
        stopFile >> parse;
        stopWords.push_back(parse);
    } while (!stopFile.eof());

    stopFile.close();
    
    //Montar el engine. Contiene un hash table para index las palabras.
    //El key es la palabra, el value es un Histograma que mantiene un LL y
    //un counter total. El LL mantiene un historial de libros con su titulo y
    //apariciones de la palabra.
    for (int i = 0; i < files.size(); i++) {
        
        //cout<<files[i]<<endl<<endl;
        
        if (files[i].c_str()[0]!='.') { //Trampa de Arce para evitar hidden files
            
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            
            for (int j = 0; j < words.size(); j++) {
                //cout<<words[j]<<endl;
                
                //Clean word
                for (int k = 0; k < words[j].length(); k++) {
                    if(!isalpha(words[j][k], filter)) {
                        words[j].erase(k,1);
                    }
                }

                //If the word is not in stopwords.txt, add it to the engine
                if (!binary_search(stopWords.begin(), stopWords.end(), words[j])) {
                    //If found, increase counter
                    tr1::unordered_map<string, Histogram>::iterator mapIndex = engine.find(words[j]);
                    if (mapIndex != engine.end()) {
                        //If findAndAdd book doesn't work, add book.
                        if (!mapIndex->second.findAndAdd(files[i])) {
                            mapIndex->second.addBook(files[i]);
                        }
                    }
                    //If not found, add the word
                    else {
                        Histogram newHistogram(files[i]);
                        engine[words[j]] = newHistogram;
                    }
                }
            }
        }
    }
    
        
}
