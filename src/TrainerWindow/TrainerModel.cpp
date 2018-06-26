#include <iostream>
#include "TrainerModel.h"

namespace breathe_trainer{
    void TrainerModel::start() {
        _timer->start();
    }

    void TrainerModel::stop() {
        _timer->stop();
    }

    TimeStr TrainerModel::getTotalTime() {
        return formatDuration<
                std::chrono::seconds,
                std::chrono::hours,
                std::chrono::minutes,
                std::chrono::seconds
        >(std::chrono::seconds(_elapsedSec));
    }

    Phase TrainerModel::getPhase() {
        switch(_curPhase){
            case InternalPhase::INHALATION: return Phase::INHALATION;
            case InternalPhase::EXHALATION: return Phase::EXHALATION;
            default: return Phase::PAUSE;
        }
    }

    TimeStr TrainerModel::getPhaseTime() {
        return formatDuration<
                std::chrono::seconds,
                std::chrono::hours,
                std::chrono::minutes,
                std::chrono::seconds
        >(std::chrono::seconds(_curPhaseTotalSec - _curPhaseCurSec));
    }

    void TrainerModel::setModelListener(const ITrainMListWPtr &ptr) {
        _listenerPtr = ptr;
    }

    template<class DurationIn, class FirstDuration, class...RestDurations>
    std::string TrainerModel::formatDuration(DurationIn d)
    {
        auto val = std::chrono::duration_cast<FirstDuration>(d);
        std::string out = std::to_string(val.count());
        out = out.insert(0, STR_PART_LEN - out.length(), '0');
        if constexpr(sizeof...(RestDurations) > 0) {
            out += ":" + formatDuration<DurationIn, RestDurations...>(d - val);
        }
        return out;
    }

    void TrainerModel::setPhase() {
        if(_curPhaseTotalSec <= _curPhaseCurSec){
            if(getPhase() != Phase::PAUSE) {
                _curPhaseMS = _curPhaseTotalSec * 1000;
                _listenerPtr.lock()->onProgressChanged();
            }
            _curPhaseMS = 0;
            _curPhaseCurSec = 0;
            switch(_curPhase){
                case InternalPhase::INHALATION:
                    if(_curPauseTimeAfterInhalation != 0) {
                        _curPhase = InternalPhase::PAUSE_AFTER_INHALATION;
                        _curPhaseTotalSec = _curPauseTimeAfterInhalation;
                    } else {
                        _curPhase = InternalPhase::EXHALATION;
                        _curPhaseTotalSec = _curExhalationTime;
                    }
                    break;
                case InternalPhase::PAUSE_AFTER_INHALATION:
                    _curPhase = InternalPhase::EXHALATION;
                    _curPhaseTotalSec = _curExhalationTime;
                    break;
                case InternalPhase::EXHALATION:
                    if(_curPauseTimeAfterExhalation != 0) {
                        _curPhase = InternalPhase::PAUSE_AFTER_EXHALATION;
                        _curPhaseTotalSec = _curPauseTimeAfterExhalation;
                    } else {
                        doAfterPhase();
                        _curPhase = InternalPhase::INHALATION;
                        _curPhaseTotalSec = _curInhalationTime;
                    }
                    break;
                case InternalPhase::PAUSE_AFTER_EXHALATION:
                    doAfterPhase();
                    _curPhase = InternalPhase::INHALATION;
                    _curPhaseTotalSec = _curInhalationTime;
                    break;
            }
        }
    }

    void TrainerModel::notifyListenerState() {
        setPhase();
        _listenerPtr.lock()->onStateChanged();
    }

    double TrainerModel::getAmount() {
        return 1.0 * _curPhaseMS / (_curPhaseTotalSec * 1000);
    }

    bool TrainerModel::isStarted() {
        return _timer->isWorking();
    }

    void TrainerModel::setProfile(const TrainProfile &profile) {
        _profile = profile;
        setInitialValsFromProfile();
    }

    uint_fast32_t TrainerModel::getCycleNum() {
        return _totalCycleNum;
    }

    TrainerModel::TrainerModel(const ITimerPtr &timer, TimeMSec timerProgressInterval)
            : _timer(timer), _timerProgressInterval(timerProgressInterval){
    }

    void TrainerModel::onSecondPassed() {
        _elapsedSec++;
        _curPhaseCurSec++;
        notifyListenerState();
    }

    void TrainerModel::onProgress() {
        if(getPhase() != Phase::PAUSE){
            _curPhaseMS += _timerProgressInterval;
            _listenerPtr.lock()->onProgressChanged();
        }
    }

    void TrainerModel::onStart() {
        _totalCycleNum = 1;
        _periodCycleNum = 1;
        _curPhase = InternalPhase::INHALATION;
        _elapsedSec = 0;
        _curPhaseMS = 0;
        _curPhaseCurSec = 0;
        _curPhaseTotalSec = _curInhalationTime;
        _isRestActive = false;
        notifyListenerState();
    }

    void TrainerModel::addTimeAfterPhase(const TrainProfileTimeItem &item, TimeSec &curTime) {
        if(item.delta != 0){
            if(item.startCycle != 0 && _totalCycleNum >= item.startCycle){
                if(item.startCycle == _totalCycleNum || (item.everyCycle != 0 && (_periodCycleNum % item.everyCycle) == 0)){
                    curTime += item.delta;
                }
            }
        }
    }

    void TrainerModel::doAfterPhase() {
        if(!_isRestActive) {
            addTimeAfterPhase(_profile.inhalationTime, _curInhalationTime);
            addTimeAfterPhase(_profile.exhalationTime, _curExhalationTime);
            addTimeAfterPhase(_profile.pauseTimeAfterInhalation, _curPauseTimeAfterInhalation);
            addTimeAfterPhase(_profile.pauseTimeAfterExhalation, _curPauseTimeAfterExhalation);

            if(haveRest() && (_periodCycleNum == _profile.restStart)){
                _isRestActive = true;
                _restCycleNum = 0;
                _curInhalationTime = _profile.restInhalationTime;
                _curExhalationTime = _profile.restExhalationTime;
                _curPauseTimeAfterInhalation = _profile.restPauseTimeAfterInhalation;
                _curPauseTimeAfterExhalation = _profile.restPauseTimeAfterExhalation;
            }
        }

        _totalCycleNum++;
        _periodCycleNum++;

        if(_isRestActive){
            if(_restCycleNum == _profile.restDur){
                _isRestActive = false;
                _periodCycleNum = 1;
                setInitialValsFromProfile();
            } else {
                _restCycleNum++;
            }
        }
    }

    bool TrainerModel::isRestActive() {
        return _isRestActive;
    }

    void TrainerModel::setInitialValsFromProfile() {
        _curInhalationTime = _profile.inhalationTime.initial;
        _curExhalationTime = _profile.exhalationTime.initial;
        _curPauseTimeAfterInhalation = _profile.pauseTimeAfterInhalation.initial;
        _curPauseTimeAfterExhalation = _profile.pauseTimeAfterExhalation.initial;
    }

    uint_fast32_t TrainerModel::getPeriodCycleNum() {
        return _periodCycleNum;
    }

    bool TrainerModel::haveRest() {
        return _profile.restStart != 0 && _profile.restDur != 0;
    }
}