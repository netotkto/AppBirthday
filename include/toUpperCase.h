//in string change first letter in all words to uppercase
void toUpperCase(string sent, string devidedBy=" "){
	vector<string> wordList = getListOfElements(sent, devidedBy);

}
/*
#include <iostream>
#include <string>
#include  <cctype>
#include <vector>

using namespace std;
vector<string> getListOfElements(string astring, string d="/"){
    size_t p = 0;
    size_t next;
    vector<string>infoList;
    while( (next = astring.find(d, p)) !=string::npos){
        infoList.push_back(astring.substr(p, next-p));
        p = next + 1;
    }
    return infoList;
}
void toUpperCase(string &sent, string devidedBy=" "){
	vector<string> wordList = getListOfElements(sent, devidedBy);
	sent="";
	int size = wordList.size();
	for(int i=0;i<=size;i++){
		wordList[i][0] =  toupper(wordList[i][0]);
		sent+=wordList[i]+devidedBy;
	}
	//int sent_size=sent.size();
	//sent=sent.substr(0, sent_size-1);
}

auto main ( ) -> int{
	string sentence;
	getline(cin, sentence);
	//sentence += " ";
	toUpperCase(sentence);
	cout<<"\n";
	cout<<sentence;

}
*/