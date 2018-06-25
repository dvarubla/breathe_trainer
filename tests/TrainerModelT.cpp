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