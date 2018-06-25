#include <iostream>
#include <QtWidgets/QInputDialog>
#include "SettingsWindow.h"

namespace breathe_trainer{
    SettingsWindow::SettingsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
        _profListFrag.setWidget(ui->profilesList);
        connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
        connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
        connect(ui->moveUpBtn, SIGNAL(clicked()), this, SLOT(onMoveUpBtnClicked()));
        connect(ui->moveDownBtn, SIGNAL(clicked()), this, SLOT(onMoveDownBtnClicked()));
        connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
        connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteBtnClicked()));
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
        if(prev.row() != -1 && cur.row() != -1) {
            _settingsWinListener.lock()->onPositionChanged(
                    prev.row(),
                    ui->profilesList->item(prev.row())->text().toStdString(),
                    getProfileStrings(),
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

    void SettingsWindow::onSaveBtnClicked() {
        _settingsWinListener.lock()->onSaveBtnClicked();
    }

    std::string SettingsWindow::getSelectedProfileName() {
        return _profListFrag.getSelectedProfileName();
    }

    ProfileStrs SettingsWindow::getProfileStrings() {
        return {
                ui->nameEdit->text().toStdString(),
                ui->inhaleEdit->text().toStdString(),
                ui->exhaleEdit->text().toStdString(),
                ui->pauseInhaleEdit->text().toStdString(),
                ui->pauseExhaleEdit->text().toStdString()
        };
    }

    int SettingsWindow::getSelectedIndex() {
        return ui->profilesList->currentRow();
    }

    void SettingsWindow::onCancelBtnClicked() {
        _settingsWinListener.lock()->onCancelBtnClicked();
    }

    void SettingsWindow::onMoveUpBtnClicked() {
        _settingsWinListener.lock()->onMoveUpBtnClicked();
    }

    void SettingsWindow::onMoveDownBtnClicked() {
        _settingsWinListener.lock()->onMoveDownBtnClicked();
    }

    void SettingsWindow::setSelectedIndex(int index) {
        ui->profilesList->setCurrentRow(index);
    }

    std::optional<std::string> SettingsWindow::showAddNameDialog() {
        QInputDialog dialog(this);
        dialog.setCancelButtonText("Отмена");
        dialog.setOkButtonText("Добавить");
        dialog.setLabelText("Название профиля:");
        dialog.setWindowTitle("Введите название профиля");
        auto status =  dialog.exec();
        if(status == QDialog::Accepted){
            return dialog.textValue().toStdString();
        } else {
            return std::nullopt;
        }
    }

    void SettingsWindow::onAddBtnClicked() {
        _settingsWinListener.lock()->onAddBtnClicked();
    }

    void SettingsWindow::onDeleteBtnClicked() {
        _settingsWinListener.lock()->onDeleteBtnClicked();
    }
}