// replace #include <boost/tr1/regex.hpp> with
#include <regex>
//#include <boost/tr1/regex.hpp>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <utility>

using std::cout;
using std::cerr;
using std::endl;

using std::ifstream;
using std::stringstream;

using std::pair;
using std::string;
using std::map;
using std::unordered_map;
using std::vector;

using std::advance;
using std::find_if;

// replace std::tr1 with std::
using std::regex;
using std::sregex_iterator;

using str2Int= unordered_map<string,size_t>;
using intAndWords= pair<size_t,vector<string>>;
using int2Words= map<size_t,vector<string>>;

// count the frequency of each word
str2Int wordCount(const string& text){

    //define regex to match a "word"
	regex wordReg(R"(\w+)");

	//construct regex iterator to search for matches between text.begin() and text.end()
	sregex_iterator wordItBegin(text.begin(),text.end(),wordReg);
	//default construct an end of sequence iterator
	const sregex_iterator wordItEnd;
	//declare map to hold search results
	str2Int allWords;

	//iterate through regex matches
	for (; wordItBegin != wordItEnd;++wordItBegin){
		++allWords[wordItBegin->str()];
	}

	//return matches
	return allWords;
}

// get to all frequencies the appropriate words
int2Words frequencyOfWords(str2Int& wordCount){
    //declare map which maps number to string
	int2Words freq2Words;
	//iterate through all found word-count pairs
	for ( auto wordIt: wordCount ){
		auto freqWord= wordIt.second;//get number of matches for a certain word

		//check, if word frequency already occures (f.e "this" and "that" may have each 20 matches)
		if ( freq2Words.find(freqWord) == freq2Words.end() ){
            //if matchcount not found in list, then create new entry with the current match count and
            //the single current word
			freq2Words.insert( intAndWords(freqWord,{wordIt.first} ));
		}
		else {
            //if matchcount is found in list, then add current word to the corresponding matchcount array
			freq2Words[freqWord].push_back(wordIt.first);
		}
	}
	return freq2Words;
}

string readFile(string filename){
	// open the file
	ifstream file(filename, std::ios::in);
	if ( !file ){
		cerr << "Can't open file "+ filename + "!" << endl;
		exit(EXIT_FAILURE);
	}

	// read the file into stringstream
	stringstream buffer;
	buffer << file.rdbuf();
	//return buffer of stringstream
	return buffer.str();
}

void outputFirstElements(size_t N, str2Int &allWords){
 	//secure that advance is not going to nirvana
	if (allWords.size() < N){
		cout << "Fewer than " << N << " words counted. Outputting existing..." << endl;
		N = allWords.size();
	}

	for (auto pair = allWords.begin(); N>0; ++pair, --N){
		cout << "(" << pair->first <<	": " << pair->second << ")";
	}
}

size_t getTotalNumberOfWords(str2Int &allWords){
    size_t sumWords;
    for ( auto wordIt: allWords) sumWords+= wordIt.second;
    return sumWords;
}

int main(int argc, char* argv[]){

	cout << endl;

	// get the filename
	std::string myFile;
	if ( argc == 2 ){
		myFile= {argv[1]};
	}
	else{
		cerr << "Filename missing !" << endl;
		exit(EXIT_FAILURE);
	}


	string text = readFile(myFile);
	// get the frequency of each word
	auto allWords= wordCount(text);

	cout << "The first 20 (key, value)-pairs: " << endl;
    outputFirstElements(20, allWords);

	cout << "\n\n";

	cout << "allWords[Web]: " << allWords["Web"] << endl;
	cout << "allWords[T(t)he]: " << allWords["The"]+allWords["the"] << "\n\n";

	cout << "Number of unique words: ";
	cout << allWords.size() << "\n\n";

	size_t sumWords=getTotalNumberOfWords(allWords);

	cout << "Total number of words: " << sumWords <<"\n\n";

	auto allFreq= frequencyOfWords(allWords);

	std::cout << "Number of different frequencies: " << allFreq.size() << "\n\n";

	cout << "All frequencies: ";
	for ( auto freqIt: allFreq) cout << freqIt.first << " ";
	cout << "\n\n";

	cout << "The most frequently occurring word(s): " << endl;
	auto atTheEnd= allFreq.rbegin();
	cout << atTheEnd->first << " :";
	for ( auto word: atTheEnd->second) cout << word << " ";
	cout << "\n\n";

	cout << "All word which appears more then 1000 times:" << endl;
	auto biggerIt= find_if(allFreq.begin(),allFreq.end(),
												 [](intAndWords iAndW){return iAndW.first > 1000;});
	if ( biggerIt == allFreq.end()){
		cerr << "No word appears more then 1000 times !" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		for ( auto allFreqIt= biggerIt; allFreqIt != allFreq.end(); ++allFreqIt){
			cout << allFreqIt->first << " :";
			for ( auto word: allFreqIt->second) cout << word << " ";
			cout << endl;
		}
	}
	cout << endl;
}
