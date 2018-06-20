project(breathe_trainer_main)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)

add_library(BreatheTrainerL STATIC TrainerWindow.cpp TrainerWindow.h TimeMeter.cpp TimeMeter.h TrainerModel.cpp TrainerModel.h ITrainerModel.h TrainProfile.cpp TrainProfile.h TrainerCommon.h ITrainerModelListener.h TrainerController.cpp TrainerController.h ITrainerController.h ITrainerWindowListener.h ITrainerController.h ITrainerWindow.h init.cpp init.h)
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