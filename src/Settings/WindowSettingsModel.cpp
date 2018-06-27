#include "WindowSettingsModel.h"

namespace breathe_trainer{
    void WindowSettingsModel::saveSize(const std::string_view &str, const WidthHeight &wh) {
        _whData[std::string(str)] = wh;
    }

    WHMap& WindowSettingsModel::getData() {
        return _whData;
    }

    WidthHeight WindowSettingsModel::getSize(const std::string_view &str) {
        return {_whData[std::string(str)].width, _whData[std::string(str)].height};
    }

    WindowSettingsModel::WindowSettingsModel(const WHMap &data) : _whData(data){
    }
}