#include <string>
using namespace std;


class Event
{
public:
    //Defualt mobojumbo
    Event();
    Event(std::string _title, int _startHour, int _endHour, int _startMinute, int _endMinute, string _displayTimeStart, string _displayTimeEnd);
    Event(Event &&) = default;
    Event(const Event &) = default;
    Event &operator=(Event &&) = default;
    Event &operator=(const Event &) = default;
    ~Event();
    //Variables

    std::string title = "";
    string displayTimeStart = "";
    string displayTimeEnd = "";
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    bool hasPlayedSoundStart = false;
    bool hasPlayedSoundEnd = false;
};



Event::Event(std::string _title, int _startHour, int _endHour, int _startMinute, int _endMinute, string _displayTimeStart, string _displayTimeEnd)
:
title(_title),
startHour(_startHour),
endHour(_endHour),
startMinute(_startMinute),
endMinute(_endMinute),
displayTimeStart(_displayTimeStart),
displayTimeEnd(_displayTimeEnd)
{
}
Event::Event()
{
}

Event::~Event()
{
}
