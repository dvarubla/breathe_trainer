#pragma once

#include "ISettingsWindow.h"

namespace breathe_trainer {
    class ISettingsWindowListener {
    public:
        virtual void onPositionChanged(int index, const std::string &oldName, const ProfileData &profileData, const std::string &newName) = 0;
        virtual void onSaveBtnClicked() = 0;
        virtual void onCancelBtnClicked() = 0;
        virtual void onMoveUpBtnClicked() = 0;
        virtual void onMoveDownBtnClicked() = 0;
        virtual void onAddBtnClicked() = 0;
        virtual void onDeleteBtnClicked() = 0;
        virtual void onResize(uint_fast32_t w, uint_fast32_t h) = 0;
    };

    typedef std::weak_ptr<ISettingsWindowListener> ISettWinListWPtr;
}
