#pragma once

#include <memory>
#include <TrainProfiles/TrainProfile.h>

namespace breathe_trainer {
    struct ProfileData{
        std::string name;
        TrainProfile profile;
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
        virtual void setFieldStrings(const ProfileData &data) = 0;
        virtual void setProfile(int index, const std::string &prof) = 0;
        virtual std::string getSelectedProfileName() = 0;
        virtual int getSelectedIndex() = 0;
        virtual void setSelectedIndex(int index) = 0;
        virtual ProfileData getProfileStrings() = 0;
        virtual std::optional<std::string> showAddNameDialog() = 0;
        virtual void clearProfiles() = 0;
        virtual void setButtonDisabled(ButtonId id, bool disabled) = 0;
        virtual void showAddErrDialog(const std::string &name) = 0;
        virtual void resize(uint_fast32_t w, uint_fast32_t h) = 0;
    };
    typedef std::shared_ptr<ISettingsWindow> ISettWinPtr;
}
