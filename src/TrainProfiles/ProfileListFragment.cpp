#include "ProfileListFragment.h"

namespace breathe_trainer{
    ProfileListFragment::ProfileListFragment(){
    }

    void ProfileListFragment::setProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end){
        _widget->clear();
        for(auto it = begin; it != end; ++it){
            _widget->addItem(QString::fromStdString(*it));
        }
        _widget->item(0)->setSelected(true);
    }

    void ProfileListFragment::setWidget(QListWidget *widget) {
        _widget = widget;
    }
}