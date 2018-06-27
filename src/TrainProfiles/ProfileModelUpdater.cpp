#include <iostream>
#include "ProfileModelUpdater.h"

namespace breathe_trainer{

    void ProfileModelUpdater::commit() {
        _finalM->copyModel(_tempM);
        _finalListener.lock()->onCommit();
    }

    void ProfileModelUpdater::rollback() {
        _tempM->copyModel(_finalM);
        _tempListener.lock()->onCommit();
    }

    ProfileModelUpdater::ProfileModelUpdater(
            const ITrainProfMCopyPtr &tempM, const ITrainProfMCopyPtr &finalM, const ISettingsPtr &settings
    ) : _tempM(tempM), _finalM(finalM), _settings(settings){
    }

    void ProfileModelUpdater::setFinalModelListener(const IProfMUpdListWPtr &listener) {
        _finalListener = listener;
    }

    void ProfileModelUpdater::restoreDefaults() {
        _finalM->init(_settings->getDefaultProfiles());
        _tempM->init(_settings->getDefaultProfiles());
        _finalListener.lock()->onCommit();
        _tempListener.lock()->onCommit();
    }

    void ProfileModelUpdater::setTempModelListener(const IProfMUpdListWPtr &listener) {
        _tempListener = listener;
    }
}
