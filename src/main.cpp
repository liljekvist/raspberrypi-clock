#include <raylib-cpp.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <time.h> 

int main() {
    int calculateTextPositionX(int fontWidth, int screenWidth);
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "PogClock");
    
    SetTargetFPS(30);

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsKeyPressed(KEY_F11))
 		{
            // see what display we are on right now
 			int display = GetCurrentMonitor();
 
            
            if (IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                SetWindowSize(screenWidth, screenHeight);
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            }
 
            // toggle the state
 			ToggleFullscreen();
 		}

        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];
        //if()

        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%T",timeinfo);
        int fontWidth = MeasureText(buffer,200);
        int fontHeight = 200;
        
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(1100,0,1101,1080,LIGHTGRAY);
            textColor.DrawText(buffer, 1130, 0, 200);
        EndDrawing();
    }

    return 0;
}
