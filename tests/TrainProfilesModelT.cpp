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
        std::vector<breathe_trainer::ProfileWithName> profiles = {
                {{}, "pr1"},
                {{}, "pr2"},
                {{}, "pr3"},
                {{}, "pr4"}
        };
        profiles[0].profile.inhalationTime.initial = 2;
        profiles[1].profile.inhalationTime.initial = 10;
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
    EXPECT_EQ(model->getProfileByName("pr2").inhalationTime.initial, 10);
}

TEST_F(TrainProfilesModelTest, ChangeProfileThanRead){
    TrainProfile t = {};
    t.inhalationTime.initial = 7;
    model->setProfile("pr2", t, "pr2");
    EXPECT_EQ(model->getProfileByName("pr2").inhalationTime.initial, 7);
}

TEST_F(TrainProfilesModelTest, ChangeProfileNameThanRead){
    TrainProfile t = {};
    t.inhalationTime.initial = 7;
    model->setProfile("prX", t, "pr2");
    EXPECT_EQ(model->getProfileByName("prX").inhalationTime.initial, 7);
}

TEST_F(TrainProfilesModelTest, MoveDown){
    model->moveDown("pr3");
    EXPECT_EQ(*std::prev(model->profileNamesEnd()), "pr3");
    EXPECT_EQ(*std::prev(std::prev(model->profileNamesEnd())), "pr4");
}

TEST_F(TrainProfilesModelTest, MoveUp){
    model->moveUp("pr2");
    EXPECT_EQ(*model->profileNamesBegin(), "pr2");
    EXPECT_EQ(*std::next(model->profileNamesBegin()), "pr1");
}

TEST_F(TrainProfilesModelTest, Add){
    model->addProfile("prLast");
    EXPECT_EQ(*std::prev(model->profileNamesEnd()), "prLast");
}