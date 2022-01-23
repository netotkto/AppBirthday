string toUpperCase(string word){
    char symb = toupper(word[0]);
    word[0]=symb;
    int wordSize=word.size();
    for(int j = 1; j<=wordSize;j++){
        char symb = tolower(word[j]);
        word[j]=symb;
    }
    return word;
}