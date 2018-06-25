#pragma once
#include <qmainwindow.h>
#include <ui_trainer.h>
#include <memory>
#include <TrainProfiles/ProfileListFragment.h>
#include "ITrainerWindow.h"
#include "ITrainerModelListener.h"

namespace breathe_trainer {
    class TrainerWindow : public QMainWindow, public ITrainerWindow {
    Q_OBJECT
    private:
        ITrainWinListWPtr _listener;
        ProfileListFragment _profListFrag;
        Q_INVOKABLE void _setTotalTime(const std::string &str);

        Q_INVOKABLE void _setPhaseTime(const std::string &str);

        Q_INVOKABLE void _setPhase(const std::string &str);

        Q_INVOKABLE void _setAmountColor(double amount, uint_fast32_t color);

    public slots:
        void startButtonClicked();
        void stopButtonClicked();
        void editButtonClicked();
    public:
        void setListener(const ITrainWinListWPtr &listener) override;

        explicit TrainerWindow();

        void setTotalTime(const std::string &str) override;

        void setPhaseTime(const std::string &str) override;

        void setPhase(const std::string &str) override;

        void setStopButtonEnable(bool status) override;

        ~TrainerWindow() override;
        void showWindow() override;

        void setAmountColor(double amount, uint_fast32_t color) override;

        void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) override;

        std::string getSelectedProfileName() override;

        void clearProfiles() override;

        void setCycleNum(const std::string &str) override;

    private:
        Ui::TrainerWindow *ui;
    };
}
