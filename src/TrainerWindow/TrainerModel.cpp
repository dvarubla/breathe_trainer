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
            _curPhaseMS = 0;
            _curPhaseCurSec = 0;
            switch(_curPhase){
                case InternalPhase::INHALATION:
                    _curPhase = InternalPhase::PAUSE_AFTER_INHALATION;
                    _curPhaseTotalSec = _curPauseTimeAfterInhalation;
                    break;
                case InternalPhase::PAUSE_AFTER_INHALATION:
                    _curPhase = InternalPhase::EXHALATION;
                    _curPhaseTotalSec = _curExhalationTime;
                    break;
                case InternalPhase::EXHALATION:
                    _curPhase = InternalPhase::PAUSE_AFTER_EXHALATION;
                    _curPhaseTotalSec = _curPauseTimeAfterExhalation;
                    break;
                case InternalPhase::PAUSE_AFTER_EXHALATION:
                    _curPhase = InternalPhase::INHALATION;
                    doAfterPhase(_profile.inhalationTime, _curInhalationTime);
                    doAfterPhase(_profile.exhalationTime, _curExhalationTime);
                    doAfterPhase(_profile.pauseTimeAfterInhalation, _curPauseTimeAfterInhalation);
                    doAfterPhase(_profile.pauseTimeAfterExhalation, _curPauseTimeAfterExhalation);
                    _curPhaseTotalSec = _curInhalationTime;
                    _cycleNum++;
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
        _curInhalationTime = profile.inhalationTime.initial;
        _curExhalationTime = profile.exhalationTime.initial;
        _curPauseTimeAfterInhalation = profile.pauseTimeAfterInhalation.initial;
        _curPauseTimeAfterExhalation = profile.pauseTimeAfterExhalation.initial;
    }

    uint_fast32_t TrainerModel::getCycleNum() {
        return _cycleNum;
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
        _cycleNum = 1;
        _curPhase = InternalPhase::INHALATION;
        _elapsedSec = 0;
        _curPhaseMS = 0;
        _curPhaseCurSec = 0;
        _curPhaseTotalSec = _curInhalationTime;
        notifyListenerState();
    }

    void TrainerModel::doAfterPhase(const TrainProfileTimeItem &item, TimeSec &curTime) {
        if(item.delta != 0){
            if(item.startCycle != 0 && _cycleNum >= item.startCycle){
                if(item.startCycle == _cycleNum || (item.everyCycle != 0 && (_cycleNum % item.everyCycle) == 0)){
                    curTime += item.delta;
                }
            }
        }
    }
}