#include <iostream>
#include <TrainProfiles/TrainProfilesModel.h>
#include "init.h"
#include "TrainerWindow/TrainerModel.h"
#include "TrainerWindow/TrainerController.h"
#include "TrainerWindow/TrainerWindow.h"

namespace breathe_trainer {
    int run(const QApplication &app) {
        qRegisterMetaType<std::string>("std::string");
        qRegisterMetaType<uint_fast32_t>("uint_fast32_t");

        QFont font("Arial");
        font.setStyleHint(QFont::SansSerif);
        QApplication::setFont(font);

        std::vector<ITrainProfilesModel::ProfileWithName> profiles = {
                {{5, 5, 5, 5}, "Начальный"},
                {{6, 6, 6, 6}, "Продвинутый"}
        };

        auto trainProfModel = std::make_shared<TrainProfilesModel>(profiles);

        TrainProfile profile = {5, 5, 5, 5};
        auto trainerModel = std::make_shared<TrainerModel>();
        trainerModel->setProfile(profile);
        auto win = std::make_shared<TrainerWindow>();
        auto ctrl = std::make_shared<TrainerController>(trainerModel, win, trainProfModel);
        trainerModel->setModelListener(ctrl);
        win->setListener(ctrl);
        ctrl->init();
        return app.exec();
    }
}
