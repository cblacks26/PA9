#include <Compare.h>

Compare::Compare() : documents(0){}

bool Compare::addCompare(const string& str, const Exception& ex){
	Count comp(str,ex);
	ifstream istr(str);
	if(comp.Read(istr)==false) return false;
  comp.StemWords();
	counts.push_back(comp);
  documents++;
	for(auto& it: comp.getStemWordCountMap()){
		words.insert({it.first,1});
	}
	return true;
}

bool Compare::addCount(const string& str, const Exception& ex){
	Count count(str,ex);
	ifstream istr(str);
	if(count.Read(istr)==false) return false;
  count.StemWords();
	counts.push_back(count);
  documents++;
	for(auto& it: words){
		if(count.getStemCountOfWord(it.first)){
			it.second++;
		}
	}
	return true;
}

void Compare::computeIDF(){
	for(std::pair<string, int> element:words){
		double tmp = documents/words.find(element.first)->second;
		double res = log(tmp);
		idf.insert({element.first, res});
	}
}

double Compare::computeTFIDF(const string& str, const Count& count)const{
  int n = count.getStemCountOfWord(str);
	if(n>0){
		double res = idf.find(str)->second * n;
		return res;
	}
	return 0;
}

void Compare::computeCompareTFIDF(){
	for(std::pair<string, int> element:words){
		comp.insert({element.first,computeTFIDF(element.first,counts[0])});
	}
}

double Compare::compareDocuments(const Count& count)const{
	double sim = 0.0;
	unordered_map<string, int>::const_iterator it = words.cbegin();
	for(;it!=words.cend();++it){
		double temp = computeTFIDF(it->first,count);
		sim += comp.find(it->first)->second*temp;
	}
	return sim;
}

string Compare::getDocumentMatch(const double& lower, const double& upper){
	if(counts.size()<1) return "";
	computeIDF();
	computeCompareTFIDF();
	double score = -1;
	int index = -1;
	for(int i = 1;i<static_cast<int>(counts.size());i++){
		double rl = counts[i].getReadingLevel();
		if(rl>=lower&&rl<=upper){
		  double temp = compareDocuments(counts[i]);
		  if(temp > score){
			score = temp;
			index = i;
		  }
		}
	}
  if(index==-1) return "";
	return counts[index].getDocumentName();
}
