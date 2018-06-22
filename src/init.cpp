#include <iostream>
#include <TrainProfiles/TrainProfilesModel.h>
#include <SettingsWindow/SettingsWindow.h>
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
                {{5, 5, 5, 5}, "Начальный"},
                {{6, 6, 6, 6}, "Продвинутый"},
                {{10, 10, 10, 10}, "Водолаз"}
        };
        auto trainerWin = std::make_shared<TrainerWindow>();
        auto settingsWin = std::make_shared<SettingsWindow>(&*trainerWin);

        auto trainProfModel = std::make_shared<TrainProfilesModel>(profiles);

        auto settingsCtrl = std::make_shared<SettingsController>(settingsWin, trainProfModel);

        auto trainerModel = std::make_shared<TrainerModel>();
        auto trainCtrl = std::make_shared<TrainerController>(trainerModel, trainerWin, trainProfModel, settingsCtrl);
        trainerModel->setModelListener(trainCtrl);
        trainerWin->setListener(trainCtrl);
        trainCtrl->init();
        return app.exec();
    }
}
