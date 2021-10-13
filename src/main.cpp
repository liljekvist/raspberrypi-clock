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
void getCalendarFromSchoolsoft();
deque<string> findRowOfTodaysFood(int week, int day);

int main() {
    //Creates a main object for use later.
    class main mainObject;

    // Initialization
    int screenWidth = 2560;
    int screenHeight = 1440;
    Rectangle container = { 25.0f, 25.0f, screenWidth - 50.0f, screenHeight - 250.0f };
    SetTraceLogCallback(LogCustom);
    SetTargetFPS(60);
    
    //Init Raylib objects
    raylib::Color whiteColor(LIGHTGRAY);
    raylib::Color blackColor(BLACK);
    raylib::Window w(screenWidth, screenHeight, "PogClock");
    
    //Gets todays day as string
    string currentDay = mainObject.getCurrentDayString();

    //Audio intis and sound loading
    InitAudioDevice(); 
    (*mainObject.effectPtr) = LoadSound("sound/siren.wav");

    //Construct a vector to use for getting todays events
    mainObject.constructDayVector();

    //Get image from r/ProgrammerHumor and Scale the image to the correct size
    auto filename = getImageFromUrl(getImageUrlFromReddit());
    raylib::Texture texture(filename);
    mainObject.ResizeImage(&texture, 500, 500);

    //Get and Process todays food
    strftime (mainObject.weekNumberbuffer,80,"%V",mainObject.timeinfo);
    mainObject.weekNumberbufferToInt();
    getCalendarFromSchoolsoft();
    deque<string> lunchStrings = findRowOfTodaysFood(mainObject.weekNumber, mainObject.getCurrentDayInt());
    for(int i = 0; i < lunchStrings.size(); i++){
        std::string delim = "\\n";
        lunchStrings[i].erase(0, lunchStrings[i].find(delim) + delim.length());
    }

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {

        //Forcing the application to run in fullscreen
        if (IsCursorOnScreen()){
            DisableCursor();
            HideCursor();
        }
        if (!IsWindowFullscreen())
        {
            // if we are not in fullscreen set fullscreen
            ToggleFullscreen();
        }

        //Sound logic function for when sound should be played.
        soundLogic(mainObject.effectPtr, mainObject.Ptr, mainObject.timeinfo);

        //Gets time string to print it later
        time (&mainObject.rawtime);
        mainObject.timeinfo = localtime (&mainObject.rawtime);
        strftime (mainObject.buffer,80,"%T",mainObject.timeinfo);


        // Draw
        BeginDrawing();
            //Clear background
            blackColor.ClearBackground();
            //Draw events
            mainObject.drawEventText();
            DrawTexture(texture, 1300 - texture.width, screenHeight - texture.height, WHITE);
            //Draw clock and borderline
            whiteColor.DrawText(mainObject.buffer, 1320, 0, 200);
            whiteColor.DrawText(currentDay, 1320, 250, 80);
            whiteColor.DrawLine(1300,0,1301,1440);

            //Draws todays food
            whiteColor.DrawText("Lunch: " + lunchStrings[0], 1320, 350, 40);
            whiteColor.DrawText("Veg Lunch: " + lunchStrings[1], 1320, 450, 40);
            
            //Draw "Made by" text
            whiteColor.DrawText("Made with <3 by liljekvist", 10, screenHeight - 40, 40);
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

void getCalendarFromSchoolsoft(){
        //Get Calendar from schoolsoft as requested by kasper.
        //It also saves it locally to help debugging.
        const std::string url("https://sms.schoolsoft.se/nti/jsp/public/right_public_student_ical.jsp?key=f9b774bfb49adf25605253580b3150c0");
        CURL* curl = curl_easy_init();
        FILE *fp;
        CURLcode res;
        std::string filename = "calendar";
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
    }

deque<string> findRowOfTodaysFood(int week, int day) {
    string substring = "lunchmenu-" + to_string(week) + "-" + to_string(day - 1); // minus 1 due to it having a sundat to saturday week format
    cout << "substring: " << substring << endl;

    ifstream calendarString("calendar", std::ifstream::in);
    string x;
    bool ans = false;
    int line = 1;
    deque<string> stringArr;
    string rowCache, rowCache2;

    if (calendarString.is_open()) //is_open open the text file.
    {

        while (std::getline(calendarString, x)) {
            if (x.find(substring, 0) != string::npos) {

                    if(rowCache[0] == ' '){
                        printf("old cache1: %s \n", rowCache.c_str());
                        printf("old cache2: %s \n", rowCache2.c_str());
                        rowCache = rowCache.c_str() + rowCache2;
                        printf("new cache: %s \n", rowCache.c_str());
                    }

                    printf("Substring found at row: %i \n", line);
                    stringArr.push_back(rowCache);
                    ans = true;
            }
            rowCache2 = rowCache;
            rowCache = x;
            line++;
        }
        calendarString.close(); //to close text file.
    } 
    else
        cout << "Unable to open file";

    if (!ans) // if subtring not present.
        cout << "subtring not present is present" << endl;

    return stringArr;
}