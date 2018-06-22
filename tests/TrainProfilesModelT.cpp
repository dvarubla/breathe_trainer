#include <gtest/gtest.h>
#include <TrainProfiles/TrainProfilesModel.h>

using breathe_trainer::TrainProfilesModel;
using breathe_trainer::ITrainProfilesModel;
using breathe_trainer::TrainProfile;
using breathe_trainer::TimeSec;
using std::make_shared;
using std::shared_ptr;

class TrainProfilesModelTest: public ::testing::Test {
public:
    shared_ptr<TrainProfilesModel> model;
    TrainProfilesModelTest(){
        std::vector<ITrainProfilesModel::ProfileWithName> profiles = {
                {{}, "pr1"},
                {{}, "pr2"}
        };
        profiles[0].profile.inhalationTime = 2;
        profiles[1].profile.inhalationTime = 10;
        model = make_shared<TrainProfilesModel>(profiles);
    }
};
TEST_F(TrainProfilesModelTest, ReadName){
    EXPECT_EQ(*(std::next(model->profileNamesBegin())), "pr2");
}

TEST_F(TrainProfilesModelTest, DeleteName){
    model->deleteProfile("pr1");
    EXPECT_EQ(*(model->profileNamesBegin()), "pr2");
}

TEST_F(TrainProfilesModelTest, ReadProfiles){
    EXPECT_EQ(model->getProfileByName("pr2").inhalationTime, 10);
}

TEST_F(TrainProfilesModelTest, ChangeProfileThanRead){
    TrainProfile t = {};
    t.inhalationTime = 7;
    model->setProfile("pr2", t, "pr2");
    EXPECT_EQ(model->getProfileByName("pr2").inhalationTime, 7);
}

TEST_F(TrainProfilesModelTest, ChangeProfileNameThanRead){
    TrainProfile t = {};
    t.inhalationTime = 7;
    model->setProfile("pr3", t, "pr2");
    EXPECT_EQ(model->getProfileByName("pr3").inhalationTime, 7);
}

