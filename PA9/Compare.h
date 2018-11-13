#ifndef COMPARE_H_INCLUDE
#define COMPARE_H_INCLUDE

#include <math.h>
#include <Count.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using std::log10;
using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;
using std::ifstream;

class Compare{
  public:
    Compare();
		bool addCount(const string& str, const Exception& ex);
		bool addCompare(const string& str, const Exception& ex);
		void computeIDF();
    double computeTFIDF(const string& str, const Count& count)const;
		void computeCompareTFIDF();
		double compareDocuments(const Count& count)const;
		string getDocumentMatch(const double& lower, const double& upper);
  private:
		int documents;
    	vector<Count> counts;
		unordered_map<string, int> words;
		unordered_map<string, double> idf;
		unordered_map<string, double> comp;
};

#endif // COMPARE_H_INCLUDE
