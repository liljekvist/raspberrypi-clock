#pragma once
#include <raylib-cpp.hpp>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <string>
#include <time.h> 
#include <deque>
#include <memory>
#include <curl/curl.h>
#include <json/json.h>

#include "event.h"
using namespace std;


class main
{   
public:
    //Functions
    
    string getCurrentDayString(){ // Returns the day represented as a string.
        int wday = getCurrentDayInt();
        string currentDay;
        switch(wday){
                case 1: 
                    currentDay = "Måndag";
                    break;
                case 2: 
                    currentDay = "Tisdag";
                    break;
                case 3: 
                    currentDay = "Onsdag";
                    break;
                case 4: 
                    currentDay = "Torsdag";
                    break;
                case 5: 
                    currentDay = "Fredag";
                    break;
                }
        return currentDay;
    }
    // Returns the day represented as a int. Range 0 to 6 where 0 is sunday and 6 is saturday.
    int getCurrentDayInt(){
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        int wday = timeinfo->tm_wday;
        return wday;
    }

    void constructDayVector(){
        int weekday = getCurrentDayInt();
        if(weekday == 1){
            Ptr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
            Ptr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
            Ptr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
            Ptr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
            Ptr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
            Ptr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
            Ptr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));

        }
        else if (weekday == 2){
            Ptr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
            Ptr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
            Ptr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
            Ptr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
            Ptr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
            Ptr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
            Ptr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
        }
        else if (weekday == 3){
            Ptr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
            Ptr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
            Ptr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
            Ptr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
            Ptr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
            Ptr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
            Ptr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
        }
        else if (weekday == 4){
            Ptr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
            Ptr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
            Ptr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
            Ptr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
            Ptr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
            Ptr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
            Ptr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
        }
        else if (weekday == 5){
            Ptr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
            Ptr->push_back(Event("Alla grupper ska ha Review", 9, 10, 00, 00, "9:00", "10:00"));
            Ptr->push_back(Event("Lunch på resturang", 12, 13, 00, 00, "12:00", "13:00"));
            Ptr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
            Ptr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
        }
        else {
            cout << "ERROR: Day not valid or is a weekend!";
        }
    }

    void drawEventText(){
        

        textColor.DrawRectangleLines(0, 0, 1000, 250);
        textColor.DrawRectangleLines(0, 250, 1000, 250);
        textColor.DrawRectangleLines(0, 500, 1000, 250);
        textColor.DrawRectangleLines(0, 750, 1000, 250);


        if(Ptr->size() > 0 && (*Ptr)[0].endHour <= timeinfo->tm_hour){
            //Hour is right
            if (((*Ptr)[0].endMinute <= timeinfo->tm_min) && ((*Ptr)[0].endHour <= timeinfo->tm_hour) || (*Ptr)[0].endHour < timeinfo->tm_hour )
            {
                cout << "Removed Event " <<  (*Ptr)[0].title << endl;
                (*Ptr).pop_front();
            }
        }

        string timesStr;
        if((*Ptr).size() > 0){
            timesStr = (*Ptr)[0].displayTimeStart + " - " + (*Ptr)[0].displayTimeEnd;
            if((*Ptr)[0].startMinute <= timeinfo->tm_min && ((*Ptr)[0].startHour <= timeinfo->tm_hour) || (*Ptr)[0].startHour < timeinfo->tm_hour){
                textColorRed.DrawText((*Ptr)[0].title, 10 , 10, 70);
                textColorRed.DrawText(timesStr, 10, 100, 40);
            }
            else {
                textColor.DrawText((*Ptr)[0].title, 10 , 10, 70);
                textColor.DrawText(timesStr, 10, 100, 40);
            }
        }

        if((*Ptr).size() > 1){   
            timesStr = (*Ptr)[1].displayTimeStart + " - " + (*Ptr)[1].displayTimeEnd;
            textColor.DrawText((*Ptr)[1].title, 10, (10 + 250), 70);
            textColor.DrawText(timesStr, 10, (100 + 250), 40);
        }

        if((*Ptr).size() > 2){
            timesStr = (*Ptr)[2].displayTimeStart + " - " + (*Ptr)[2].displayTimeEnd;
            textColor.DrawText((*Ptr)[2].title, 10, (10 + 500), 70);
            textColor.DrawText(timesStr, 10, (100 + 500), 40);
        }

        if((*Ptr).size() > 3){
            timesStr = (*Ptr)[3].displayTimeStart + " - " + (*Ptr)[3].displayTimeEnd;
            textColor.DrawText((*Ptr)[3].title, 10, (10 + 750), 70);
            textColor.DrawText(timesStr, 10, (100 + 750), 40);
        }
    }

    //Variables
    string urlToImage = "";
    shared_ptr<deque<Event>> Ptr = make_shared<deque<Event>>();
    shared_ptr<Sound> effectPtr = make_shared<Sound>();
    raylib::Color textColor = raylib::Color(LIGHTGRAY);
    raylib::Color textColorRed = raylib::Color(RED);
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
};
