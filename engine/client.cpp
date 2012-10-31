#include "ParsedFile.h"
#include <iostream>
#include <fstream>
#include <tr1/unordered_map>
#include "Histogram.h"
#include <vector>
#include <algorithm>
#include <locale>
#include <string>
#include <regex.h>

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
    tr1::unordered_map<string, Histogram>::iterator mapIndex;
    
    locale filter;
    
    //Stopwords requirements
	vector<string> stopWords;//Lista esta sorted, so binary search for the win.
    ifstream stopFile("../stopwords.txt");
    
    
    cout << "Building the stopwatch list."<<endl;
    do {
        string parse;
        stopFile >> parse;
        stopWords.push_back(parse);
    } while (!stopFile.eof());

    stopFile.close();

    cout << "Done building the stopwatch list."<<endl;
    
    //Montar el engine. Contiene un hash table para index las palabras.
    //El key es la palabra, el value es un Histograma que mantiene un LL y
    //un counter total. El LL mantiene un historial de libros con su titulo y
    //apariciones de la palabra.
    cout <<endl<<"Start building the search engine."<<endl;
    for (int i = 0; i < files.size(); i++) {
        
        if (files[i].c_str()[0]!='.') { //Trampa de Arce para evitar hidden files
            
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            
            for (int j = 0; j < words.size(); j++) {
                //cout<<words[j]<<endl;
                
                //Clean words
                
                for (int k = 0; k < words[j].length(); k++) {
                    words[j][k] = tolower(words[j][k], filter);
                    if(!isalpha(words[j][k], filter)) {
                        if(words[j][k] == '\'') words[j].erase(k);
                        else words[j].erase(k--,1);
                    }
                }
				
                //If the word is not in stopwords.txt, add it to the engine
                if (!binary_search(stopWords.begin(), stopWords.end(), words[j]) && !words[j].empty()) {
                    //If found, increase counter
                    
                    mapIndex = engine.find(words[j]);
                    if (mapIndex != engine.end()) {
                
                		engine[words[j]].add(files[i]);
                    }
                    //If not found, add the word
                    else {

                        //Histogram newHistogram(files[i]);
                        engine[words[j]] = Histogram(files[i]);
                    }
                }
            }
        }
    }
    cout<<"Done building search engine."<<endl;


    //Empieza el I/O con el usuario.
    
    
    cout<<endl<<"Submit your words bro! Enter 0 when done."<<endl;
    string parse;
    cin >> parse;
    while (parse != "0") {
		

    }
    
    return 0;
        
}
