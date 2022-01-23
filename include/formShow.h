bool verifyCorectForm(GtkWidget *entryFullName, string &message_error){
    string fullName=(string)gtk_entry_get_text(GTK_ENTRY(entryFullName));
    int size=fullName.size();
    int count=0;
    for(int i=0; i<size; i++){
        if(fullName[i]==' '){
            count++;
        }
    }
    if(count!=1){
        message_error+="There is incorrect input full name";
        return false;
    }
    else{
        return true;
    }
}

vector<string> getElementsOfFullName(string fullName){//0-name; 1-last name
    fullName+=" ";
    vector<string>fullNameList=getListOfElements(fullName, " ");
    string name=fullNameList[0];
    string last_name=fullNameList[1]; 
    fullNameList[0]=toUpperCase(name);
    fullNameList[1]=toUpperCase(last_name);
    return fullNameList;
}

bool findPersonFromList(string name, string last_name, string &message_error, Person &p){
    vector<string> infoList=getInfoFromFile(message_error);
    int infoSize=infoList.size();
    for(int i=0; i<infoSize; i++){
        vector<string> person=getListOfElements(infoList[i]);
        if(name==person[0] && last_name==person[1]){
            int day=stoi(person[2]); int month=stoi(person[3]); int year=stoi(person[4]);
            p.name=person[0];
            p.last_name=person[1];
            p.day=day;
            p.month=month;
            p.year=year;
            return true;
        }
    }
    message_error+="There is no person with that name in the database";
    return false;
}

void showPersonsInfo(GtkWidget *entryFullName){
    string message_error="";
    string fullName=(string)gtk_entry_get_text(GTK_ENTRY(entryFullName));
    if(verifyCorectForm(entryFullName, message_error)){
        vector<string>fullNameList=getElementsOfFullName(fullName);
        Person p;
        if(findPersonFromList(fullNameList[0], fullNameList[1], message_error, p)){
            fullName=p.name+" "+p.last_name;                            // for output
            Date personBirthday {p.day, p.month, p.year};
            vector<int> ageVector=personBirthday.getAge();
            string age="Age: "+to_string(ageVector[2])+" years old | "+to_string(ageVector[1])+" months | "+to_string(ageVector[0])+" days";
            gtk_label_set_text(GTK_LABEL(labelBirthdayDate), personBirthday.getFullBirthday().c_str());
            gtk_label_set_text(GTK_LABEL(labelFullName), fullName.c_str());
            gtk_label_set_text(GTK_LABEL(labelNextBirth), personBirthday.getWhenNextBirthdayWill().c_str());
            gtk_label_set_text(GTK_LABEL(labelAge), age.c_str());
            gtk_label_set_text(GTK_LABEL(labelFullAge), personBirthday.getFullAge().c_str());
        }

    }
    if(message_error!=""){
        gtk_label_set_text(GTK_LABEL(errorOutputShow), message_error.c_str());
    }
    
}



void formShow(){
    builderShow = gtk_builder_new_from_file("designShow.glade");
   
    windowShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "window"));

    g_signal_connect(windowShow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builderShow, NULL);

    fixedShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "fixed"));
    textEdFullNameShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "textEdFullName"));
    errorOutputShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "errorOutput"));
    labelBirthdayDate = GTK_WIDGET(gtk_builder_get_object(builderShow, "birthdayDate"));
    labelFullName = GTK_WIDGET(gtk_builder_get_object(builderShow, "fullName"));
    labelNextBirth = GTK_WIDGET(gtk_builder_get_object(builderShow, "nextBirthday"));
    labelAge = GTK_WIDGET(gtk_builder_get_object(builderShow, "age"));
    labelFullAge = GTK_WIDGET(gtk_builder_get_object(builderShow, "fullAge"));
    buttonAddFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonAdd"));
    buttonShowFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonShow"));

    gtk_widget_show(windowShow);
    gtk_main();
}

