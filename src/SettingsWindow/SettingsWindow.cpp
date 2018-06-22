#include "SettingsWindow.h"

namespace breathe_trainer{
    SettingsWindow::SettingsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
        _profListFrag.setWidget(ui->profilesList);
        connect(ui->profilesList, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
    }

    void SettingsWindow::showWindow() {
        show();
    }

    SettingsWindow::~SettingsWindow() {
        delete ui;
    }

    void SettingsWindow::addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) {
        _profListFrag.setProfiles(begin, end);
    }

    void SettingsWindow::setFieldStrings(const ProfileStrs &strs) {
        ui->nameEdit->setText(QString::fromStdString(strs.name));
        ui->inhaleEdit->setText(QString::fromStdString(strs.inhalationTime));
        ui->exhaleEdit->setText(QString::fromStdString(strs.exhalationTime));
        ui->pauseInhaleEdit->setText(QString::fromStdString(strs.pauseTimeAfterInhalation));
        ui->pauseExhaleEdit->setText(QString::fromStdString(strs.pauseTimeAfterExhalation));
    }

    void SettingsWindow::onCurrentRowChanged(int row) {
        if(row != -1) {
            _settingsWinListener.lock()->onPositionChanged(ui->profilesList->item(row)->text().toStdString());
        }
    }

    void SettingsWindow::setSettingsWindowListener(const ISettWinListWPtr &settingsWinListener) {
        _settingsWinListener = settingsWinListener;
    }
}