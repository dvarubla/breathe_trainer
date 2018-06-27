#pragma once

#include <Settings/ISettings.h>
#include "IProfileModelsUpdater.h"
#include "ITrainProfilesModelCopy.h"
#include "ISettingsRestorer.h"

namespace breathe_trainer {
    class ProfileModelUpdater: public IProfileModelsUpdater, public ISettingsRestorer {
    private:
        ITrainProfMCopyPtr _tempM;
        ITrainProfMCopyPtr _finalM;
        ISettingsPtr _settings;
        IProfMUpdListWPtr _tempListener;
        IProfMUpdListWPtr _finalListener;

    public:
        ProfileModelUpdater(const ITrainProfMCopyPtr &tempM, const ITrainProfMCopyPtr &finalM, const ISettingsPtr &settings);

        void commit() override;

        void rollback() override;

        void restoreDefaults() override;

        void setFinalModelListener(const IProfMUpdListWPtr &ptr);

        void setTempModelListener(const IProfMUpdListWPtr &listener);
    };
}
