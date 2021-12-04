#include <iostream>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <string>
#include <vector>
#include <ctime>
#include <fstream> // for write to file
#include <algorithm> //sort and unique
//#include "Main.h"
//#include <gtkmm.h>
//global varriables

using namespace std;
//AddForm
GtkWidget  *windowAdd;
GtkWidget  *fixedAdd;
GtkWidget  *errorOutputAdd;
GtkWidget  *textEdNameAdd;
GtkWidget  *textEdLastNameAdd;
GtkWidget  *textEdBirthdayAdd;
GtkWidget  *buttonAddFA;
GtkWidget  *buttonShowFA;
GtkBuilder *builderAdd;
//ShowForm
GtkWidget  *comboShow;
GtkWidget  *windowShow;
GtkWidget  *fixedShow;
GtkWidget  *buttonAddFS;
GtkWidget  *buttonShowFS;
GtkBuilder *builderShow;



vector<int> date;

/*
*
*   string to const gchar* srting.c_str();
*   
*   const gchar* text; 
*   const gchar* to string (string)text;
*
*/

struct Person{
    string name;
    string last_name;
    int day;
    int month;
    int year;
    Person(string p_name, string p_last_name, int iday, int imonth, int iyear){
        name=p_name;
        last_name=p_last_name;
        day=iday;
        month=imonth;
        year=iyear;
    }
};

struct Date{
    const vector<int>leap_year = {31,29,31,30,31,30,31,31,30,31,30,31};
    const vector<int>normal_year = {31,28,31,30,31,30,31,31,30,31,30,31};
    int day;
    int month;
    int year;

    Date(int iday, int imonth, int iyear){
        day = iday;
        month = imonth;
        year = iyear;
    }
    int getDayByMonth(){
        if(year%4==0){
            return leap_year[month-1];
        }
        else return normal_year[month-1];
    }
    bool isDayValid(){
        if(day<=getDayByMonth()) return true;
        else return false;
    }
};

#define VNAME(var) #var; //macros get varriable name

bool verifyIsInputData(string &message_error, GtkWidget *entry, string &enterInfo, string fieldName){
    if((string)gtk_entry_get_text (GTK_ENTRY(entry)) == "") {
        message_error += "No input "+ fieldName +".\n";
        return true;
    }
    else {
        enterInfo = (string)gtk_entry_get_text (GTK_ENTRY(entry));
        return false;
    }
}

bool isDig(char s){
    if(s >= '0' && s <= '9')
        return true;
    
    else return false;
}

int getNumber(string ex, int &ind) {
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

string chechDateFormat(string s_date, vector<int> &date){

    int str_size = s_date.size();
    string rofl="";
    int minus_count=0;
    for (int i=0; i<str_size; i++){
        if(!isDig(s_date[i])&&s_date[i]!='-'){
            return "date isn't valid+_";
        }
        if(s_date[i]=='-'){
            minus_count++;
        }
        if(isDig(s_date[i])){
            date.push_back(getNumber(s_date, i));
        }
    }

    time_t ttime = time(0);
    std::tm *local_time = localtime(&ttime);
    

    int current_year = local_time->tm_year + 1900;
    int current_month = local_time->tm_mon + 1;
    int current_day = local_time->tm_mday;

    if (minus_count!=2)
    {
        return "date isn't valid--";
    }
    if (date.size() != 3 )
        return "Error";
    else {
        string sdate = to_string(date[0])+"/"+to_string(date[1])+"/"+to_string(date[2]);
        //const char date1;
        //date1 = sdate.c_str();//to_string(date[0])+"/"+to_string(date[1])+"/"+to_string(date[2]);
        struct tm tm;
        Date d{date[0], date[1], date[2]};
        if (!strptime(sdate.c_str(), "%d/%m/%Y", &tm)||!d.isDayValid()) return "date isn't valid\n";
        if(date[2]>current_year) return "date isn't valid";
        if(date[2]<1900) return "date isn't valid";
        if(date[2]==current_year){
            if(date[1]>current_month) return "date isn't valid";
            
            else if(date[1]==current_month){
                if(date[0]>current_day) return "date isn't valid";

            }
        }
        
        /*if(std::mktime(&tmdate)){
            return "Error";
        }*/
        //return to_string(d.is_not_a_date());
        /*if(date[0]>31||date[1]>12||date[2]>current_year){
            return "Error";
        }
        if(date[2]==current_year){
            if(date[1]>current_month){
                return "Error";
            }
            if(date[1]==current_month){
                if(date[0]>current_day){
                    return "Error";
                }
                else return "ok";
            }
        }*/
        return "";
    }
}

vector<string> getListOfElements(string personInfo){
    size_t p = 0;
    size_t next;
    string d = "/";
    vector<string>personInfoList;
    while( (next = personInfo.find(d, p)) !=string::npos){
        personInfoList.push_back(personInfo.substr(p, next-p));
        p = next + 1;
    }
    return personInfoList;
}

void checkInfoFile(string &message_error){
    vector<string> infoList;
    string filepath = "info.txt";
    ifstream file_to_read;
    file_to_read.open(filepath);
    if(!file_to_read.is_open()){
        message_error+="Ошибка в открытии файла";
    }
    else{
        //ok
        string str;
        while(!file_to_read.eof()){
            file_to_read >> str;
            infoList.push_back(str);
        }

    }
    //check if persons have same name and last name
    vector<int>numberRepeatedPersons;
    int list_size = infoList.size();
    int count_removed_person=0;
    for(int i=0; i<list_size; i++){
        //message_error+=infoList[i]+" ";
        for (int j=0;j<list_size; j++)
        {
            vector<string>p1=getListOfElements(infoList[i]);
            vector<string>p2=getListOfElements(infoList[j]);
            //message_error+=p2[0];
            if(i!=j&&p1[0]==p2[0]&&p1[1]==p2[1]){
                //message_error+="Вы насоздовали людей с одинаковыми именами и фамилиями, оди будут удалены\n";
                infoList.erase(infoList.begin() + i);
                list_size-=1;
                count_removed_person+=1;
            }
        }
    }

    if(count_removed_person==2){
        message_error+="Person whis this name won't add to database, because this person exist\n";
    }
    if(count_removed_person>2){
        message_error+="People with same names will remove from database\n";
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

void outputMessageError(GtkWidget *entryName, GtkWidget *entryLastName, GtkWidget *entryBirthday){
    string name;
    string last_name;
    string birthday;
    string message_error = "";

    verifyIsInputData(message_error, textEdNameAdd, name, "name");
    verifyIsInputData(message_error, textEdLastNameAdd, last_name, "last name");
    verifyIsInputData(message_error, textEdBirthdayAdd, birthday, "birthday");
    message_error += chechDateFormat(birthday, date);
    
    string filepath = "info.txt"; // окрываем файл для записи
    if (message_error==""){
        Person p{name, last_name, date[0], date[1], date[2]};
        std::ofstream out;   
        out.open(filepath, ofstream::app); 
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



void formShow(){
    builderShow = gtk_builder_new_from_file("designShow.glade");
   
    windowShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "window"));

    g_signal_connect(windowShow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builderShow, NULL);

    fixedShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "fixed"));
    buttonAddFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonAdd"));
    buttonShowFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonShow"));

    gtk_widget_show(windowShow);
    gtk_main();
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
const gchar* gpa_receive_key_dialog_get_id (GtkWidget *entry)
{
  return gtk_entry_get_text (GTK_ENTRY(entry));
}


//FormShow
extern "C" void on_buttonShowFS_clicked(GtkButton *button, gpointer data){

}

extern "C" void on_buttonAddFS_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide_on_delete(windowShow);
    formAdd();
}

//FormAdd
extern "C" void on_buttonShowFA_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide_on_delete(windowAdd);
    formShow();
}
extern "C" void on_buttonAddFA_clicked(GtkButton *button, gpointer data)
{
    //const gchar* name = gpa_receive_key_dialog_get_id(textEdName);
    outputMessageError(textEdLastNameAdd, textEdLastNameAdd, textEdBirthdayAdd);
}
int main (int argc, char *argv[]){

    //FormShow
    gtk_init( & argc, & argv );
    formShow();

    return EXIT_SUCCESS;

}
