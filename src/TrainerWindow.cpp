#include "TrainerWindow.h"

namespace breathe_trainer {

    TrainerWindow::TrainerWindow() : QMainWindow(nullptr), ui(new Ui::TrainerWindow) {
        ui->setupUi(this);
    }

    void TrainerWindow::showWindow() {
        show();
    }

    TrainerWindow::~TrainerWindow() {
        delete ui;
    }

    void TrainerWindow::setTotalTime(const std::string &str) {
        ui->totalTime->setText(QString::fromStdString(str));
    }

    void TrainerWindow::setPhaseTime(const std::string &str) {
        ui->phaseTime->setText(QString::fromStdString(str));
    }

    void TrainerWindow::setPhase(const std::string &str) {
        ui->phase->setText(QString::fromStdString(str));
    }

    void TrainerWindow::setAmountColor(double amount, uint_fast32_t color) {
        ui->timeMeter->setAmountColor(amount, color);
    }
}
