/*
   ParsedFile.cpp
   
   Este archivo contiene implementaciones para funciones miembro
   de la clase ParsedFile y algunas otras funciones.
*/


#include "ParsedFile.h"

vector<string> ParsedFile::readAndTokenize() {
  	string line;
  	ifstream myfile (name.c_str());
	vector<string> result;
 
 	if (myfile.is_open()) {
		while ( myfile.good() ) {
			// for every line in the file, tokenize and store
			// to a vector of strings.
			getline (myfile,line);
			vector<string> tokenized_line = tokenize(line, " "); 
			for(uint i=0; i<tokenized_line.size(); i++)
				result.push_back(tokenized_line[i]);
		}
		myfile.close();
	}
	else cout << "readAndTokenize: Unable to open file, returning empty vector"; 
	return result;
}


vector<string> tokenize(const string & str, const string & delim) {
	vector<string> tokens;
	size_t p0 = 0, p1 = string::npos;
	while(p0 != string::npos) {
    	p1 = str.find_first_of(delim, p0);
    	if(p1 != p0) {
      		string token = str.substr(p0, p1 - p0);
      		tokens.push_back(token);
      	}
		p0 = str.find_first_not_of(delim, p1);
	}
	return tokens;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


