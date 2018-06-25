#pragma once

#include <memory>
#include <TrainProfiles/TrainProfile.h>

namespace breathe_trainer {
    struct ProfileStrs{
        std::string name;
        std::string inhalationTime;
        std::string pauseTimeAfterInhalation;
        std::string exhalationTime;
        std::string pauseTimeAfterExhalation;
    };
    class ISettingsWindow {
    public:
        enum class ButtonId{
            ADD,
            DELETE,
            MOVE_UP,
            MOVE_DOWN,
            SAVE,
            CANCEL
        };
        virtual void showWindow() = 0;
        virtual void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) = 0;
        virtual void setFieldStrings(const ProfileStrs &strs) = 0;
        virtual void setProfile(int index, const std::string &prof) = 0;
        virtual std::string getSelectedProfileName() = 0;
        virtual int getSelectedIndex() = 0;
        virtual void setSelectedIndex(int index) = 0;
        virtual ProfileStrs getProfileStrings() = 0;
        virtual std::optional<std::string> showAddNameDialog() = 0;
        virtual void clearProfiles() = 0;
        virtual void setButtonDisabled(ButtonId id, bool disabled) = 0;
    };
    typedef std::shared_ptr<ISettingsWindow> ISettWinPtr;
}
