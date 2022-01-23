struct Date{
    const vector<int>leap_year = {31,29,31,30,31,30,31,31,30,31,30,31};
    const vector<int>normal_year = {31,28,31,30,31,30,31,31,30,31,30,31};
    const vector<string> months = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
    const vector<string> days_of_the_week = {"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};

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
    string getFullBirthday(){
        string fullBirth="";
        fullBirth+=to_string(day);
        fullBirth+=" ";
        fullBirth+=months[month-1];
        fullBirth+=" ";
        fullBirth+=to_string(year);
        return fullBirth;
    }
    vector<int> getCurrentTime(){
        time_t ttime = time(0);
        std::tm *local_time = localtime(&ttime);

        int current_year = local_time->tm_year + 1900;
        int current_month = local_time->tm_mon + 1;
        int current_day = local_time->tm_mday;
        vector<int>current_time={current_day, current_month, current_year};
        return current_time;
    }
    string getDayNextBirthday(){//a day of the week
        vector<int>current_time=getCurrentTime();
        int yearCount=current_time[2]-2020;
        int dayCount=day;
        int temp = yearCount;
        int leap_yearCount=0;
        while(temp-4>=0){
            leap_yearCount++;
            temp-=4;
        }
        yearCount-=leap_yearCount;
        dayCount+=yearCount*365;
        dayCount+=leap_yearCount*366;
        for(int i=0; i<month-1; i++){
            if(current_time[2]%4==0){
                dayCount+=leap_year[i];
            }
            else{
                dayCount+=normal_year[i];
            }
        }
        if(day==current_time[0] && month==current_time[1]){
            if((current_time[2]+1)%4==0){
                dayCount+=366;
            }
            else{
                dayCount+=365;
            }
        }
        if(dayCount%7==0){
            return "Wednesday";
        }
        else{
            return days_of_the_week[dayCount%7-1];
        }
    }
    string getWhenNextBirthdayWill(){
        vector<int> current_time=getCurrentTime();
        string nextBirth="Next Birthday: On ";
        nextBirth+=getDayNextBirthday();
        int dayCount;
        int monthCount;
        if(current_time[1]<month){
            if(current_time[0]<day){
                dayCount=day-current_time[0];
                monthCount=month-current_time[1];
            }
            else if(current_time[0]>day){
                int monthInd=month-2; //month before bithday month fe: october - it will be september;
                monthCount=month-current_time[1]-1;
                if(current_time[2]%4==0){
                    dayCount = leap_year[monthInd]-day-1;
                }
                else{
                    dayCount = normal_year[monthInd]-day-1;
                }
                dayCount+=day;
            }
            else{
                dayCount=0;
                monthCount=month-current_time[1];
            }
            
        }
        else if(current_time[1]>month){
            if(current_time[0]<day){
                dayCount=day-current_time[0];
                monthCount=12-current_time[1];
                monthCount+=month;
            }
            else if(current_time[0]>day){
                int monthInd=month-2; //month before bithday month fe: october - it will be september;
                monthCount=11-current_time[1];
                if(current_time[2]%4==0){
                    dayCount = leap_year[monthInd]-day-1;
                }
                else{
                    dayCount = normal_year[monthInd]-day-1;
                }
                dayCount+=day;
            }
            else{
                dayCount=0;
                monthCount=12-current_time[1];
                monthCount+=month;
            }
        }   
        else{
            if(current_time[0]<day){
                monthCount=0;
                dayCount=day-current_time[0];

            }
            else if(current_time[0]>day){
                monthCount=11;
                int monthInd=month-2; //month before bithday month fe: october - it will be september;
                if(current_time[2]%4==0){
                    dayCount = leap_year[monthInd]-day;
                }
                else{
                    dayCount = normal_year[monthInd]-day;
                }
                dayCount+=day;
            }
            else{
                nextBirth+=" in 1 year. Happy Birthday<3";
                return nextBirth;
            }
        }
        nextBirth=nextBirth+" in "+to_string(monthCount)+" months "+to_string(dayCount)+" days";
        return nextBirth;
    }

    vector<int> getAge(){ //  years old | months | days  
        vector<int> current_time=getCurrentTime();
        int yearsCount;
        int monthsCount;
        int daysCount;
        int monthInd=month-1;
        if(current_time[1]<month){
            yearsCount=current_time[2]-year-1;
            if(current_time[0]<day){
                monthsCount=11-month+current_time[1];
                if(current_time[2]%4==0){
                    daysCount = leap_year[monthInd]-day;
                }
                else{
                    daysCount = normal_year[monthInd]-day;
                }
                daysCount+=current_time[0];
            }
            else if(current_time[0]>day){
                monthsCount=12-month+current_time[1];
                daysCount=current_time[0]-day;
            }
            else{
                daysCount=0;
                monthsCount=12-month+current_time[1];
            }       
        }
        else if(current_time[1]>month){
            yearsCount=current_time[2]-year;
            if(current_time[0]<day){
                monthsCount=current_time[1]-month-1;
                if(current_time[2]%4==0){
                    daysCount = leap_year[monthInd]-day;
                }
                else{
                    daysCount = normal_year[monthInd]-day;
                }
                daysCount+=current_time[0];
            }
            else if(current_time[0]>day){
                daysCount=current_time[0]-day;
                monthsCount=current_time[1]-month;
            }
            else{
                daysCount=0;
                monthsCount=current_time[1]-month;
            }
        }   
        else{
            if(current_time[0]<day){
                yearsCount=current_time[2]-year-1;
                monthsCount=11;
                if(current_time[2]%4==0){
                    daysCount = leap_year[monthInd]-(day-current_time[0]);
                }
                else{
                    daysCount = normal_year[monthInd]-(day-current_time[0]);
                }
            }
            else if(current_time[0]>day){
                yearsCount=current_time[2]-year;
                monthsCount=0;
                daysCount=current_time[0]-day;
            }
            else{
                yearsCount=current_time[2]-year;
                monthsCount=0;
                daysCount=0;
            }
        }
        vector<int> age={daysCount, monthsCount, yearsCount};
        return age;
    }

    string getFullAge(){
        vector<int> age=getAge();
        vector<int> current_time=getCurrentTime();
        string fullAge="Full age: ";
        int yearsCount=age[2];
        int monthsCount=age[1]+12*yearsCount;
        int daysCount=age[0];
        int weeksCount;
        int leap_yearCount=0;
        int ind=0;
        int indYear=year;
        if(year%4==0 && month<2){
            while(ind<yearsCount){
                if(indYear%4==0){
                    leap_yearCount++;
                }
                ind++;
                indYear++;
            }
        }
        else{
            indYear+=1;
            while(ind<yearsCount){
                if(indYear%4==0){
                    leap_yearCount++;
                }
                indYear++;
                ind++;
            }
        }
        daysCount+=leap_yearCount*366;
        daysCount+=(yearsCount-leap_yearCount)*365;
        if(12-month>=age[1]){
            if((current_time[2]-1)%4==0){
                for(int i=month; i<12; i++){
                    daysCount+=leap_year[i];
                }
            }
            else{
                for(int i=month; i<12; i++){
                    daysCount+=normal_year[i];
                }
            }
            if(current_time[2]%4==0){
                for(int i=0; i<current_time[1]-1; i++){
                    daysCount+=leap_year[i];
                }
            }
            else{
                for(int i=0; i<current_time[1]-1; i++){
                    daysCount+=normal_year[i];
                }
            }
    
        }
        else{
            if(current_time[1]%4==0){
                for(int i=month; i<month+age[1]; i++){
                    daysCount+=leap_year[i];
                }
            }
            else{
                for(int i=month; i<month+age[1]; i++){
                    daysCount+=normal_year[i];
                }
            }
        }
        weeksCount=daysCount/7;
        fullAge=fullAge+to_string(leap_yearCount)+" y.o. | "+to_string(monthsCount)+" m. | "+to_string(weeksCount)+" w. | "+to_string(daysCount)+" d.";
        return fullAge;
    }


};