#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "ISettingsWindow.h"
#include "ISettingsWindowListener.h"
#include <ui_settings.h>
#include <TrainProfiles/ProfileListFragment.h>

namespace breathe_trainer {
    class SettingsWindow : public QMainWindow, public ISettingsWindow {
        Q_OBJECT
    private:
        ProfileListFragment _profListFrag;
        ISettWinListWPtr _settingsWinListener;
    public slots:
        void onCurrentRowChanged(int row);
    public:
        explicit SettingsWindow(QWidget *parent);

        ~SettingsWindow() override;

        void showWindow() override;

        void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) override;

        void setFieldStrings(const ProfileStrs &strs) override;

        void setSettingsWindowListener(const ISettWinListWPtr &settingsWinListener);

    private:
        Ui::SettingsWindow *ui;
    };
}