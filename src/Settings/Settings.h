#pragma once

#include <QtCore/QSettings>
#include "ISettings.h"
#include "ISettingsListener.h"

namespace breathe_trainer {
    class Settings : public QObject, public ISettings{
        Q_OBJECT
    private:
        static ProfileWithNameVect DEFAULT_SETTINGS;
        QSettings *_settings;
        ISettListWPtr _listener;
    public slots:
        void onAppExit();
    public:
        Settings();

        ~Settings();

        void save(const ProfileNameList &list, const ProfileMap &map) override;

        ProfileWithNameVect load() override;

        void setListener(const ISettListWPtr &listener);
    };
}