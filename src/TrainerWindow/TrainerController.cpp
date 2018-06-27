#include <cmath>
#include "TrainerController.h"

namespace breathe_trainer{
    TrainerController::TrainerController(
            const ITrainMPtr &trainModel,
            const ITrainWinPtr &window,
            const ITrainProfMPtr &trainProfModel,
            const ISettCtrlPtr &settingsCtrl,
            const IWinSettMPtr &winSettModel,
            const ISettRestorerPtr &restorer
    )
            :_trainModel(trainModel), _trainProfModel(trainProfModel), _window(window),
             _settingsCtrl(settingsCtrl), _winSettModel(winSettModel), _restorer(restorer) {
        auto size = winSettModel->getSize(MAIN_WINDOW_NAME);
        _window->resize(size.width, size.height);
    }

    void TrainerController::onStateChanged() {
        _window->setTotalTime(_trainModel->getTotalTime());
        _window->setPhaseTime(_trainModel->getPhaseTime());
        std::string phaseStr;
        switch(_trainModel->getPhase()){
            case Phase::INHALATION:
                phaseStr = "Вдох";
                break;
            case Phase::PAUSE:
                phaseStr = "Пауза";
                break;
            case Phase::EXHALATION:
                phaseStr = "Выдох";
                break;
        }
        if(_trainModel->isRestActive()){
            phaseStr += " / Отдых";
        }
        _window->setPhase(phaseStr);
        if(_trainModel->haveRest()){
            _window->setCycleNum(std::to_string(_trainModel->getPeriodCycleNum()) + " (" + std::to_string(_trainModel->getCycleNum()) + ")");
        } else {
            _window->setCycleNum(std::to_string(_trainModel->getCycleNum()));
        }
    }

    void TrainerController::init() {
        clearWindow();
        _window->setStopButtonEnable(false);
        updateProfiles();
        _window->showWindow();
    }

    void TrainerController::onProgressChanged() {
        auto amount = _trainModel->getAmount();
        uint_fast32_t color;
        if(amount < 1. / NUM_INHALE_COLORS){
            color = inhaleColors[0];
        } else if(amount < 2 * 1. / NUM_INHALE_COLORS){
            color = inhaleColors[1];
        } else {
            color = inhaleColors[2];
        }
        if(_trainModel->getPhase() == Phase::INHALATION) {
            _window->setAmountColor(amount, color);
        } else {
            _window->setAmountColor(1 - amount, color);
        }
    }

    void TrainerController::onStartPressed() {
        _window->setStopButtonEnable(true);
        if(_trainModel->isStarted()) {
            _trainModel->stop();
        }
        _trainModel->setProfile(_trainProfModel->getProfileByName(_window->getSelectedProfileName()));
        _trainModel->start();
    }

    void TrainerController::onStopPressed() {
        _window->setStopButtonEnable(false);
        _trainModel->stop();
        _window->setPhase("");
        _window->setPhaseTime("00:00:00");
        _window->setAmountColor(0, 0);
        _window->setCycleNum("");
    }

    void TrainerController::clearWindow() {
        _window->setPhase("");
        _window->setTotalTime("00:00:00");
        _window->setPhaseTime("00:00:00");
        _window->setCycleNum("");
    }

    void TrainerController::onEditPressed() {
        _settingsCtrl->show();
    }

    void TrainerController::onCommit() {
        updateProfiles();
    }

    void TrainerController::updateProfiles() {
        if(_trainProfModel->numProfiles() == 0){
            _window->clearProfiles();
        } else {
            _window->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
        }
    }

    void TrainerController::onResize(uint_fast32_t w, uint_fast32_t h) {
        _winSettModel->saveSize(MAIN_WINDOW_NAME, {w, h});
    }

    void TrainerController::onRestoreActClicked() {
        if(_window->showConfirmRestoreDialog()) {
            _restorer->restoreDefaults();
        }
    }
}