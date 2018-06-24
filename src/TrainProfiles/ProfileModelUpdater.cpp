#include <iostream>
#include "ProfileModelUpdater.h"

namespace breathe_trainer{

    void ProfileModelUpdater::commit() {
        _finalM->copyModel(_tempM);
        _listener.lock()->onCommit();
    }

    void ProfileModelUpdater::rollback() {
        _tempM->copyModel(_finalM);
    }

    ProfileModelUpdater::ProfileModelUpdater(const ITrainProfMCopyPtr &tempM, const ITrainProfMCopyPtr &finalM) : _tempM(tempM), _finalM(finalM){
    }

    void ProfileModelUpdater::setListener(const IProfMUpdListWPtr &listener) {
        _listener = listener;
    }
}
