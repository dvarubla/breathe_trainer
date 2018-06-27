#pragma once

#include <string>
#include <unordered_map>

namespace breathe_trainer{
    struct WidthHeight{
        uint_fast32_t width;
        uint_fast32_t height;
    };

    typedef std::unordered_map<std::string, WidthHeight> WHMap;

    static const std::string_view MAIN_WINDOW_NAME = "MainWindow";
    static const std::string_view SETTINGS_WINDOW_NAME = "SettingsWindow";
}