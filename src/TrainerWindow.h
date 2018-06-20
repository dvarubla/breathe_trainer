#pragma once
#include <qmainwindow.h>
#include <ui_trainer.h>
#include <memory>
#include "ITrainerWindow.h"

namespace breathe_trainer {
    class TrainerWindow : public QMainWindow, public ITrainerWindow {
    Q_OBJECT
    public:
        explicit TrainerWindow();

        void setTotalTime(const std::string &str) override;

        void setPhaseTime(const std::string &str) override;

        void setPhase(const std::string &str) override;

        ~TrainerWindow();
        void showWindow() override;

        void setAmountColor(double amount, uint_fast32_t color) override;

    private:
        Ui::TrainerWindow *ui;
    };
}
