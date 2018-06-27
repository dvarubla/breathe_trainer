#pragma once

#include <QtCore/QSettings>
#include "ISettings.h"
#include "ISettingsListener.h"

namespace breathe_trainer {
    class Settings : public QObject, public ISettings{
        Q_OBJECT
    private:
        static ProfileWithNameVect DEFAULT_SETTINGS;
        static WHMap DEFAULT_SIZES;
        std::unique_ptr<QSettings> _settings;
        ISettListWPtr _listener;
    public slots:
        void onAppExit();
    public:
        Settings();

        void saveProfiles(const ProfileNameList &list, const ProfileMap &map) override;

        ProfileWithNameVect loadProfiles() override;

        void setListener(const ISettListWPtr &listener);

        void saveWindowData(const WHMap &map) override;

        WHMap loadWindowData() override;

        ProfileWithNameVect getDefaultProfiles() override;
    };
}