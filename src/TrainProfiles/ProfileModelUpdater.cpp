#include "ProfileModelUpdater.h"

namespace breathe_trainer{

    void ProfileModelUpdater::commit() {
        _finalM->profileList() = _tempM->profileList();
        _finalM->profileMap() = _tempM->profileMap();
    }

    void ProfileModelUpdater::rollback() {
        _tempM->profileList() = _finalM->profileList();
        _tempM->profileMap() = _finalM->profileMap();
    }

    ProfileModelUpdater::ProfileModelUpdater(const ITrainProfMCopyPtr &tempM, const ITrainProfMCopyPtr &finalM) : _tempM(tempM), _finalM(finalM){
    }
}
