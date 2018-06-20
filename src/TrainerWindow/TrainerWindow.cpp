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
        QMetaObject::invokeMethod(this, "_setTotalTime", Qt::AutoConnection, Q_ARG(std::string, str));
    }

    void TrainerWindow::setPhaseTime(const std::string &str) {
        QMetaObject::invokeMethod(this, "_setPhaseTime", Qt::AutoConnection, Q_ARG(std::string, str));
    }

    void TrainerWindow::setPhase(const std::string &str) {
        QMetaObject::invokeMethod(this, "_setPhase", Qt::AutoConnection, Q_ARG(std::string, str));
    }

    void TrainerWindow::setAmountColor(double amount, uint_fast32_t color) {
        QMetaObject::invokeMethod(this, "_setAmountColor", Qt::AutoConnection, Q_ARG(double, amount), Q_ARG(uint_fast32_t, color));
    }

    void TrainerWindow::_setTotalTime(const std::string &str) {
        ui->totalTime->setText(QString::fromStdString(str));
    }

    void TrainerWindow::_setPhaseTime(const std::string &str) {
        ui->phaseTime->setText(QString::fromStdString(str));
    }

    void TrainerWindow::_setPhase(const std::string &str) {
        ui->phase->setText(QString::fromStdString(str));
    }

    void TrainerWindow::_setAmountColor(double amount, uint_fast32_t color) {
        ui->timeMeter->setAmountColor(amount, color);
    }
}
