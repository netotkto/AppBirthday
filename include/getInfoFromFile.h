vector<string> getInfoFromFile(string &message_error){
    vector<string> infoList;
    string filepath = "info.txt";
    ifstream file_to_read;
    file_to_read.open(filepath);
    if(!file_to_read.is_open()){
        message_error+="There is error opening info.txt\n";
    }
    else{
        //ok
        string str;
        while(!file_to_read.eof()){
            file_to_read >> str;
            infoList.push_back(str);
        }

    }
    return infoList;
}