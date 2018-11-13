#include <Exception.h>

bool Exception::read(istream& istr){
  // check if the stream has failed
	string str;
	while(getline(istr, str)){
		string word[2];
		int i = 0;
		char* w = strtok (&str[0]," ,.-");
		while (w != NULL){
			word[i] = w;
			++i;
			w = strtok (NULL, " ,.-");
		}
		if(i!=2){
			cerr << "Incorrect amount of words on a line" << endl;
			return false;
		}else{
			words.insert({word[0],word[1]});
		}
	}
	if(istr.eof()){
		return true;
	}else return false;
}

string Exception::getWord(const string& str)const{
	unordered_map<string, string>::const_iterator it = words.find(str);
	if(it!=words.end()) return it->second;
  return "";
}