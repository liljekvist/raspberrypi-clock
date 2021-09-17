#include <raylib-cpp.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <time.h> 

int main() {
    int directionX (int currentXPos, int fontWidth, int screenWidth, int direction);
    int directionY (int currentYPos, int fontHeight, int screenHeight, int direction);
    // Initialization
    int screenWidth = 1920;
    int screenHeight = 1080;
    int currentXPos = 0;
    int currentYPos = 0;
    int moveXByPixels = -1;
    int moveYByPixels = -1;

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
        fprintf(stderr, "%i : %i \n", currentXPos, screenWidth);

        std::cout << (screenWidth + fontWidth);
        moveXByPixels = directionX(currentXPos, fontWidth, screenWidth, moveXByPixels);
        moveYByPixels = directionX(currentYPos, fontHeight, screenHeight, moveYByPixels);

        currentXPos = currentXPos + moveXByPixels;
        currentYPos = currentYPos + moveYByPixels;

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            textColor.DrawText(buffer, currentXPos, currentYPos, 200);
        EndDrawing();
    }

    return 0;
}

int directionX (int currentXPos, int fontWidth, int screenWidth, int direction){
    if(currentXPos > (screenWidth - fontWidth)) {
        fprintf(stderr, "Dirr x\n");
        return -1;
    }
    else if( currentXPos < 0){
        return 1;
    }
    return direction;
}

int directionY (int currentYPos, int fontHeight, int screenHeight, int direction){
    if(currentYPos > (screenHeight - fontHeight)) {
        fprintf(stderr, "Dirr x\n");
        return -1;
    }
    else if( currentYPos < 0){
        return 1;
    }
    return direction;
}