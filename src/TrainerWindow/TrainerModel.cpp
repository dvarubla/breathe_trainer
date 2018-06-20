#include <iostream>
#include "TrainerModel.h"
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;

namespace breathe_trainer{
    void TrainerModel::start() {
        _threadStarted = true;
        _threadWorking = true;
        _timerThread = std::thread(&TrainerModel::thread_func, this);
    }

    void TrainerModel::stop() {
        _threadWorking = false;
        _timerThread.join();
    }

    TimeStr TrainerModel::getTotalTime() {
        return formatDuration<
                std::chrono::seconds,
                std::chrono::hours,
                std::chrono::minutes,
                std::chrono::seconds
        >(_timeElapsedSec);
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
        >(_curPhaseTotalSec - _curPhaseCurSec);
    }

    void TrainerModel::setModelListener(const ITMListenerWPtr &ptr) {
        _listenerPtr = ptr;
    }

    TrainerModel::TrainerModel(const TrainProfile &profile): _profile(profile), _threadStarted(false), _threadWorking(false) {
    }

    void TrainerModel::thread_func() {
        _startPhaseTime = _startTime = system_clock::now();
        _timeElapsedSec = seconds(0);
        _curPhase = InternalPhase::INHALATION;
        _curPhaseTotalSec = seconds(_profile.inhalationTime);
        notifyListenerState();
        while(_threadWorking) {
            std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_INTERVAL_MS));
            if(_threadWorking) {
                processTimerTick();
            }
        }
    }

    TrainerModel::~TrainerModel() {
        if(_threadStarted) {
            if(_timerThread.joinable()) {
                _threadWorking = false;
                _timerThread.join();
            }
        }
    }

    template<class DurationIn, class FirstDuration, class...RestDurations>
    std::string TrainerModel::formatDuration(DurationIn d)
    {
        auto val = duration_cast<FirstDuration>(d);
        std::string out = std::to_string(val.count());
        out = out.insert(0, STR_PART_LEN - out.length(), '0');
        if constexpr(sizeof...(RestDurations) > 0) {
            out += ":" + formatDuration<DurationIn, RestDurations...>(d - val);
        }
        return out;
    }

    void TrainerModel::processTimerTick() {
        auto curTime = system_clock::now();
        auto diffCurTime = curTime - _startTime;
        if(getPhase() != Phase::PAUSE){
            _curPhaseMS = duration_cast<milliseconds>(curTime - _startPhaseTime);
            _listenerPtr.lock()->onProgressChanged();
        }
        auto curTimeElapsedSec = duration_cast<seconds>(diffCurTime);
        if(curTimeElapsedSec.count() != _timeElapsedSec.count()){
            _timeElapsedSec = curTimeElapsedSec;
            notifyListenerState();
        }
    }

    void TrainerModel::setPhase() {
        auto curTime = system_clock::now();
        auto diffPhaseTime = curTime - _startPhaseTime;
        _curPhaseCurSec = duration_cast<seconds>(diffPhaseTime);
        if(_curPhaseTotalSec <= _curPhaseCurSec){
            _curPhaseCurSec = seconds(0);
            switch(_curPhase){
                case InternalPhase::INHALATION:
                    _curPhase = InternalPhase::PAUSE_AFTER_INHALATION;
                    _curPhaseTotalSec = seconds(_profile.pauseTimeAfterInhalation);
                    break;
                case InternalPhase::PAUSE_AFTER_INHALATION:
                    _curPhase = InternalPhase::EXHALATION;
                    _curPhaseTotalSec = seconds(_profile.exhalationTime);
                    break;
                case InternalPhase::EXHALATION:
                    _curPhase = InternalPhase::PAUSE_AFTER_EXHALATION;
                    _curPhaseTotalSec = seconds(_profile.pauseTimeAfterExhalation);
                    break;
                case InternalPhase::PAUSE_AFTER_EXHALATION:
                    _curPhase = InternalPhase::INHALATION;
                    _curPhaseTotalSec = seconds(_profile.inhalationTime);
                    break;
            }
            _startPhaseTime = curTime;
        }
    }

    void TrainerModel::notifyListenerState() {
        setPhase();
        _listenerPtr.lock()->onStateChanged();
    }

    double TrainerModel::getAmount() {
        return 1.0 * _curPhaseMS.count() / duration_cast<milliseconds>(_curPhaseTotalSec).count();
    }

    bool TrainerModel::isStarted() {
        return _threadWorking;
    }
}