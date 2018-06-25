#pragma once

#include "ITrainerWindowListener.h"

namespace breathe_trainer {
    class ITrainerWindow {
    public:
        virtual void showWindow() = 0;
        virtual void setTotalTime(const std::string &str) = 0;
        virtual void setPhaseTime(const std::string &str) = 0;
        virtual void setPhase(const std::string &str) = 0;
        virtual void setCycleNum(const std::string &str) = 0;
        virtual void setAmountColor(double amount, uint_fast32_t color) = 0;
        virtual void setListener(const ITrainWinListWPtr &ctrl) = 0;
        virtual void setStopButtonEnable(bool status) = 0;

        virtual void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) = 0;
        virtual std::string getSelectedProfileName() = 0;
        virtual void clearProfiles() = 0;
    };

    typedef std::shared_ptr<ITrainerWindow> ITrainWinPtr;
}
