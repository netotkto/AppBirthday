vector<int> date;

/*
*
*   string to const gchar* srting.c_str();
*   
*   const gchar* text; 
*   const gchar* to string (string)text;
*
*/



bool verifyIsInputData(string &message_error, GtkWidget *entry, string &enterInfo, string fieldName){
    if((string)gtk_entry_get_text (GTK_ENTRY(entry)) == "") {
        message_error += "No input "+ fieldName +".\n";
        return true; // There is no input you will get message about it
    }
    else {
        enterInfo = (string)gtk_entry_get_text (GTK_ENTRY(entry));
        return false; // There is data input in entry field and program will take data in string format
    }
}

bool verifyIsInputDataValid(string &message_error, string enterInfo, string fieldName){
    int enterInfoSize=enterInfo.size();
    for(int i=0; i<enterInfoSize; i++){
        if(enterInfo[i]==' ' || enterInfo[i] == '/'){
            message_error += "Invalid input (there is \'/\' oe \' \') "+ fieldName +".\n";
            return true;
        }
    }
    return false;
}

bool isDig(char s){ 
    if(s >= '0' && s <= '9')
        return true;
    
    else return false;
}

int getNumber(string ex, int &ind) { //parse a number from string 
    double num = 0;
    while (ind < ex.size()) {
        if (isDig(ex[ind])) {
            num = num * 10 + (int)ex[ind] - 48;
        }
        else {
            ind--;
            break;
        }
        ind++;
    }
    return num;
}

string chechDateFormat(string s_date, vector<int> &date){ //s_date is birthday date in string format
    // date format must be like dd-mm-yyyy also can be d-m-yyyy there exactly must be 2 minuses, not more not less
    int str_size = s_date.size();
    int minus_count=0;
    for (int i=0; i<str_size; i++){
        if(!isDig(s_date[i])&&s_date[i]!='-'){ // if in b date entry are letters or isnt valid format
            return "date isn't valid\n";
        }
        if(s_date[i]=='-'){
            minus_count++;
        }
        if(isDig(s_date[i])){
            date.push_back(getNumber(s_date, i));
        }
    }

    if (minus_count!=2)
    {
        return "date isn't valid\n";
    }
    if (date.size() != 3 )
        return "date isn't valid\n";
    else {
        //string sdate = to_string(date[0])+"/"+to_string(date[1])+"/"+to_string(date[2]);

        time_t ttime = time(0);
        std::tm *local_time = localtime(&ttime);

        int current_year = local_time->tm_year + 1900;
        int current_month = local_time->tm_mon + 1;
        int current_day = local_time->tm_mday;

        Date d{date[0], date[1], date[2]};
        if (!d.isDayValid()) return "date isn't valid\n";
        if(date[2]>current_year) return "date isn't valid\n";
        if(date[2]<1900) return "date isn't valid\n";
        if(date[2]==current_year){
            if(date[1]>current_month) return "date isn't vali\n";
            
            else if(date[1]==current_month){
                if(date[0]>current_day) return "date isn't valid\n";

            }
        }
        return "";
    }
}

void checkInfoFile(string &message_error){
    vector<string> infoList=getInfoFromFile(message_error);
    //check if persons have same name and last name
    vector<int>numberRepeatedPersons;
    int list_size = infoList.size();
    int count_removed_person=0;
    for(int i=0; i<list_size; i++){

        for (int j=0;j<list_size; j++)
        {
            vector<string>p1=getListOfElements(infoList[i]);
            vector<string>p2=getListOfElements(infoList[j]);

            if(i!=j&&p1[0]==p2[0]&&p1[1]==p2[1]){
                infoList.erase(infoList.begin() + i);
                list_size-=1;
                count_removed_person+=1;
            }
        }
    }

    if(count_removed_person==2){
        message_error+="Person with this name won't add to database,\nbecause this person exist\n";
    }
    if(count_removed_person>2){
        message_error+="People with same names \nwill remove from database\n";
    }

    count_removed_person=0;
    std::sort(numberRepeatedPersons.begin(), numberRepeatedPersons.end()); //sort for next eraise repeat
    auto last = std::unique(numberRepeatedPersons.begin(), numberRepeatedPersons.end()); //remove repeat
    numberRepeatedPersons.erase(last, numberRepeatedPersons.end());                      //remove repeat
    list_size=numberRepeatedPersons.size();
    for(int i=0;i<list_size;i++){
        message_error+=to_string(numberRepeatedPersons[i]);
    }
    list_size=infoList.size();
    std::ofstream out;   
    string filepath="info.txt";
    out.open(filepath); //open and close file for eraise(for clean thus file)
    out << "";
    out.close();
    out.open(filepath, ofstream::app); 
    for(int i=0;i<list_size;i++){
        if (out.is_open())
        {   
            out << infoList[i] << endl;
            
        }
    }
    out.close();
}

void addPersonToBase(GtkWidget *entryName, GtkWidget *entryLastName, GtkWidget *entryBirthday){
    string name;
    string last_name;
    string birthday;
    string message_error = "";

    verifyIsInputData(message_error, textEdNameAdd, name, "name");
    verifyIsInputData(message_error, textEdLastNameAdd, last_name, "last name");
    verifyIsInputData(message_error, textEdBirthdayAdd, birthday, "birthday");

    verifyIsInputDataValid(message_error, name, "name");
    verifyIsInputDataValid(message_error, last_name, "last name");
    verifyIsInputDataValid(message_error, birthday, "birthday");
    message_error += chechDateFormat(birthday, date);
    
    string filepath = "info.txt"; // open file for writing
    if (message_error==""){
        std::ofstream out;   
        out.open(filepath, ofstream::app); 
        name=toUpperCase(name);
        last_name=toUpperCase(last_name);
        string infoLine = name+"/"+last_name+"/"+to_string(date[0])+"/"+to_string(date[1])+"/"+to_string(date[2])+"/";
        if (out.is_open())
        {   
            out << infoLine << endl;
            out.close();
        }
    }
    
    //check is in fileInfo Persons with same name and lastname
    checkInfoFile(message_error);

    gtk_label_set_text(GTK_LABEL(errorOutputAdd), message_error.c_str());

    message_error = "";

    date.clear();
}

void formAdd(){
    builderAdd = gtk_builder_new_from_file("designAdd.glade");
   
    windowAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "window"));

    g_signal_connect(windowAdd, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builderAdd, NULL);

    fixedAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "fixedAdd"));
    buttonAddFA = GTK_WIDGET(gtk_builder_get_object(builderAdd, "buttonAdd"));
    textEdNameAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "textEdName"));
    textEdLastNameAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "textEdLastName"));
    textEdBirthdayAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "textEdBirthday"));
    errorOutputAdd = GTK_WIDGET(gtk_builder_get_object(builderAdd, "errorOutput"));

    gtk_widget_show(windowAdd);
    gtk_main();
}
