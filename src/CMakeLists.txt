project(breathe_trainer_main)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)

add_library(BreatheTrainerL STATIC TrainerWindow/TrainerWindow.cpp TrainerWindow/TrainerWindow.h TrainerWindow/TimeMeter.cpp TrainerWindow/TimeMeter.h TrainerWindow/TrainerModel.cpp TrainerWindow/TrainerModel.h TrainerWindow/ITrainerModel.h TrainProfile.cpp TrainProfile.h TrainerCommon.h TrainerWindow/ITrainerModelListener.h TrainerWindow/TrainerController.cpp TrainerWindow/TrainerController.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindowListener.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindow.h init.cpp init.h)
target_include_directories(BreatheTrainerL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
        BreatheTrainerL
        PUBLIC
        Qt5::Widgets
        Qt5::Gui
        pthread
)

add_executable(breathe_trainer main.cpp)
target_link_libraries(
        breathe_trainer
        BreatheTrainerL
)