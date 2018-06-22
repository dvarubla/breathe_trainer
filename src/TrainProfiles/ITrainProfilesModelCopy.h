#pragma once

#include <TrainerCommon.h>
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class ITrainProfilesModelCopy : public virtual ITrainProfilesModel {
    public:
        virtual ProfileMap& profileMap() = 0;
        virtual ProfileNameList& profileList() = 0;
    };

    typedef std::shared_ptr<ITrainProfilesModelCopy> ITrainProfMCopyPtr;
}
