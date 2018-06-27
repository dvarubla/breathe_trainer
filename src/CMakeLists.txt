project(breathe_trainer_main)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(DEFINED CROSS)
    set(QT_PREFIX "${CMAKE_SOURCE_DIR}/qt")
    set(CMAKE_PREFIX_PATH ${QT_PREFIX})
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

add_library(BreatheTrainerL STATIC ${CMAKE_SOURCE_DIR}/res/resources.qrc TrainerWindow/TrainerWindow.cpp TrainerWindow/TrainerWindow.h TrainerWindow/TimeMeter.cpp TrainerWindow/TimeMeter.h TrainerWindow/TrainerModel.cpp TrainerWindow/TrainerModel.h TrainerWindow/ITrainerModel.h TrainerCommon.h TrainerWindow/ITrainerModelListener.h TrainerWindow/TrainerController.cpp TrainerWindow/TrainerController.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindowListener.h TrainerWindow/ITrainerController.h TrainerWindow/ITrainerWindow.h init.cpp init.h TrainProfiles/TrainProfilesModel.cpp TrainProfiles/TrainProfilesModel.h TrainProfiles/ITrainProfilesModel.h TrainProfiles/TrainProfile.cpp TrainProfiles/TrainProfile.h SettingsWindow/SettingsWindow.cpp SettingsWindow/SettingsWindow.h SettingsWindow/ISettingsWindow.h SettingsWindow/ISettingsWindowListener.h SettingsWindow/ISettingsController.h SettingsWindow/SettingsController.cpp SettingsWindow/SettingsController.h TrainProfiles/ProfileListFragment.cpp TrainProfiles/ProfileListFragment.h TrainProfiles/IProfileModelsUpdater.h TrainProfiles/ProfileModelUpdater.cpp TrainProfiles/ProfileModelUpdater.h TrainProfiles/ITrainProfilesModelCopy.h TrainProfiles/ITrainProfilesModelEdit.h TrainProfiles/IProfileModelUpdaterListener.h TrainerWindow/Timer.cpp TrainerWindow/Timer.h TrainerWindow/ITimerListener.h TrainerWindow/ITimer.h Settings/ISettings.h Settings/Settings.cpp Settings/Settings.h Settings/ISettingsListener.h Settings/SettingsHelper.cpp Settings/SettingsHelper.h Settings/WindowSettingsModel.cpp Settings/WindowSettingsModel.h Settings/IWindowSettingsModel.h Settings/WidthHeight.h)

if(DEFINED CROSS)
    get_target_property(
            linked_libs
            Qt5::Widgets
            INTERFACE_LINK_LIBRARIES
    )
    set_target_properties(
            Qt5::Widgets
            PROPERTIES
            INTERFACE_LINK_LIBRARIES
            "-lmingw32 -L${QT_PREFIX}/lib -lqtmain -L${QT_PREFIX}/plugins/platforms -lqwindows -lwinspool -lshlwapi -lQt5PlatformSupport -lqtfreetype -L${QT_PREFIX}/plugins/imageformats -lqico -lQt5Widgets -lQt5Gui -lcomdlg32 -loleaut32 -limm32 -lwinmm -lglu32 -lopengl32 -lgdi32 -lqtharfbuzzng -lQt5Core -lole32 -luuid -lws2_32 -ladvapi32 -lshell32 -luser32 -lkernel32 -lmpr -lqtpcre"
    )
    target_compile_options(BreatheTrainerL PUBLIC -DSTATIC)
endif()

target_include_directories(BreatheTrainerL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
        BreatheTrainerL
        PUBLIC
        Qt5::Gui
        Qt5::Widgets
        pthread
)

add_executable(breathe_trainer main.cpp)
target_link_libraries(
        breathe_trainer
        BreatheTrainerL
)