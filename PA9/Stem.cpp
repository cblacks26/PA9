#include <Stem.h>

Stem::Stem(const string &str) : word(str){}

string Stem::StemWord(){
	Step1();
	Step2();
	Step3();
	Step4();
	Step5();
	Step6();
	Step7();
	Step8();
	return word;
}

void Stem::Step1(){
	if(word[0]=='\'') word = word.substr(1);
	if(FindSuffix("'s'")){
		word = word.substr(0,word.length()-3);
	}else if(FindSuffix("'s")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("'")){
		word = word.substr(0,word.length()-1);
	}
}

void Stem::Step2(){
	if(FindSuffix("sses")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("ied")||FindSuffix("ies")){
		word = word.substr(0,word.length()-3);
		if(word.length()<2){
			word += "ie";
		}else word += "i";
	}else if(FindSuffix("us")||FindSuffix("ss")){
		// do nothing
	}else if(FindSuffix("s")){
		if(ContainsVowelBefore((int)word.length()-2)){
			word = word.substr(0,word.length()-1);
		}
	}
}

void Stem::Step3(){
	int reg1 = FindRegion1();
	if(FindSuffix("eed")){
    if(isInRegion("eed",reg1)){
			word = word.substr(0,word.length()-1);
		}
  }else if(FindSuffix("eedly")){
		if(isInRegion("eedly",reg1)){
			word = word.substr(0,word.length()-3);
		}
	}else{
		int loc = 0;
		if(FindSuffix("ed")){
			loc = word.length()-2;
		}else if(FindSuffix("edly")){
			loc = word.length()-4;
		}else if(FindSuffix("ing")){
			loc = word.length()-3;
		}else if(FindSuffix("ingly")){
			loc = word.length()-5;
		}
		if(loc>0){
			if(ContainsVowelBefore(loc)){
				word = word.substr(0,loc);
				if(FindSuffix("bl")||FindSuffix("at")||FindSuffix("iz")){
					word += "e";
				}else if(EndsDouble(loc)){
					word = word.substr(0,word.length()-1);
				}else if(isShort(loc)){
					word += "e";
				}
			}
		}
	}
}

void Stem::Step4(){
	if(word.length()>1){
		if(FindSuffix("y")){
			if(isConsonant(word.length()-2)){
				word = word.substr(0,word.length()-1);
				word += "i";
			}
		}
	}
}

void Stem::Step5(){
	if(FindSuffix("ization")){
		word = word.substr(0,word.length()-5);
		word += "e";
	}else if(FindSuffix("ation")){
		word = word.substr(0,word.length()-3);
		word += "e";
	}else if(FindSuffix("ational")){
		word = word.substr(0,word.length()-5);
		word += "e";
	}else if(FindSuffix("tional")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("enci")){
		word = word.substr(0,word.length()-1);
		word += "e";
	}else if(FindSuffix("anci")){
		word = word.substr(0,word.length()-1);
		word += "e";
	}else if(FindSuffix("abli")){
		word = word.substr(0,word.length()-1);
		word += "e";
	}else if(FindSuffix("entli")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("izer")){
		word = word.substr(0,word.length()-1);
	}else if(FindSuffix("ator")){
		word = word.substr(0,word.length()-2);
		word += "e";
	}else if(FindSuffix("alism")){
		word = word.substr(0,word.length()-3);
	}else if(FindSuffix("aliti")){
		word = word.substr(0,word.length()-3);
	}else if(FindSuffix("alli")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("fulness")){
		word = word.substr(0,word.length()-4);
	}else if(FindSuffix("ousli")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("ousness")){
		word = word.substr(0,word.length()-4);
	}else if(FindSuffix("iveness")){
		word = word.substr(0,word.length()-4);
	}else if(FindSuffix("iviti")){
		word = word.substr(0,word.length()-3);
		word += "e";
	}else if(FindSuffix("biliti")){
		word = word.substr(0,word.length()-5);
		word += "le";
	}else if(FindSuffix("bli")){
		word = word.substr(0,word.length()-1);
		word += "e";
	}else if(FindSuffix("ogi")){
		word = word.substr(0,word.length()-1);
	}else if(FindSuffix("fulli")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("lessli")){
		word = word.substr(0,word.length()-2);
	}else if(FindSuffix("li")){
		if(isValidLi(((int)word.length()-3))) word = word.substr(0,word.length()-2);
	}
}

void Stem::Step6(){
	int reg1 = FindRegion1();
	int loc;
	if(FindSuffix("ational")){
		loc = word.find("ational");
		if(loc>reg1){
			word = word.substr(0,word.length()-5);
			word += "e";
		}
	}else if(FindSuffix("tional")){
		loc = word.length()-6;
		if(loc>reg1) word = word.substr(0,word.length()-2);
	}else if(FindSuffix("alize")){
		loc = word.length()-5;
		if(loc>reg1) word = word.substr(0,word.length()-3);
	}else if(FindSuffix("icate")){
		loc = word.length()-5;
		if(loc>reg1) word = word.substr(0,word.length()-3);
	}else if(FindSuffix("iciti")){
		loc = word.length()-5;
		if(loc>reg1) word = word.substr(0,word.length()-3);
	}else if(FindSuffix("ical")){
		loc = word.length()-4;
		if(loc>reg1) word = word.substr(0,word.length()-2);
	}else if(FindSuffix("ful")){
		loc = word.length()-3;
		if(loc>reg1) word = word.substr(0,word.length()-3);
	}else if(FindSuffix("ness")){
		loc = word.length()-4;
		if(loc>reg1) word = word.substr(0,word.length()-4);
	}else if(FindSuffix("ative")){
		if(FindRegion2(reg1)<static_cast<int>(word.length()-5)) word = word.substr(0,word.length()-5);
	}
}

void Stem::Step7(){
	int reg1 = FindRegion1();
	int reg2 = FindRegion2(reg1);
	if(reg1>0&&reg2>reg1){
		if(FindSuffix("al")){
			if(isInRegion("al",reg2)) word = word.substr(0,word.length()-2);
		}else if(FindSuffix("ance")){
			if(isInRegion("ance",reg2)) word = word.substr(0,word.length()-4);
		}else if(FindSuffix("ence")){
			if(isInRegion("ence",reg2)) word = word.substr(0,word.length()-4);
		}else if(FindSuffix("er")){
			if(isInRegion("er",reg2)) word = word.substr(0,word.length()-2);
		}else if(FindSuffix("ic")){
			if(isInRegion("ic",reg2)) word = word.substr(0,word.length()-2);
		}else if(FindSuffix("able")){
			if(isInRegion("able",reg2)) word = word.substr(0,word.length()-4);
		}else if(FindSuffix("ible")){
			if(isInRegion("ible",reg2)) word = word.substr(0,word.length()-4);
		}else if(FindSuffix("ant")){
			if(isInRegion("ant",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ement")){
			if(isInRegion("ement",reg2)) word = word.substr(0,word.length()-5);
		}else if(FindSuffix("ment")){
			if(isInRegion("ment",reg2)) word = word.substr(0,word.length()-4);
		}else if(FindSuffix("ent")){
			if(isInRegion("ent",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ism")){
			if(isInRegion("ism",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ate")){
			if(isInRegion("ate",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("iti")){
			if(isInRegion("iti",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ous")){
			if(isInRegion("ous",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ive")){
			if(isInRegion("ive",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ize")){
			if(isInRegion("ize",reg2)) word = word.substr(0,word.length()-3);
		}else if(FindSuffix("ion")){
			if(isInRegion("ion",reg2)){
				if(word[word.length()-4]=='s'||word[word.length()-4]=='t'){
					word = word.substr(0,word.length()-3);
				}
			}
		}
	}
}

void Stem::Step8(){
	int reg1 = FindRegion1();
	int reg2 = FindRegion2(reg1);
	if(FindSuffix("e")){
		if(isInRegion("e",reg1)){
			if(!isShort(static_cast<int>(word.length()-2))){
        word = word.substr(0,word.length()-1);
      } 
		}
	}else if(FindSuffix("l")){
		if(isInRegion("l",reg2)){
			if(FindSuffix("ll")) word = word.substr(0,word.length()-1);
		}
	}
}

bool Stem::FindSuffix(const string suffix)const{
	for(int i=word.length()-1, j=suffix.length()-1; i > ((int)(word.length()-suffix.length())-1);i--,j--){
		if(word[i]!=suffix[j])return false;
	}
	return true;
}

int Stem::GetSuffix(const string suffix)const{
	if(FindSuffix(suffix)){
		return ((int)(word.length()-suffix.length()));
	}else return -1;
}

bool Stem::isInRegion(const string comp, const int reg)const{
	int loc = GetSuffix(comp);
	if(loc==-1) return false;
	if(reg==-1) return false;
	if(loc>=reg) return true;
	return false;
}

bool Stem::isValidLi(const int i)const{
	switch(word[i]){
		case 'c': case 'd': case 'e': case 'g': case 'h': case 'k': case 'm':
		case 'n': case 'r': case 't':
			return true;
		default:
			return false;
	}
}

bool Stem::isShort(const int i)const{
	if(isShortSyllable(i)){
		int reg = FindRegion1();
		if(reg==-1||reg>i){
			return true;
		}
	}
	return false;
}

bool Stem::isShortSyllable(const int i)const{
	if(i==1){
		if(isVowel(i-1)&&isConsonant(i)) return true;
	}else{
		if(isConsonant(i-2)&&isVowel(i-1)&&isConsonant(i)){
			if(word[i]!='x'&&word[i]!='y'&&word[i]!='w') return true;
		}
	}
	return false;
}

int Stem::FindRegion1()const{
	for(int i = 0;i<((int)word.length());i++){
		if(isVowel(i)){
			if(isConsonant(i+1)){
				if(i+2>=static_cast<int>(word.length())) return -1;
				return i+2;
			}
		}
	}
	return -1;
}

int Stem::FindRegion2(const int reg1)const{
	for(int i = reg1;i<((int)word.length());i++){
		if(isVowel(i)){
			if(isConsonant(i+1)){
				if(i+2>=static_cast<int>(word.length())) return -1;
				return i+2;
			}
		}
	}
	return -1;
}

bool Stem::isVowel(const int i)const{
	if(word[i]=='a'||word[i]=='e'||word[i]=='i'||word[i]=='o'||word[i]=='u') return true;
	else if(word[i]=='y'){
		if(i!=0){
			return isConsonant(i-1);
		}
	}
	return false;
}

bool Stem::ContainsVowel()const{
	for(char c:word){
		if(isVowel(c)) return true;
	}
	return false;
}

bool Stem::ContainsVowelBefore(const int length)const{
	for(int i = 0; i<length;i++){
		if(isVowel(i)) return true;
	}
	return false;
}

bool Stem::isConsonant(const int i)const{
	return !isVowel(i);
}

bool Stem::FindStringBefore(const string comp, const int i)const{
	int loc = word.find(comp);
	if(loc<i&&loc>0) return true;
	return false;
}

bool Stem::EndsDouble(const int i)const{
	if(FindStringBefore("bb",i)||FindStringBefore("dd",i)||FindStringBefore("ff",i)||FindStringBefore("gg",i)||FindStringBefore("mm",i)||
	FindStringBefore("nn",i)||FindStringBefore("pp",i)||FindStringBefore("rr",i)||FindStringBefore("tt",i)){
		return true;
	}else{
		return false;
	}
}
