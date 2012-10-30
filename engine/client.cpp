#include "ParsedFile.h"
#include <map>
#include <tr1/unordered_map>
#include "Book.h"
#include "Histogram.h"

using namespace std;

/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main() {
    
    string dir = string("./test/");
    vector<string> files = vector<string>();
    getdir(dir,files); //Anade los files del directorio al vector
    tr1::unordered_map<string, Histogram> engine;
    
    
    //Montar el engine.
    for (int i = 0; i < files.size(); i++) {
        
        //cout<<files[i]<<endl<<endl;
        
        if (files[i].c_str()[0]!='.') { //Trampa de Arce para evitar hidden files
            
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            
            for (int j = 0; j < words.size(); j++) {
                //cout<<words[j]<<endl;
                //Clean word.
                //Check if valid
                
                
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
    
    tr1::unordered_map<string, Histogram>::iterator printer;
    for (printer = engine.begin(); printer != engine.end(); printer++) {
        cout<<printer->first<<printer->second.getTotalRepetitions()<<endl;
    }
    
	/*
	vector< map <string, int> > all_freq_tables;
    for (unsigned int i = 0;i < files.size();i++) {
    	if (files[i].c_str()[0]!='.') {
    		string tmp;
    		cout <<  "./moviesdb/" + files[i] << endl;
            vector<string> words = ParsedFile("./moviesdb/" + files[i]).readAndTokenize();
            for (int i = 0; i < words.size(); i++) {
                cout << words[i]<<endl;
            }
        }
    }
	*/
    
        
}
