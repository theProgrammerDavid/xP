#pragma once
#include "config.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <memory>
#include "util.hpp"
#include <cpr/ssl_options.h>
#include <cpr/cprtypes.h>
#include "imgui.h"
#ifdef _Win32
#include <Windows.h>
#endif
using namespace cpr;

void glfw_error_callback(int error, const char *description);

class Constants
{
private:
    std::string workingDir;
    std::string configFilePath;
    std::string iniFilePath;
    ImGuiWindowFlags windowFlags;
    YAML::Node config;
    template <class T>
    void writeToFile(std::ofstream& fout, const char* key, const T& value);
public:
    ImGuiWindowFlags getWindowFlags();
    void writeConfig();
    void updateWindowFlags();
    const char* getWorkingDir();
    const char* getConfigFilePath();
    const char* getIniFilePath();
    void defaultValues();
    void createConfigFile();
    bool configFileExists();
    void setOnlineStatus(bool status);
    Constants();
    enum
    {
        DARK,
        LIGHT,
        CLASSIC
    };

    void setTheme();
    int MAX_URL_SIZE;
    SslOptions sslOpts;
    int REQUEST_TIMEOUT;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int CURRENT_THEME;
    float FONT_SIZE;
    bool configError;
    bool moveWindow;
    bool htmlIndent;
    bool isOnline;
    std::string PATH_TO_FONT;
    float highDPIscaleFactor;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    const char *REQUEST_TYPE[6] = {"GET", "POST", "PUT", "DELETE", "HEAD", "OPTIONS"};
    const char *THEMES[3] = {"DARK", "LIGHT", "CLASSIC"};
    ImVec4 TEMP_BG_COLOR = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Static access method. */
    // static Constants* getInstance();
};
inline std::unique_ptr<Constants> constants{new Constants()};