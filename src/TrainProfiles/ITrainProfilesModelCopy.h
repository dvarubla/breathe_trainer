#pragma once

#include <TrainerCommon.h>
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class ITrainProfilesModelCopy;
    typedef std::shared_ptr<ITrainProfilesModelCopy> ITrainProfMCopyPtr;

    class ITrainProfilesModelCopy : public virtual ITrainProfilesModel {
    public:
        virtual ProfileMap& profileMap() = 0;
        virtual ProfileNameList& profileList() = 0;
        virtual void copyModel(const ITrainProfMCopyPtr &other) = 0;
        virtual void init(const ProfileWithNameVect &vector) = 0;
    };
}
