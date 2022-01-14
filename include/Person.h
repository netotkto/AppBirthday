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