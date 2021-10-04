#include "main.hpp"

void LogCustom(int msgType, const char *text, va_list args);
void soundLogic(shared_ptr<Sound> soundEffect, shared_ptr<deque<Event>> dayPtr, tm * timeinfo);

int main() {

    class main mainObject;
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;
    SetTraceLogCallback(LogCustom);
    SetTargetFPS(60);
    
    raylib::Color whiteColor(LIGHTGRAY);
    raylib::Color blackColor(BLACK);
    raylib::Window w(screenWidth, screenHeight, "PogClock");
    
    string currentDay = mainObject.getCurrentDayString();

    InitAudioDevice(); 
    (*mainObject.effectPtr) = LoadSound("sound/siren.wav");

    mainObject.constructDayVector();

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

        soundLogic(mainObject.effectPtr, mainObject.Ptr, mainObject.timeinfo);

        time (&mainObject.rawtime);
        mainObject.timeinfo = localtime (&mainObject.rawtime);
        strftime (mainObject.buffer,80,"%T",mainObject.timeinfo);

        // Draw
        BeginDrawing();
            //Clear background
            blackColor.ClearBackground();

            //Draw events
            mainObject.drawEventText();
            //Draw clock and borderline
            whiteColor.DrawText(mainObject.buffer, 1030, 0, 200);
            whiteColor.DrawText(currentDay, 1030, 250, 100);
            whiteColor.DrawLine(1000,0,1001,1080);
            
            //Draw "Made by" text
            whiteColor.DrawText("Made with <3 by liljekvist", 10, 20 + 1000, 40);
        EndDrawing();
    }
    CloseAudioDevice();
    return 0;
}

void soundLogic(shared_ptr<Sound> soundEffect, shared_ptr<deque<Event>> dayPtr, tm * timeinfo){
        if(((*dayPtr)[0].endHour == timeinfo->tm_hour) && ((*dayPtr)[0].endMinute == timeinfo->tm_min) && ((*dayPtr)[0].hasPlayedSoundEnd == false)){
            (*dayPtr)[0].hasPlayedSoundEnd = true;
                PlaySound((*soundEffect)); 
        }

        if(((*dayPtr)[0].startHour == timeinfo->tm_hour) && ((*dayPtr)[0].startMinute == timeinfo->tm_min) && ((*dayPtr)[0].hasPlayedSoundStart == false)){
            (*dayPtr)[0].hasPlayedSoundStart = true;
                PlaySound((*soundEffect)); 
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