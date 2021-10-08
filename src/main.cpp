#include "main.hpp"

namespace {
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
        {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
        }

    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t written;
        written = fwrite(ptr, size, nmemb, stream);
        return written;
    }
}

void LogCustom(int msgType, const char *text, va_list args);
void soundLogic(shared_ptr<Sound> soundEffect, shared_ptr<deque<Event>> dayPtr, tm * timeinfo);
std::string getImageUrlFromReddit();
std::string getImageFromUrl(std::string url);

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
    auto filename = getImageFromUrl(getImageUrlFromReddit());
    raylib::Texture texture(filename);
    int orgHeight = texture.height;
    int orgWidth = texture.width;
    texture.SetWidth(700 * orgWidth / orgHeight);
    texture.SetHeight(700 * orgHeight / orgWidth);

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
            DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
            //Draw clock and borderline
            whiteColor.DrawText(mainObject.buffer, 1030, 0, 200);
            whiteColor.DrawText(currentDay, 1030, 250, 100);
            whiteColor.DrawLine(1000,0,1001,1080);
            
            //Draw "Made by" text
            whiteColor.DrawText("Made with <3 by liljekvist", 10, 20 + 1000, 40);
        EndDrawing();
    }
    UnloadTexture(texture);
    CloseWindow();
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

std::string getImageUrlFromReddit(){
        //Get top post of r/ProgrammingHumor
        //https://www.reddit.com/r/ProgrammerHumor/top.json?limit=1
        const std::string url("https://www.reddit.com/r/ProgrammerHumor/top.json?limit=1");
        CURL* curl = curl_easy_init();
        std::string urlreturn;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        std::unique_ptr<std::string> httpData(new std::string());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        Json::Value jsonData;
        Json::Reader jsonReader;
        if (jsonReader.parse(*httpData, jsonData)){
            auto newobj = jsonData["data"]["children"][0];
            urlreturn = newobj["data"]["url"].asString();
            std::cout << "Got URL:" << urlreturn << std::endl;
        }
        else{
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
        }
        return urlreturn;
    }

std::string getImageFromUrl(std::string url){
        CURL* curl = curl_easy_init();
        FILE *fp;
        CURLcode res;
        std::string filename = "meme." + url.substr(url.length() - 3);
        char outfilename[filename.length() + 1];
        strcpy(outfilename, filename.c_str());
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        return filename;
    }
