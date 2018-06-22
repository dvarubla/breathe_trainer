#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "ISettingsWindow.h"
#include <ui_settings.h>
#include <TrainProfiles/ProfileListFragment.h>

namespace breathe_trainer {
    class SettingsWindow : public QMainWindow, public ISettingsWindow {
    private:
        ProfileListFragment _profListFrag;
    public:
        explicit SettingsWindow(QWidget *parent);

        ~SettingsWindow() override;

        void showWindow() override;

        void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) override;

        void setFieldStrings(const ProfileStrs &strs);

    private:
        Ui::SettingsWindow *ui;
    };
}