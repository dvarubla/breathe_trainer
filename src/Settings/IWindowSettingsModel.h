#pragma once

#include <memory>
#include "WidthHeight.h"

namespace breathe_trainer{
    class IWindowSettingsModel {
    public:
        virtual void saveSize(const std::string_view &str, const WidthHeight &wh) = 0;
        virtual WidthHeight getSize(const std::string_view &str) = 0;
        virtual WHMap& getData() = 0;
    };

    typedef std::shared_ptr<IWindowSettingsModel> IWinSettMPtr;
}