#include <iostream>
#include "init.h"
#include "TrainerWindow/TrainerModel.h"
#include "TrainerWindow/TrainerController.h"
#include "TrainerWindow/TrainerWindow.h"

namespace breathe_trainer {
    int run(const QApplication &app) {
        TrainProfile profile = {5, 5, 5, 5};
        auto model = std::make_shared<TrainerModel>(profile);
        auto win = std::make_shared<TrainerWindow>();
        auto ctrl = std::make_shared<TrainerController>(model, win);
        model->setModelListener(ctrl);
        ctrl->init();
        return app.exec();
    }
}
