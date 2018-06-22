#pragma once

#include <QtWidgets/QListWidget>
#include <TrainProfiles/TrainProfile.h>

namespace breathe_trainer {
    class ProfileListFragment {
    private:
        QListWidget *_widget;
    public:
        explicit ProfileListFragment();
        void setProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end);
        std::string getSelectedProfileName();
        void setWidget(QListWidget *widget);
    };
}
