#include <iostream>
#include "Timer.h"
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;

namespace breathe_trainer{
    Timer::Timer(TimeMSec secondInterval, TimeMSec progressInterval)
            :_secondInterval(secondInterval), _progressInterval(progressInterval),
             _threadStarted(false), _threadWorking(false) {

    }

    void Timer::setListener(const ITimerListWPtr &timerListener) {
        _timerListener = timerListener;
    }

    void Timer::start() {
        _threadStarted = true;
        _threadWorking = true;
        _timerThread = std::thread(&Timer::threadFunc, this);
    }

    void Timer::stop() {
        _threadWorking = false;
        _timerThread.join();
    }

    void Timer::threadFunc() {
        _startTime = system_clock::now();
        _timeElapsedMSecForSeconds = milliseconds(0);
        _timeElapsedMSecForProgress = milliseconds(0);
        _timerListener.lock()->onStart();
        while(_threadWorking) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_progressInterval));
            if(_threadWorking) {
                milliseconds diff = duration_cast<milliseconds>(system_clock::now() - _startTime);
                milliseconds diffForProgress = diff - _timeElapsedMSecForProgress;
                if(diffForProgress >= _progressInterval){
                    _timerListener.lock()->onProgress();
                    _timeElapsedMSecForProgress += _progressInterval;
                }
                milliseconds diffForSeconds = diff - _timeElapsedMSecForSeconds;
                if(diffForSeconds >= _secondInterval){
                    _timerListener.lock()->onSecondPassed();
                    _timeElapsedMSecForSeconds += _secondInterval;
                }
            }
        }
    }

    Timer::~Timer() {
        if(_threadStarted) {
            if(_timerThread.joinable()) {
                _threadWorking = false;
                _timerThread.join();
            }
        }
    }

    bool Timer::isWorking() {
        return _threadWorking;
    }
}