#ifndef EXCEPTION_H_INCLUDE
#define EXCEPTION_H_INCLUDE

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cstring>
using std::strtok;
using std::istream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::unordered_map;
class Exception{
  public:
    bool read(istream& istr);
    string getWord(const string& str)const;
  private:
    unordered_map<string, string> words;
  
};

#endif // EXCEPTION_H_INCLUDE