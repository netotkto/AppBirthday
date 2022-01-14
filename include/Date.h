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