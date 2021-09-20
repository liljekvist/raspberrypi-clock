#include <raylib-cpp.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <time.h> 
#include <vector>
#include <memory>
#include "defines.h"



class Event
{
public:
    //Defualt mobojumbo
    Event();
    Event(std::string _title, int _startHour, int _endHour, int _startMinute, int _endMinute, bool _days[7]);
    Event(Event &&) = default;
    Event(const Event &) = default;
    Event &operator=(Event &&) = default;
    Event &operator=(const Event &) = default;
    ~Event();
    //Variables

    std::string title = "";
    int startHour = 0;
    int endHour = 0;
    int startMinute = 0;
    int endMinute = 0;
    bool days[7] = {false, false, false, false, false, false, false}; //Days of occurence. Index 0 is monday.
};

Event::Event(std::string _title, int _startHour, int _endHour, int _startMinute, int _endMinute, bool _days[7])
:
title(_title),
startHour(_startHour),
endHour(_endHour),
startMinute(_startMinute),
endMinute(_endMinute),
days{_days}
{
}


Event::Event()
{
}

Event::~Event()
{
}