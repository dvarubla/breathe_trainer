#pragma once

#include "ISettingsWindow.h"

namespace breathe_trainer {
    class ISettingsWindowListener {
    public:
        virtual void onPositionChanged(int index, const std::string &oldName, const ProfileStrs &profileStrs, const std::string &newName) = 0;
        virtual void onSaveBtnClicked() = 0;
        virtual void onCancelBtnClicked() = 0;
    };

    typedef std::weak_ptr<ISettingsWindowListener> ISettWinListWPtr;
}
