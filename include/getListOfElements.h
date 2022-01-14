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