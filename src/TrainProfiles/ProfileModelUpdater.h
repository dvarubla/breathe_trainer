#pragma once

#include "IProfileModelsUpdater.h"
#include "ITrainProfilesModelCopy.h"

namespace breathe_trainer {
    class ProfileModelUpdater: public IProfileModelsUpdater {
    private:
        ITrainProfMCopyPtr _tempM;
        ITrainProfMCopyPtr _finalM;
        IProfMUpdListWPtr _listener;

    public:
        ProfileModelUpdater(const ITrainProfMCopyPtr &tempM, const ITrainProfMCopyPtr &finalM);

        void commit() override;

        void rollback() override;

        void setListener(const IProfMUpdListWPtr &ptr) override;
    };
}
