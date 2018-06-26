#include <iostream>
#include <TrainProfiles/TrainProfilesModel.h>
#include <SettingsWindow/SettingsWindow.h>
#include <TrainProfiles/ProfileModelUpdater.h>
#include <TrainerWindow/Timer.h>
#include "init.h"
#include "TrainerWindow/TrainerModel.h"
#include "TrainerWindow/TrainerController.h"
#include "TrainerWindow/TrainerWindow.h"
#include "SettingsWindow/SettingsController.h"

namespace breathe_trainer {
    int run(const QApplication &app) {
        qRegisterMetaType<std::string>("std::string");
        qRegisterMetaType<uint_fast32_t>("uint_fast32_t");

        QFont font("Arial");
        font.setStyleHint(QFont::SansSerif);
        QApplication::setFont(font);

        std::vector<ITrainProfilesModel::ProfileWithName> profiles = {
                {
                        {{5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, 0, 0, 1, 0, 1, 0},
                        "Начальный"
                },
                {
                        {{6, 0, 0, 0}, {6, 0, 0, 0}, {6, 0, 0, 0}, {6, 0, 0, 0}, 0, 0, 1, 0, 1, 0},
                        "Продвинутый"
                },
                {
                        {{10, 0, 0, 0}, {10, 0, 0, 0}, {10, 0, 0, 0}, {10, 0, 0, 0}, 0, 0, 1, 0, 1, 0},
                        "Водолаз"
                }
        };
        auto trainerWin = std::make_shared<TrainerWindow>();
        auto settingsWin = std::make_shared<SettingsWindow>(&*trainerWin);

        auto trainProfModelMain = std::make_shared<TrainProfilesModel>(profiles);
        auto trainProfModelSettings = std::make_shared<TrainProfilesModel>(profiles);

        auto profileModelUpdater = std::make_shared<ProfileModelUpdater>(trainProfModelSettings, trainProfModelMain);
        auto settingsCtrl = std::make_shared<SettingsController>(settingsWin, trainProfModelSettings, profileModelUpdater);
        settingsWin->setSettingsWindowListener(settingsCtrl);

        auto timer = std::make_shared<Timer>(1000, 100);
        auto trainerModel = std::make_shared<TrainerModel>(timer, 100);
        timer->setListener(trainerModel);
        auto trainCtrl = std::make_shared<TrainerController>(trainerModel, trainerWin, trainProfModelMain, settingsCtrl);
        profileModelUpdater->setListener(trainCtrl);
        trainerModel->setModelListener(trainCtrl);
        trainerWin->setListener(trainCtrl);
        trainCtrl->init();
        return app.exec();
    }
}
