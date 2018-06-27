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
#include <QtCore/QtPlugin>
#include <Settings/Settings.h>
#include <Settings/SettingsHelper.h>

#ifdef STATIC
Q_IMPORT_PLUGIN(QICOPlugin)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

namespace breathe_trainer {
    int run(const QApplication &app) {
        qRegisterMetaType<std::string>("std::string");
        qRegisterMetaType<uint_fast32_t>("uint_fast32_t");

        QFont font("Arial");
        font.setStyleHint(QFont::SansSerif);
        font.setPointSize(12);
        font.setStyleStrategy(QFont::PreferAntialias);
        QApplication::setFont(font);

        auto settings = std::make_shared<Settings>();

        auto trainerWin = std::make_shared<TrainerWindow>();
        auto settingsWin = std::make_shared<SettingsWindow>(&*trainerWin);

        auto profiles = settings->load();
        auto trainProfModelMain = std::make_shared<TrainProfilesModel>(profiles);
        auto trainProfModelSettings = std::make_shared<TrainProfilesModel>(profiles);

        auto settingsHelper = std::make_shared<SettingsHelper>(settings, trainProfModelMain);
        settings->setListener(settingsHelper);
        QObject::connect(&app, SIGNAL(aboutToQuit()), settings.get(), SLOT(onAppExit()));

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
