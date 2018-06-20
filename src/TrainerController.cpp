#include <cmath>
#include "TrainerController.h"

namespace breathe_trainer{
    TrainerController::TrainerController(const ITMPtr &model, const ITWPtr &window) :_model(model), _window(window) {
    }

    void TrainerController::onStateChanged() {
        _window->setTotalTime(_model->getTotalTime());
        _window->setPhaseTime(_model->getPhaseTime());
        switch(_model->getPhase()){
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
        _window->showWindow();
        _model->start();
    }

    void TrainerController::onProgressChanged() {
        auto amount = _model->getAmount();
        uint_fast32_t color;
        if(amount < 1. / NUM_INHALE_COLORS){
            color = inhaleColors[0];
        } else if(amount < 2 * 1. / NUM_INHALE_COLORS){
            color = inhaleColors[1];
        } else {
            color = inhaleColors[2];
        }
        if(_model->getPhase() == Phase::INHALATION) {
            _window->setAmountColor(amount, color);
        } else {
            _window->setAmountColor(1 - amount, color);
        }
    }
}