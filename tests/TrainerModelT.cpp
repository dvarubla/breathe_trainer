#include <TrainerModelListenerMock.h>
#include <TrainerWindow/TrainerModel.h>
#include <TrainerWindow/Timer.h>
#include <future>

using breathe_trainer::TrainerModel;
using breathe_trainer::Timer;
using breathe_trainer::TrainProfile;
using breathe_trainer::TimeSec;
using std::make_shared;
using std::shared_ptr;

const TimeSec INH_TIME = 2;
const TimeSec EXH_TIME = 3;
const TimeSec PAUSE_AFTER_INH = 1;
const TimeSec PAUSE_AFTER_EXH = 2;

class TrainerModelTest: public ::testing::Test {
public:
    shared_ptr<TrainerModel> model;
    shared_ptr<Timer> timer;
    TrainProfile profile;
    shared_ptr<testing::NiceMock<TrainerModelListenerMock>> mock;
    TrainerModelTest(): profile{} {
        profile.inhalationTime.initial = INH_TIME;
        profile.exhalationTime.initial = EXH_TIME;
        profile.pauseTimeAfterInhalation.initial = PAUSE_AFTER_INH;
        profile.pauseTimeAfterExhalation.initial = PAUSE_AFTER_EXH;
        timer = make_shared<Timer>(1,1);
        model = make_shared<TrainerModel>(timer, 100);
        timer->setListener(model);
        mock = make_shared<testing::NiceMock<TrainerModelListenerMock>>();
        model->setModelListener(mock);
    }
    template <typename T>
    void attachListener(T &l){
        attachListenerAndSetProfile(l, profile);
    }

    template <typename T>
    void attachListenerAndSetProfile(T &l, const TrainProfile &profile){
        model->setProfile(profile);
        ON_CALL(*mock, onStateChanged()).WillByDefault(testing::Invoke(&l, &T::onStateChanged));
        l.model = model;
        model->start();
        l.threadPromise = std::make_shared<std::promise<void>>();
        l.mainPromise = std::make_shared<std::promise<void>>();
        l.threadPromise->get_future().get();
        l.mainPromise->set_value();
        model->stop();
    }
};

struct BaseListenerStruct{
    shared_ptr<std::promise<void>> threadPromise;
    shared_ptr<std::promise<void>> mainPromise;
    shared_ptr<TrainerModel> model;
    void end(){
        threadPromise->set_value();
        mainPromise->get_future().get();
    }
};

TEST_F(TrainerModelTest, Started){
    EXPECT_FALSE(model->isStarted());
    model->start();
    EXPECT_TRUE(model->isStarted());
    model->stop();
}

TEST_F(TrainerModelTest, TotalTime){
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            EXPECT_EQ(model->getTotalTime(), std::string("00:00:0") + std::to_string(sec)) << sec;
            if(sec == 4){
                end();
            }
            sec++;
        }
    } listener;
    EXPECT_CALL(*mock, onStateChanged()).Times(5);
    attachListener(listener);
}

TEST_F(TrainerModelTest, Phase){
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            sec++;
            if(sec <= INH_TIME){
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if(sec <= INH_TIME + PAUSE_AFTER_INH){
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::PAUSE) << sec;
            } else if(sec <= INH_TIME + PAUSE_AFTER_INH + EXH_TIME){
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::EXHALATION) << sec;
            } else if(sec <= INH_TIME + PAUSE_AFTER_INH + EXH_TIME + PAUSE_AFTER_EXH){
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::PAUSE) << sec;
            } else if(sec <= INH_TIME + PAUSE_AFTER_INH + EXH_TIME + PAUSE_AFTER_EXH + 1){
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else {
                end();
            }
        }
    } listener;
    EXPECT_CALL(*mock, onStateChanged()).Times(INH_TIME + PAUSE_AFTER_INH + EXH_TIME + PAUSE_AFTER_EXH + 1 + 1);
    attachListener(listener);
}

TEST_F(TrainerModelTest, PhaseTime){
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            static TimeSec curPhaseSec = INH_TIME;
            if(sec == INH_TIME){
                curPhaseSec = PAUSE_AFTER_INH;
            } else if(sec == INH_TIME + PAUSE_AFTER_INH){
                curPhaseSec = EXH_TIME;
            }
            EXPECT_EQ(model->getPhaseTime(), std::string("00:00:0") + std::to_string(curPhaseSec)) << sec;
            if(sec == INH_TIME + PAUSE_AFTER_INH + 1){
                end();
            }
            sec++;
            curPhaseSec--;
        }
    } listener;
    EXPECT_CALL(*mock, onStateChanged()).Times(INH_TIME + PAUSE_AFTER_INH + 2);
    attachListener(listener);
}

TEST_F(TrainerModelTest, PhaseWithIncrement){
    profile.inhalationTime.startCycle = 1;
    profile.inhalationTime.everyCycle = 2;
    profile.inhalationTime.delta = 1;
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            auto cycleTime = INH_TIME + PAUSE_AFTER_INH + EXH_TIME + PAUSE_AFTER_EXH;
            sec++;
            if (sec == cycleTime + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec == cycleTime + INH_TIME + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec == cycleTime * 3 + INH_TIME + 2) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec > cycleTime * 3 + INH_TIME + 2) {
                end();
            }
        }
    } listener;
    attachListener(listener);
}

TEST_F(TrainerModelTest, PhaseWithIncrement2){
    profile.inhalationTime.startCycle = 1;
    profile.inhalationTime.everyCycle = 0;
    profile.inhalationTime.delta = 5;
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            auto cycleTime = INH_TIME + PAUSE_AFTER_INH + EXH_TIME + PAUSE_AFTER_EXH;
            sec++;
            if (sec == cycleTime + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec == cycleTime + INH_TIME + 5) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec == cycleTime + (cycleTime + 5) * 7 + INH_TIME + 5) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION) << sec;
            } else if (sec > cycleTime + (cycleTime + 5) * 7 + INH_TIME + 5) {
                end();
            }
        }
    } listener;
    attachListener(listener);
}

TEST_F(TrainerModelTest, Rest){
    profile.exhalationTime.initial = 5;
    profile.inhalationTime.initial = 6;
    profile.pauseTimeAfterInhalation.initial = 2;
    profile.pauseTimeAfterExhalation.initial = 3;
    profile.restStart = 2;
    profile.restDur = 2;
    profile.restInhalationTime = 2;
    profile.restExhalationTime = 2;
    profile.restPauseTimeAfterInhalation = 1;
    profile.restPauseTimeAfterExhalation = 1;
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            static bool isRectActive = false;
            sec++;
            if (model->getCycleNum() == 3) {
                EXPECT_TRUE(model->isRestActive());
                isRectActive = true;
                sec = 0;
            } else if (isRectActive && sec == 2) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION);
            } else if (isRectActive && sec == 2 + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::PAUSE);
            } else if (isRectActive && sec == 2 + 1 + 2) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::EXHALATION);
            } else if (isRectActive && sec == 2 + 1 + 2 + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::PAUSE);
            } else if (isRectActive && sec == 2 + 1 + 2 + 2) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION);
            } else if (isRectActive && sec > 2 + 1 + 2 + 2) {
                end();
            }
        }
    } listener;
    attachListener(listener);
}

TEST_F(TrainerModelTest, AfterRest){
    profile.exhalationTime.initial = 5;
    profile.inhalationTime.initial = 6;
    profile.pauseTimeAfterInhalation.initial = 2;
    profile.pauseTimeAfterExhalation.initial = 3;
    profile.restStart = 2;
    profile.restDur = 2;
    profile.restInhalationTime = 2;
    profile.restExhalationTime = 2;
    profile.restPauseTimeAfterInhalation = 1;
    profile.restPauseTimeAfterExhalation = 1;
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            static bool afterRest = false;
            sec++;
            if (model->getCycleNum() == 5) {
                EXPECT_FALSE(model->isRestActive());
                afterRest = true;
                sec = 0;
            } else if (afterRest && sec == 5) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION);
            } else if (afterRest && sec > 5 + 1) {
                end();
            }
        }
    } listener;
    attachListener(listener);
}

TEST_F(TrainerModelTest, SecondRest){
    profile.exhalationTime.initial = 5;
    profile.inhalationTime.initial = 6;
    profile.pauseTimeAfterInhalation.initial = 2;
    profile.pauseTimeAfterExhalation.initial = 3;
    profile.restStart = 2;
    profile.restDur = 2;
    profile.restInhalationTime = 2;
    profile.restExhalationTime = 2;
    profile.restPauseTimeAfterInhalation = 1;
    profile.restPauseTimeAfterExhalation = 1;
    struct : public BaseListenerStruct{
        void onStateChanged(){
            static TimeSec sec = 0;
            static bool isRectActive = false;
            sec++;
            if (model->getCycleNum() == 7) {
                EXPECT_TRUE(model->isRestActive());
                isRectActive = true;
                sec = 0;
            } else if (isRectActive && sec == 2) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::INHALATION);
            } else if (isRectActive && sec == 2 + 1) {
                EXPECT_EQ(model->getPhase(), breathe_trainer::Phase::PAUSE);
            } else if (isRectActive && sec > 2 + 1 + 2 + 2) {
                end();
            }
        }
    } listener;
    attachListener(listener);
}