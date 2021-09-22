#include "main.hpp"


int main() {
    //void eventDraw(std::vector<Event> input);

    int calculateTextPositionX(int fontWidth, int screenWidth);
    deque<Event> constructDayVector(deque<Event> day, int weekday);
    void LogCustom(int msgType, const char *text, va_list args);
    deque<Event> drawEventText(deque<Event> day, tm* timeinfo);
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;
    SetTraceLogCallback(LogCustom);
    

    raylib::Color whiteColor(LIGHTGRAY);
    raylib::Color blackColor(BLACK);
    raylib::Window w(screenWidth, screenHeight, "PogClock");
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    int wday = timeinfo->tm_wday;
    string currentDay;
    deque<Event> day;
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
    
    SetTargetFPS(0);
    day = constructDayVector(day, wday);

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        if (IsCursorOnScreen()){
            DisableCursor();
            HideCursor();
        }
        if (!IsWindowFullscreen())
        {
             // if we are not in fullscreen set fullscreen
            ToggleFullscreen();
        }

        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%T",timeinfo);
        
        // Draw
        BeginDrawing();
            //Clear background
            blackColor.ClearBackground();

            //Draw events
            day = drawEventText(day,timeinfo);
            //Draw clock and borderline
            whiteColor.DrawText(buffer, 1030, 0, 200);
            whiteColor.DrawText(currentDay, 1030, 250, 100);
            whiteColor.DrawLine(1000,0,1001,1080);
            
            //Draw "Made by" text
            whiteColor.DrawText("Made with <3 by liljekvist", 10, 20 + 1000, 40);
        EndDrawing();
    }

    return 0;
}

deque<Event> constructDayVector(deque<Event> day, int weekday){
    if(weekday == 1){
        day.push_back(Event("Dag Börjar", 9, 9, 00, 00, "9:00", "9:00"));
        day.push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        day.push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        day.push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        day.push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        day.push_back(Event("Dag Slut", 16, 16, 00, 00, "16:00", "16:00"));

    }
    else if (weekday == 2){
        day.push_back(Event("Dag Börjar", 9, 9, 00, 00, "9:00", "9:00"));
        day.push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        day.push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        day.push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        day.push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        day.push_back(Event("Dag Slut", 16, 16, 00, 00, "16:00", "16:00"));

    }
    else if (weekday == 3){
        day.push_back(Event("Dag Börjar", 9, 9, 00, 00, "9:00", "9:00"));
        day.push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        day.push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        day.push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        day.push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        day.push_back(Event("Dag Slut", 16, 16, 00, 00, "16:00", "16:00"));
    }
    else if (weekday == 4){
        day.push_back(Event("Dag Börjar", 9, 9, 00, 00, "9:00", "9:00"));
        day.push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        day.push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        day.push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        day.push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        day.push_back(Event("Dag Slut", 16, 16, 00, 00, "16:00", "16:00"));

    }
    else if (weekday == 5){
        //TBD
    }
    else {
        cout << "ERROR: Day not valid!";
    }
    return day;
}

deque<Event> drawEventText(deque<Event> day, tm* timeinfo){
    raylib::Color textColor(LIGHTGRAY);
    Sound effect = LoadSound("sound/siren.wav");
    

    textColor.DrawRectangleLines(0, 0, 1000, 250);
    textColor.DrawRectangleLines(0, 250, 1000, 250);
    textColor.DrawRectangleLines(0, 500, 1000, 250);
    textColor.DrawRectangleLines(0, 750, 1000, 250);

    if((day[0].startHour == timeinfo->tm_hour) && (day[0].startMinute == timeinfo->tm_min)){
        PlaySound(effect);
    }

    if(day[0].endHour <= timeinfo->tm_hour){
        //Hour is right
        if ((day[0].endMinute <= timeinfo->tm_min) && (day[0].endHour <= timeinfo->tm_hour) || day[0].endHour < timeinfo->tm_hour )
        {
            cout << "Removed Event " <<  day[0].title << endl;
            day.pop_front();
        }
    }

    string timesStr;
    if(day.size() > 0){
        timesStr = day[0].displayTimeStart + " - " + day[0].displayTimeEnd;
        textColor.DrawText(day[0].title, 10 , 10, 70);
        textColor.DrawText(timesStr, 10, 100, 40);
    }

    if(day.size() > 1){   
        timesStr = day[1].displayTimeStart + " - " + day[1].displayTimeEnd;
        textColor.DrawText(day[1].title, 10, (10 + 250), 70);
        textColor.DrawText(timesStr, 10, (100 + 250), 40);
    }

    if(day.size() > 2){
        timesStr = day[2].displayTimeStart + " - " + day[2].displayTimeEnd;
        textColor.DrawText(day[2].title, 10, (10 + 500), 70);
        textColor.DrawText(timesStr, 10, (100 + 250), 40);
    }

    if(day.size() > 3){
        timesStr = day[3].displayTimeStart + " - " + day[3].displayTimeEnd;
        textColor.DrawText(day[3].title, 10, (10 + 750), 70);
        textColor.DrawText(timesStr, 10, (100 + 250), 40);
    }

    return day;
}

// Custom logging funtion
void LogCustom(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}