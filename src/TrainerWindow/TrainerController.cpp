#include <cmath>
#include "TrainerController.h"

namespace breathe_trainer{
    TrainerController::TrainerController(const ITrainMPtr &trainModel, const ITrainWinPtr &window, const ITrainProfMPtr &trainProfModel)
            :_trainModel(trainModel), _trainProfModel(trainProfModel), _window(window) {
    }

    void TrainerController::onStateChanged() {
        _window->setTotalTime(_trainModel->getTotalTime());
        _window->setPhaseTime(_trainModel->getPhaseTime());
        switch(_trainModel->getPhase()){
            case Phase::INHALATION:
                _window->setPhase("Вдох");
                break;
            case Phase::PAUSE:
                _window->setPhase("Пауза");
                break;
            case Phase::EXHALATION:
                _window->setPhase("Выдох");
                break;
        }
    }

    void TrainerController::init() {
        clearWindow();
        _window->setStopButtonEnable(false);
        _window->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
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
    }

    void TrainerController::clearWindow() {
        _window->setPhase("");
        _window->setTotalTime("00:00:00");
        _window->setPhaseTime("00:00:00");
    }
}