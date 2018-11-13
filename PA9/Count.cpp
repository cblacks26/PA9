#include <Count.h>

Count::Count(const string name, const Exception& exception) : startSentence(true), letterAmount(0), wordAmount(0), sentenceAmount(0), readingLevel(0), docName(name), ex(exception){}

Count::Count(const string name) : startSentence(true), letterAmount(0), wordAmount(0), sentenceAmount(0), readingLevel(0), docName(name){}

bool Count::Read(istream& istr){
	bool res = false;
	string str;
	while(istr >> str){
		Eval(str);
		res = true;
	}
	if(res){
		if(istr.eof()){
			if(wordAmount==0){
				cerr << "can't divide by 0" << endl;
				return false;
			}
			readingLevel = (0.0588*100.0*(letterAmount/wordAmount))-(0.296*100.0*(sentenceAmount/wordAmount))-15.8;
			return true;
		}else{
			return false;
		}
	}else{
		cerr << "Error reading file" << endl;
		return false;
	}
	
}

double Count::getReadingLevel()const{
	return readingLevel;
}

string Count::getDocumentName()const{
	return docName;
}

int Count::getCountOfWord(const string& str) const{
	unordered_map<string, int>::const_iterator it = wordCount.find(str);
	if(it==wordCount.end()) return 0;
	return it->second;
}

int Count::getStemCountOfWord(const string& str) const{
	unordered_map<string, int>::const_iterator it = stemWordCount.find(str);
	if(it==wordCount.end()) return 0;
	return it->second;
}

unordered_map<string, int> Count::getStemWordCountMap()const{
	return stemWordCount;
}

void Count::StemWords(){  
	for(std::pair<std::string, int> element:wordCount){
    string word = element.first;
		if(word[0]=='+'){
			int c = element.second + getCountOfWord(word.substr(1));
			if(c<2){
				word = word.substr(1);
				word[0] = tolower(word[0]);
			}
		}
		if(isalpha(word[0])){
			if(isStemable(word)){
				string tmp = ex.getWord(word);
				if(tmp!=""){
					word = tmp;
				}else{
					Stem stem(word);
					word = stem.StemWord();
				}
			}
		}else if(word[0]=='+'){
			word = word.substr(1);
		}else if(word[0]=='\''){
			Stem stem(word);
			word = stem.StemWord();
		}
    unordered_map<string, int>::iterator itr = stemWordCount.find(word);
    if(itr==stemWordCount.end()){
      stemWordCount.insert({word,element.second});
    }else{
      itr->second += element.second;
    }
	}
}

bool Count::isStemable(const string& str)const{
	if(str.length()<3) return false;
  for(char c:str){
    if(isalpha(c)){
			if(isupper(c)) return false;
		}else if(isPunct(c)) return false;
  }
  return true;
}

// is setup to add all alpha of all non alpha strings to vector
// delimeters create a seperate call recursively to seperate them
void Count::Eval(string& str){
	if(static_cast<int>(str.length())==1){
		addWord(str);
		return;
	}
	for(int i = 0;i<static_cast<int>(str.length());i++){
		if(isPunct(str[i])){
			if(i==static_cast<int>(str.length())-1){
				if(!isPunct(str[i-1])){
					Seperate(str,i);
				}else{
					addWord(str);
				}
			}else if(str[i]=='.'){
				HandlePeriod(str,i);
			}else if(str[i]==','){
				HandleComma(str,i);
			}else{
				if(i==0){
					if(!isPunct(str[i+1])) Seperate(str,++i);
				}else{
					if(!isPunct(str[i-1])) Seperate(str,i);
					else if(!isPunct(str[i+1])) Seperate(str,++i);
				}
			}
		}else{
			if(i==static_cast<int>(str.length())-1){
				if(isdigit(str[i])&&(str[i-1]=='.'||str[i-1]==',')){
					addWord(str);
				}else if(isPunct(str[i-1])){
					Seperate(str,i);
				}else{
					addWord(str);
				}
			}
		}
	}
}

void Count::HandlePeriod(const string& str, int& i){
  if(i!=0){
		if(isalpha(str[i-1])) Seperate(str,i);
		else if(!isPunct(str[i-1])&&isPunct(str[i+1])) Seperate(str,i);
		else if(isPunct(str[i-1])&&!isPunct(str[i+1])) Seperate(str,++i);
		else if(isalpha(str[i+1])) Seperate(str,i);
	}else if(!isdigit(str[i+1])&&!isPunct(str[i+1])){
		Seperate(str,++i);
	}
}

void Count::HandleComma(const string& str, int& i){
	//check if its the first character
	if(i==0){
		if(!isPunct(str[i+1])) Seperate(str,++i);
	}else{
		if(isdigit(str[i-1])){
			if(!isdigit(str[i+1])) Seperate(str,i);
		}else if(isPunct(str[i-1])){
			if(!isPunct(str[i+1])) Seperate(str,++i);
		}else{
			Seperate(str,i);
		}
	}
}

string Count::AddCap(const string& str){
	for(string::const_iterator it = str.cbegin();it!=str.cend();++it){
		if(!isalpha(*it)&&*it!='\''){
			return str;
		}else if(it==str.cbegin()){
			if(!isupper(*it)){
				return str;
			}
		}else if(isupper(*it)){
			return str;
		}
	}
	if(startSentence){
		return "+"+str;
	}
	return str;
}

bool Count::isEndString(const string& str)const{
	if(str.empty()) return false;
	for(char c:str){
    if(isdigit(c)) return false;
		else if(c=='!'||c=='.'||c=='?') return true;
	}
	return false;
}

inline bool Count::isPunct(const char& c)const{
	if(c=='\'')return false;
	return ispunct(c);
}

void Count::Seperate(const string& str, int& i){
	addWord(str.substr(0,i));
	string temp = str.substr(i);
	if(temp.size()==1) addWord(temp);
	else Eval(temp);
	i = ((int)str.length()+1);
}

void Count::addWord(const string& str){
	if(isEndString(str)){
		sentenceAmount++;
		startSentence = true;
	}else if(isWord(str)){
		string s = AddCap(str);
		startSentence = false;
    wordAmount++;
    for(char c:s){
      if(isalnum(c)||c=='\''||c=='.'||c==',') letterAmount++;
    }
		unordered_map<string, int>::iterator it = wordCount.find(s);
		if(it==wordCount.end()){
			wordCount.insert({s,1});
		}else{
			it->second++;
		}
	}
}

bool Count::isWord(const string& str)const{
	for(char c:str){
		if(!isPunct(c)) return true;
	}
	return false;
}
