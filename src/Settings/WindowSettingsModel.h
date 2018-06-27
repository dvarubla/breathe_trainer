#pragma once

#include "IWindowSettingsModel.h"

namespace breathe_trainer {
    class WindowSettingsModel : public IWindowSettingsModel{
    private:
        WHMap _whData;
    public:
        explicit WindowSettingsModel(const WHMap &data);

        void saveSize(const std::string_view &str, const WidthHeight &wh) override;

        WHMap& getData() override;

        WidthHeight getSize(const std::string_view &str) override;
    };
}