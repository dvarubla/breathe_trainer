#include <iostream>
#include "SettingsWindow.h"

namespace breathe_trainer{
    SettingsWindow::SettingsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
        _profListFrag.setWidget(ui->profilesList);
        connect(ui->profilesList->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onCurrentRowChanged(const QModelIndex&, const QModelIndex&)));
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

    void SettingsWindow::onCurrentRowChanged(const QModelIndex& cur, const QModelIndex& prev) {
        if(prev.row() != -1) {
            ProfileStrs strs = {
                    ui->nameEdit->text().toStdString(),
                    ui->inhaleEdit->text().toStdString(),
                    ui->exhaleEdit->text().toStdString(),
                    ui->pauseInhaleEdit->text().toStdString(),
                    ui->pauseExhaleEdit->text().toStdString()
            };
            _settingsWinListener.lock()->onPositionChanged(
                    prev.row(),
                    ui->profilesList->item(prev.row())->text().toStdString(),
                    strs,
                    ui->profilesList->item(cur.row())->text().toStdString()
            );
        }
    }

    void SettingsWindow::setSettingsWindowListener(const ISettWinListWPtr &settingsWinListener) {
        _settingsWinListener = settingsWinListener;
    }

    void SettingsWindow::setProfile(int index, const std::string &prof) {
        ui->profilesList->item(index)->setText(QString::fromStdString(prof));
    }
}