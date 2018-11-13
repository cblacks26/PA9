#ifndef STEM_H_INCLUDE
#define STEM_H_INCLUDE

#include<string>
#include<iostream>
using std::string;
using std::cout;
using std::endl;

class Stem{
	public :
	
		Stem(const string& str);
	
		string StemWord();
		void Step1();
		void Step2();
		void Step3();
		void Step4();
		void Step5();
		void Step6();
		void Step7();
		void Step8();
		bool isShort(const int i)const;
		bool isShortSyllable(const int i)const;
		int FindRegion1()const;
    string word;
  
	private :
		
		bool FindSuffix(const string suffix)const;
		bool isInRegion(const string comp, const int region)const;
		bool isValidLi(const int i)const;
		
		
		int FindRegion2(const int region1)const;
		bool isVowel(const int i)const;
		bool ContainsVowel()const;
		bool ContainsVowelBefore(const int length)const;
		int GetSuffix(const string suffix)const;
		bool isConsonant(const int i)const;
		bool FindStringBefore(const string comp, const int i)const;
		bool EndsDouble(const int i)const;
		
};

#endif // STEM_H_INCLUDE
