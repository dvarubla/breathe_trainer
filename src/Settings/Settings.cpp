#include "Settings.h"

namespace breathe_trainer{
    ProfileWithNameVect Settings::DEFAULT_SETTINGS = {
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

    WHMap Settings::DEFAULT_SIZES = {
            {std::string(MAIN_WINDOW_NAME), {600, 400}},
            {std::string(SETTINGS_WINDOW_NAME), {630, 400}}
    };


    void Settings::saveProfiles(const ProfileNameList &list, const ProfileMap &map) {
        _settings->clear();
        _settings->setValue("NumProfiles", static_cast<int>(list.size()));
        _settings->beginGroup("Profiles");
        uint_fast32_t i = 0;
        for (const auto &name : list) {
            TrainProfile profile = map.at(name).profile;
            _settings->beginGroup("Profile" + QString::number(i));
            _settings->setValue("Name", QString::fromStdString(name));
            _settings->setValue("InhalationTimeInitial", static_cast<int>(profile.inhalationTime.initial));
            _settings->setValue("InhalationTimeStart", static_cast<int>(profile.inhalationTime.startCycle));
            _settings->setValue("InhalationTimeEvery", static_cast<int>(profile.inhalationTime.everyCycle));
            _settings->setValue("InhalationTimeDelta", static_cast<int>(profile.inhalationTime.delta));

            _settings->setValue("PauseTimeAfterInhalationInitial", static_cast<int>(profile.pauseTimeAfterInhalation.initial));
            _settings->setValue("PauseTimeAfterInhalationStart", static_cast<int>(profile.pauseTimeAfterInhalation.startCycle));
            _settings->setValue("PauseTimeAfterInhalationEvery", static_cast<int>(profile.pauseTimeAfterInhalation.everyCycle));
            _settings->setValue("PauseTimeAfterInhalationDelta", static_cast<int>(profile.pauseTimeAfterInhalation.delta));

            _settings->setValue("ExhalationTimeInitial", static_cast<int>(profile.exhalationTime.initial));
            _settings->setValue("ExhalationTimeStart", static_cast<int>(profile.exhalationTime.startCycle));
            _settings->setValue("ExhalationTimeEvery", static_cast<int>(profile.exhalationTime.everyCycle));
            _settings->setValue("ExhalationTimeDelta", static_cast<int>(profile.exhalationTime.delta));

            _settings->setValue("PauseTimeAfterExhalationInitial", static_cast<int>(profile.pauseTimeAfterExhalation.initial));
            _settings->setValue("PauseTimeAfterExhalationStart", static_cast<int>(profile.pauseTimeAfterExhalation.startCycle));
            _settings->setValue("PauseTimeAfterExhalationEvery", static_cast<int>(profile.pauseTimeAfterExhalation.everyCycle));
            _settings->setValue("PauseTimeAfterExhalationDelta", static_cast<int>(profile.pauseTimeAfterExhalation.delta));

            _settings->setValue("RestStart", static_cast<int>(profile.restStart));
            _settings->setValue("RestDur", static_cast<int>(profile.restDur));
            _settings->setValue("RestInhalationTime", static_cast<int>(profile.restInhalationTime));
            _settings->setValue("RestPauseTimeAfterInhalation", static_cast<int>(profile.restPauseTimeAfterInhalation));
            _settings->setValue("RestExhalationTime", static_cast<int>(profile.restExhalationTime));
            _settings->setValue("RestPauseTimeAfterExhalation", static_cast<int>(profile.restPauseTimeAfterExhalation));
            _settings->endGroup();
            i++;
        }
        _settings->endGroup();
    }

    ProfileWithNameVect Settings::loadProfiles() {
        if(!_settings->contains("NumProfiles")){
            return DEFAULT_SETTINGS;
        } else {
            uint_fast32_t numProfiles = static_cast<uint_fast32_t>(_settings->value("NumProfiles").toInt());
            _settings->beginGroup("Profiles");
            ProfileWithNameVect vect;
            for(uint_fast32_t i = 0; i < numProfiles; i++){
                _settings->beginGroup("Profile" + QString::number(i));
                ProfileWithName pWN = {};
                pWN.name = _settings->value("Name").toString().toStdString();
                pWN.profile.inhalationTime.initial = static_cast<TimeSec>(_settings->value("InhalationTimeInitial").toInt());
                pWN.profile.inhalationTime.startCycle = static_cast<Cycle>(_settings->value("InhalationTimeStart").toInt());
                pWN.profile.inhalationTime.everyCycle = static_cast<Cycle>(_settings->value("InhalationTimeEvery").toInt());
                pWN.profile.inhalationTime.delta = static_cast<TimeSec>(_settings->value("InhalationTimeDelta").toInt());

                pWN.profile.pauseTimeAfterInhalation.initial = static_cast<TimeSec>(_settings->value("PauseTimeAfterInhalationInitial").toInt());
                pWN.profile.pauseTimeAfterInhalation.startCycle = static_cast<Cycle>(_settings->value("PauseTimeAfterInhalationStart").toInt());
                pWN.profile.pauseTimeAfterInhalation.everyCycle = static_cast<Cycle>(_settings->value("PauseTimeAfterInhalationEvery").toInt());
                pWN.profile.pauseTimeAfterInhalation.delta = static_cast<TimeSec>(_settings->value("PauseTimeAfterInhalationDelta").toInt());

                pWN.profile.exhalationTime.initial = static_cast<TimeSec>(_settings->value("ExhalationTimeInitial").toInt());
                pWN.profile.exhalationTime.startCycle = static_cast<Cycle>(_settings->value("ExhalationTimeStart").toInt());
                pWN.profile.exhalationTime.everyCycle = static_cast<Cycle>(_settings->value("ExhalationTimeEvery").toInt());
                pWN.profile.exhalationTime.delta = static_cast<TimeSec>(_settings->value("ExhalationTimeDelta").toInt());

                pWN.profile.pauseTimeAfterExhalation.initial = static_cast<TimeSec>(_settings->value("PauseTimeAfterExhalationInitial").toInt());
                pWN.profile.pauseTimeAfterExhalation.startCycle = static_cast<Cycle>(_settings->value("PauseTimeAfterExhalationStart").toInt());
                pWN.profile.pauseTimeAfterExhalation.everyCycle = static_cast<Cycle>(_settings->value("PauseTimeAfterExhalationEvery").toInt());
                pWN.profile.pauseTimeAfterExhalation.delta = static_cast<TimeSec>(_settings->value("PauseTimeAfterExhalationDelta").toInt());

                pWN.profile.restStart = static_cast<TimeSec>(_settings->value("RestStart").toInt());
                pWN.profile.restDur = static_cast<TimeSec>(_settings->value("RestDur").toInt());
                pWN.profile.restInhalationTime = static_cast<TimeSec>(_settings->value("RestInhalationTime").toInt());
                pWN.profile.restPauseTimeAfterInhalation = static_cast<TimeSec>(_settings->value("RestPauseTimeAfterInhalation").toInt());
                pWN.profile.restExhalationTime = static_cast<TimeSec>(_settings->value("RestExhalationTime").toInt());
                pWN.profile.restPauseTimeAfterExhalation = static_cast<TimeSec>(_settings->value("RestPauseTimeAfterExhalation").toInt());

                _settings->endGroup();

                vect.push_back(pWN);
            }
            _settings->endGroup();
            return vect;
        }
    }

    Settings::Settings() {
        _settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BreatheTrainer", "BreatheTrainer");

    }

    Settings::~Settings() {
        delete _settings;
    }

    void Settings::onAppExit() {
        _listener.lock()->onAppExit();
    }

    void Settings::setListener(const ISettListWPtr &listener) {
        _listener = listener;
    }

    void Settings::saveWindowData(const WHMap &map) {
        _settings->beginGroup(QString::fromStdString(std::string(MAIN_WINDOW_NAME)));
        _settings->setValue("Width", static_cast<int>(map.at(std::string(MAIN_WINDOW_NAME)).width));
        _settings->setValue("Height",  static_cast<int>(map.at(std::string(MAIN_WINDOW_NAME)).height));
        _settings->endGroup();
        _settings->beginGroup(QString::fromStdString(std::string(SETTINGS_WINDOW_NAME)));
        _settings->setValue("Width", static_cast<int>(map.at(std::string(SETTINGS_WINDOW_NAME)).width));
        _settings->setValue("Height",  static_cast<int>(map.at(std::string(SETTINGS_WINDOW_NAME)).height));
        _settings->endGroup();
    }

    WHMap Settings::loadWindowData() {
        WHMap res;
        _settings->beginGroup(QString::fromStdString(std::string(MAIN_WINDOW_NAME)));
        res.insert(std::make_pair<>(MAIN_WINDOW_NAME, WidthHeight{
            static_cast<uint_fast32_t>(_settings->value("Width", static_cast<int>(DEFAULT_SIZES[std::string(MAIN_WINDOW_NAME)].width)).toInt()),
            static_cast<uint_fast32_t>(_settings->value("Height", static_cast<int>(DEFAULT_SIZES[std::string(MAIN_WINDOW_NAME)].height)).toInt())
        }));
        _settings->endGroup();

        _settings->beginGroup(QString::fromStdString(std::string(SETTINGS_WINDOW_NAME)));
        res.insert(std::make_pair<>(SETTINGS_WINDOW_NAME, WidthHeight{
            static_cast<uint_fast32_t>(_settings->value("Width", static_cast<int>(DEFAULT_SIZES[std::string(SETTINGS_WINDOW_NAME)].width)).toInt()),
            static_cast<uint_fast32_t>(_settings->value("Height", static_cast<int>(DEFAULT_SIZES[std::string(SETTINGS_WINDOW_NAME)].height)).toInt())
        }));
        _settings->endGroup();
        return res;
    }
}