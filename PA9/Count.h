#ifndef COUNT_H_INCLUDE
#define COUNT_H_INCLUDE

#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<vector>
#include<algorithm>
#include<ctype.h>
#include<Stem.h>
#include<Exception.h>
#include <unordered_map>
using std::istream;
using std::ostream;
using std::string;
using std::exception;
using std::vector;
using std::sort;
using std::cout;
using std::endl;
using std::cerr;
using std::isupper;
using std::unordered_map;

class Count{
	public :
		Count(const string name);
    Count(const string name, const Exception& ex);
		// Read the file and count the numbers
		bool Read(istream& istr);
		void StemWords();
		int getCountOfWord(const string& str)const;
    int getStemCountOfWord(const string& str) const;
    unordered_map<string, int> getStemWordCountMap()const;
		double getReadingLevel()const;
		string getDocumentName()const;
	private :
	
		bool startSentence;
		
		double letterAmount;
		
		double wordAmount;
		
		double sentenceAmount;
		
		double readingLevel;
		
		string docName;
		// unordered map for word counts
		unordered_map<string, int> wordCount;
    unordered_map<string, int> stemWordCount;
    // exception class to handle exceptions for stemmer
    Exception ex;
		// Evaluate stringstream
		void Eval(string& str);
		// Handles a comma
		void HandleComma(const string& str, int& i);
		// Handles a period
		void HandlePeriod(const string& str, int& i);
		// seperates string and push 1st and calls eval on the 2nd
		void Seperate(const string& str, int& i);
		// adds + if should be capital
		string AddCap(const string& str);
    bool isStemable(const string& str)const;
		bool isEndString(const string& str)const;
		void addWord(const string& str);
    inline bool isPunct(const char& c)const;
		bool isWord(const string& str)const;
};

#endif // COUNT_H_INCLUDE