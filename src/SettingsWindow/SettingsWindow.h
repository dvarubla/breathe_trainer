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
        void onCurrentRowChanged(const QModelIndex& cur, const QModelIndex& prev);
        void onSaveBtnClicked();
        void onCancelBtnClicked();
        void onMoveUpBtnClicked();
        void onMoveDownBtnClicked();
        void onAddBtnClicked();
        void onDeleteBtnClicked();
    public:
        explicit SettingsWindow(QWidget *parent);

        ~SettingsWindow() override;

        void showWindow() override;

        void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) override;

        void setFieldStrings(const ProfileStrs &strs) override;

        void setSettingsWindowListener(const ISettWinListWPtr &settingsWinListener);

        void setProfile(int index, const std::string &prof) override;

        std::string getSelectedProfileName() override;

        ProfileStrs getProfileStrings() override;

        int getSelectedIndex() override;

        void setSelectedIndex(int index) override;

        std::optional<std::string> showAddNameDialog() override;

    private:
        Ui::SettingsWindow *ui;
    };
}