#include "TrainerWindow.h"
#include "ITrainerModelListener.h"

namespace breathe_trainer {

    TrainerWindow::TrainerWindow() : QMainWindow(nullptr), ui(new Ui::TrainerWindow){
        ui->setupUi(this);
        _profListFrag.setWidget(ui->profilesList);

        connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
        connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
        connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
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

    void TrainerWindow::startButtonClicked() {
        _listener.lock()->onStartPressed();
    }

    void TrainerWindow::stopButtonClicked() {
        _listener.lock()->onStopPressed();
    }

    void TrainerWindow::setListener(const ITrainWinListWPtr &listener) {
        _listener = listener;
    }

    void TrainerWindow::setStopButtonEnable(bool status) {
        ui->stopButton->setEnabled(status);
    }

    void TrainerWindow::addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) {
        _profListFrag.setProfiles(begin, end);
    }

    std::string TrainerWindow::getSelectedProfileName() {
        return ui->profilesList->selectedItems().first()->text().toStdString();
    }

    void TrainerWindow::editButtonClicked() {
        _listener.lock()->onEditPressed();
    }
}
