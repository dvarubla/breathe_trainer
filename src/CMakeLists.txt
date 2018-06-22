project(breathe_trainer_main)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Svg)

add_library(BreatheTrainerL STATIC ${CMAKE_SOURCE_DIR}/res/resources.qrc TrainerWindow/TrainerWindow.cpp TrainerWindow/TrainerWindow.h TrainerWindow/TimeMeter.cpp TrainerWindow/TimeMeter.h TrainerWindow/TrainerModel.cpp TrainerWindow/TrainerModel.h TrainerWindow/ITrainerModel.h TrainerCommon.h TrainerWindow/ITrainerModelListener.h TrainerWindow/TrainerController.cpp TrainerWindow/TrainerController.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindowListener.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindow.h init.cpp init.h TrainProfiles/TrainProfilesModel.cpp TrainProfiles/TrainProfilesModel.h TrainProfiles/ITrainProfilesModel.h TrainProfiles/TrainProfile.cpp TrainProfiles/TrainProfile.h SettingsWindow/SettingsWindow.cpp SettingsWindow/SettingsWindow.h SettingsWindow/ISettingsWindow.h SettingsWindow/ISettingsWindowListener.h SettingsWindow/ISettingsController.h SettingsWindow/SettingsController.cpp SettingsWindow/SettingsController.h TrainProfiles/ProfileListFragment.cpp TrainProfiles/ProfileListFragment.h)
target_include_directories(BreatheTrainerL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
        BreatheTrainerL
        PUBLIC
        Qt5::Widgets
        Qt5::Gui
        Qt5::Svg
        pthread
)

add_executable(breathe_trainer main.cpp)
target_link_libraries(
        breathe_trainer
        BreatheTrainerL
)