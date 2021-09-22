#include "main.hpp"

int calculateTextPositionX(int fontWidth, int screenWidth);
void constructDayVector(shared_ptr<deque<Event>> dayPtr, int weekday);
void LogCustom(int msgType, const char *text, va_list args);
void drawEventText(shared_ptr<deque<Event>> dayPtr, tm* timeinfo);

int main() {
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;
    SetTraceLogCallback(LogCustom);
    shared_ptr<deque<Event>> Ptr(new deque<Event>);
    
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
        InitAudioDevice(); 
        Sound effect = LoadSound("sound/siren.wav");


    SetTargetFPS(0);
    constructDayVector(Ptr, wday);

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
        if((((*Ptr)[0].startHour == timeinfo->tm_hour) && ((*Ptr)[0].startMinute == timeinfo->tm_min) || ((*Ptr)[0].endHour == timeinfo->tm_hour) && ((*Ptr)[0].endMinute == timeinfo->tm_min) ) && ((*Ptr)[0].hasPlayedSound == false)){
            (*Ptr)[0].hasPlayedSound = true;
                PlaySound(effect); 
        }

        // Draw
        BeginDrawing();
            //Clear background
            blackColor.ClearBackground();

            //Draw events
            drawEventText(Ptr,timeinfo);
            //Draw clock and borderline
            whiteColor.DrawText(buffer, 1030, 0, 200);
            whiteColor.DrawText(currentDay, 1030, 250, 100);
            whiteColor.DrawLine(1000,0,1001,1080);
            
            //Draw "Made by" text
            whiteColor.DrawText("Made with <3 by liljekvist", 10, 20 + 1000, 40);
        EndDrawing();
    }
    CloseAudioDevice();
    return 0;
}

void constructDayVector(shared_ptr<deque<Event>> dayPtr, int weekday){
    if(weekday == 1){
        dayPtr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
        dayPtr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        dayPtr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        dayPtr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        dayPtr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        dayPtr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
        dayPtr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));

    }
    else if (weekday == 2){
        dayPtr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
        dayPtr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        dayPtr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        dayPtr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        dayPtr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        dayPtr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
        dayPtr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
    }
    else if (weekday == 3){
        dayPtr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
        dayPtr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        dayPtr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        dayPtr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        dayPtr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        dayPtr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
        dayPtr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
    }
    else if (weekday == 4){
        dayPtr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
        dayPtr->push_back(Event("Standup Amogus", 9, 10, 55, 00, "9:55", "10:00"));
        dayPtr->push_back(Event("Standup Anubis", 10, 10, 0, 5, "10:00", "10:05"));
        dayPtr->push_back(Event("Standup AJVP", 10, 10, 5, 10, "10:05", "10:10"));
        dayPtr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        dayPtr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
        dayPtr->push_back(Event("Dag slut", 16, 16, 00, 00, "16:00", "16:00"));
    }
    else if (weekday == 5){
        dayPtr->push_back(Event("Dag börjar", 9, 9, 00, 00, "9:00", "9:00"));
        dayPtr->push_back(Event("Amogus sprint review", 9, 10, 00, 00, "9:00", "10:00"));
        dayPtr->push_back(Event("Lunch", 12, 13, 00, 00, "12:00", "13:00"));
        dayPtr->push_back(Event("1337 fika", 13, 13, 37, 50, "13:37", "13:50"));
        dayPtr->push_back(Event("Anubis sprint review", 14, 15, 0, 0, "14:00", "15:00"));
        dayPtr->push_back(Event("AJVP sprint review", 15, 16, 0, 0, "15:00", "16:00"));
    }
    else {
        cout << "ERROR: Day not valid or is a weekend!";
    }
}

void drawEventText(shared_ptr<deque<Event>> dayPtr, tm* timeinfo){
    raylib::Color textColor(LIGHTGRAY);
    

    textColor.DrawRectangleLines(0, 0, 1000, 250);
    textColor.DrawRectangleLines(0, 250, 1000, 250);
    textColor.DrawRectangleLines(0, 500, 1000, 250);
    textColor.DrawRectangleLines(0, 750, 1000, 250);


    if(dayPtr->size() > 0 && (*dayPtr)[0].endHour <= timeinfo->tm_hour){
        //Hour is right
        if (((*dayPtr)[0].endMinute <= timeinfo->tm_min) && ((*dayPtr)[0].endHour <= timeinfo->tm_hour) || (*dayPtr)[0].endHour < timeinfo->tm_hour )
        {
            cout << "Removed Event " <<  (*dayPtr)[0].title << endl;
            (*dayPtr).pop_front();
        }
    }

    string timesStr;
    if((*dayPtr).size() > 0){
        timesStr = (*dayPtr)[0].displayTimeStart + " - " + (*dayPtr)[0].displayTimeEnd;
        textColor.DrawText((*dayPtr)[0].title, 10 , 10, 70);
        textColor.DrawText(timesStr, 10, 100, 40);
    }

    if((*dayPtr).size() > 1){   
        timesStr = (*dayPtr)[1].displayTimeStart + " - " + (*dayPtr)[1].displayTimeEnd;
        textColor.DrawText((*dayPtr)[1].title, 10, (10 + 250), 70);
        textColor.DrawText(timesStr, 10, (100 + 250), 40);
    }

    if((*dayPtr).size() > 2){
        timesStr = (*dayPtr)[2].displayTimeStart + " - " + (*dayPtr)[2].displayTimeEnd;
        textColor.DrawText((*dayPtr)[2].title, 10, (10 + 500), 70);
        textColor.DrawText(timesStr, 10, (100 + 500), 40);
    }

    if((*dayPtr).size() > 3){
        timesStr = (*dayPtr)[3].displayTimeStart + " - " + (*dayPtr)[3].displayTimeEnd;
        textColor.DrawText((*dayPtr)[3].title, 10, (10 + 750), 70);
        textColor.DrawText(timesStr, 10, (100 + 750), 40);
    }
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