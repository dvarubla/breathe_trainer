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
        void setTextEditsDisabled(bool disabled);
    public slots:
        void onCurrentRowChanged(const QModelIndex& cur, const QModelIndex& prev);
        void onSaveBtnClicked();
        void onCancelBtnClicked();
        void onMoveUpBtnClicked();
        void onMoveDownBtnClicked();
        void onAddBtnClicked();
        void onDeleteBtnClicked();
    protected:
        void resizeEvent(QResizeEvent *event) override;
    public:
        explicit SettingsWindow(QWidget *parent);

        void showWindow() override;

        void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) override;

        void setFieldStrings(const ProfileData &data) override;

        void setSettingsWindowListener(const ISettWinListWPtr &settingsWinListener);

        void setProfile(int index, const std::string &prof) override;

        std::string getSelectedProfileName() override;

        ProfileData getProfileStrings() override;

        int getSelectedIndex() override;

        void setSelectedIndex(int index) override;

        std::optional<std::string> showAddNameDialog() override;

        void clearProfiles() override;

        void setButtonDisabled(ButtonId id, bool disabled) override;

        void showAddErrDialog(const std::string &name) override;

        void resize(uint_fast32_t w, uint_fast32_t h) override;

    private:
        std::unique_ptr<Ui::SettingsWindow> ui;
    };
}