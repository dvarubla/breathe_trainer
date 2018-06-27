#include <iostream>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QResizeEvent>
#include "SettingsWindow.h"

namespace breathe_trainer{
    SettingsWindow::SettingsWindow(QWidget *parent): QMainWindow(parent), ui(std::make_unique<Ui::SettingsWindow>()) {
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

    void SettingsWindow::addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) {
        _profListFrag.setProfiles(begin, end);
    }

    void SettingsWindow::setFieldStrings(const ProfileData &data) {
        setTextEditsDisabled(false);
        ui->nameEdit->setText(QString::fromStdString(data.name));
        ui->inhaleEdit->setValue(static_cast<int>(data.profile.inhalationTime.initial));
        ui->exhaleEdit->setValue(static_cast<int>(data.profile.exhalationTime.initial));
        ui->pauseInhaleEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterInhalation.initial));
        ui->pauseExhaleEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterExhalation.initial));

        ui->inhaleBeginEdit->setValue(static_cast<int>(data.profile.inhalationTime.startCycle));
        ui->exhaleBeginEdit->setValue(static_cast<int>(data.profile.exhalationTime.startCycle));
        ui->inhalePauseBeginEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterInhalation.startCycle));
        ui->exhalePauseBeginEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterExhalation.startCycle));

        ui->inhaleEveryEdit->setValue(static_cast<int>(data.profile.inhalationTime.everyCycle));
        ui->exhaleEveryEdit->setValue(static_cast<int>(data.profile.exhalationTime.everyCycle));
        ui->inhalePauseEveryEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterInhalation.everyCycle));
        ui->exhalePauseEveryEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterExhalation.everyCycle));

        ui->inhaleDeltaEdit->setValue(static_cast<int>(data.profile.inhalationTime.delta));
        ui->exhaleDeltaEdit->setValue(static_cast<int>(data.profile.exhalationTime.delta));
        ui->inhalePauseDeltaEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterInhalation.delta));
        ui->exhalePauseDeltaEdit->setValue(static_cast<int>(data.profile.pauseTimeAfterExhalation.delta));

        ui->restStartEdit->setValue(static_cast<int>(data.profile.restStart));
        ui->restDurEdit->setValue(static_cast<int>(data.profile.restDur));
        ui->restInhaleEdit->setValue(static_cast<int>(data.profile.restInhalationTime));
        ui->restExhaleEdit->setValue(static_cast<int>(data.profile.restExhalationTime));
        ui->restPauseInhaleEdit->setValue(static_cast<int>(data.profile.restPauseTimeAfterInhalation));
        ui->restPauseExhaleEdit->setValue(static_cast<int>(data.profile.restPauseTimeAfterExhalation));
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

    ProfileData SettingsWindow::getProfileStrings() {
        return {
                ui->nameEdit->text().toStdString(),
                {
                    {
                            static_cast<TimeSec>(ui->inhaleEdit->value()),
                            static_cast<Cycle>(ui->inhaleBeginEdit->value()),
                            static_cast<Cycle>(ui->inhaleEveryEdit->value()),
                            static_cast<TimeSec>(ui->inhaleDeltaEdit->value())
                    },
                    {
                            static_cast<TimeSec>(ui->pauseInhaleEdit->value()),
                            static_cast<Cycle>(ui->inhalePauseBeginEdit->value()),
                            static_cast<Cycle>(ui->inhalePauseEveryEdit->value()),
                            static_cast<TimeSec>(ui->inhalePauseDeltaEdit->value())
                    },
                    {
                            static_cast<TimeSec>(ui->exhaleEdit->value()),
                            static_cast<Cycle>(ui->exhaleBeginEdit->value()),
                            static_cast<Cycle>(ui->exhaleEveryEdit->value()),
                            static_cast<TimeSec>(ui->exhaleDeltaEdit->value())
                    },
                    {
                            static_cast<TimeSec>(ui->pauseExhaleEdit->value()),
                            static_cast<Cycle>(ui->exhalePauseBeginEdit->value()),
                            static_cast<Cycle>(ui->exhalePauseEveryEdit->value()),
                            static_cast<TimeSec>(ui->exhalePauseDeltaEdit->value())
                    },
                    static_cast<Cycle>(ui->restStartEdit->value()),
                    static_cast<Cycle>(ui->restDurEdit->value()),
                    static_cast<TimeSec>(ui->restInhaleEdit->value()),
                    static_cast<TimeSec>(ui->restPauseInhaleEdit->value()),
                    static_cast<TimeSec>(ui->restExhaleEdit->value()),
                    static_cast<TimeSec>(ui->restPauseExhaleEdit->value()),
                }
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

    void SettingsWindow::clearProfiles() {
        ui->profilesList->clear();
        setTextEditsDisabled(true);
    }

    void SettingsWindow::setTextEditsDisabled(bool disabled) {
        if(disabled){
            ui->nameEdit->setText("");

            ui->inhaleEdit->setValue(1);
            ui->exhaleEdit->setValue(1);
            ui->pauseInhaleEdit->setValue(1);
            ui->pauseExhaleEdit->setValue(1);

            ui->inhaleBeginEdit->setValue(0);
            ui->exhaleBeginEdit->setValue(0);
            ui->inhalePauseBeginEdit->setValue(0);
            ui->exhalePauseBeginEdit->setValue(0);

            ui->inhaleEveryEdit->setValue(0);
            ui->exhaleEveryEdit->setValue(0);
            ui->inhalePauseEveryEdit->setValue(0);
            ui->exhalePauseEveryEdit->setValue(0);

            ui->inhaleDeltaEdit->setValue(0);
            ui->exhaleDeltaEdit->setValue(0);
            ui->inhalePauseDeltaEdit->setValue(0);
            ui->exhalePauseDeltaEdit->setValue(0);

            ui->restStartEdit->setValue(0);
            ui->restDurEdit->setValue(0);
            ui->restInhaleEdit->setValue(1);
            ui->restPauseInhaleEdit->setValue(1);
            ui->restExhaleEdit->setValue(1);
            ui->restPauseExhaleEdit->setValue(1);
        }
        ui->nameEdit->setDisabled(disabled);

        ui->inhaleEdit->setDisabled(disabled);
        ui->exhaleEdit->setDisabled(disabled);
        ui->pauseInhaleEdit->setDisabled(disabled);
        ui->pauseExhaleEdit->setDisabled(disabled);

        ui->inhaleBeginEdit->setDisabled(disabled);
        ui->exhaleBeginEdit->setDisabled(disabled);
        ui->inhalePauseBeginEdit->setDisabled(disabled);
        ui->exhalePauseBeginEdit->setDisabled(disabled);

        ui->inhaleEveryEdit->setDisabled(disabled);
        ui->exhaleEveryEdit->setDisabled(disabled);
        ui->inhalePauseEveryEdit->setDisabled(disabled);
        ui->exhalePauseEveryEdit->setDisabled(disabled);

        ui->inhaleDeltaEdit->setDisabled(disabled);
        ui->exhaleDeltaEdit->setDisabled(disabled);
        ui->inhalePauseDeltaEdit->setDisabled(disabled);
        ui->exhalePauseDeltaEdit->setDisabled(disabled);

        ui->restStartEdit->setDisabled(disabled);
        ui->restDurEdit->setDisabled(disabled);
        ui->restInhaleEdit->setDisabled(disabled);
        ui->restPauseInhaleEdit->setDisabled(disabled);
        ui->restExhaleEdit->setDisabled(disabled);
        ui->restPauseExhaleEdit->setDisabled(disabled);
    }

    void SettingsWindow::setButtonDisabled(ISettingsWindow::ButtonId id, bool disabled) {
        switch(id){
            case ButtonId::ADD:
                ui->addBtn->setDisabled(disabled);
                break;
            case ButtonId::DELETE:
                ui->deleteButton->setDisabled(disabled);
                break;
            case ButtonId::MOVE_UP:
                ui->moveUpBtn->setDisabled(disabled);
                break;
            case ButtonId::MOVE_DOWN:
                ui->moveDownBtn->setDisabled(disabled);
                break;
            case ButtonId::SAVE:
                ui->saveButton->setDisabled(disabled);
                break;
            case ButtonId::CANCEL:
                ui->cancelButton->setDisabled(disabled);
                break;
        }
    }

    void SettingsWindow::showAddErrDialog(const std::string &name) {
        QMessageBox::warning(this, "Ошибка!", QString::fromStdString(std::string("Профиль с именем \"") + name + "\" уже существует"),
                             QMessageBox::Ok);
    }

    void SettingsWindow::resize(uint_fast32_t w, uint_fast32_t h) {
        QMainWindow::resize(static_cast<int>(w), static_cast<int>(h));
    }

    void SettingsWindow::resizeEvent(QResizeEvent *event) {
        QMainWindow::resizeEvent(event);
        _settingsWinListener.lock()->onResize(static_cast<uint_fast32_t>(event->size().width()), static_cast<uint_fast32_t>(event->size().height()));
    }
}