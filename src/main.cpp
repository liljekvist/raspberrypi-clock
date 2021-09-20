#include "main.hpp"


int main() {
    std::vector<Event> Monday;
    std::vector<Event> Tuesday;
    std::vector<Event> Wednesday;
    std::vector<Event> Thursday;
    std::vector<Event> Friday;
    bool days[7] = {true,true,true,true,true,false,false};
    Monday.push_back(Event(anubisStandUpMessage, 10, 10, 0, 5, days));

    int calculateTextPositionX(int fontWidth, int screenWidth);
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "PogClock");
    
    SetTargetFPS(10);

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
            DrawFPS(10, 10);
            ClearBackground(BLACK);
            DrawLine(1000,0,1001,1080,LIGHTGRAY);
            textColor.DrawText(buffer, 1030, 0, 200);
        EndDrawing();
    }

    return 0;
}
