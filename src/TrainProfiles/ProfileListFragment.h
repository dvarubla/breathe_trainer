#pragma once

#include <QtWidgets/QListWidget>
#include <TrainerCommon.h>

namespace breathe_trainer {
    class ProfileListFragment {
    private:
        QListWidget *_widget;
    public:
        explicit ProfileListFragment();
        void setProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end);
        void setWidget(QListWidget *widget);
    };
}
