#pragma once
#include <qmainwindow.h>
#include <ui_trainer.h>
#include <memory>
#include "ITrainerWindow.h"
#include "ITrainerModelListener.h"

namespace breathe_trainer {
    class TrainerWindow : public QMainWindow, public ITrainerWindow {
    Q_OBJECT
    private:
        ITWinListenerWPtr _listener;
        Q_INVOKABLE void _setTotalTime(const std::string &str);

        Q_INVOKABLE void _setPhaseTime(const std::string &str);

        Q_INVOKABLE void _setPhase(const std::string &str);

        Q_INVOKABLE void _setAmountColor(double amount, uint_fast32_t color);

    public slots:
        void startButtonClicked();
        void stopButtonClicked();
    public:
        void setListener(const ITWinListenerWPtr &listener) override;

        explicit TrainerWindow();

        void setTotalTime(const std::string &str) override;

        void setPhaseTime(const std::string &str) override;

        void setPhase(const std::string &str) override;

        void setStopButtonEnable(bool status) override;

        ~TrainerWindow();
        void showWindow() override;

        void setAmountColor(double amount, uint_fast32_t color) override;

    private:
        Ui::TrainerWindow *ui;
    };
}
