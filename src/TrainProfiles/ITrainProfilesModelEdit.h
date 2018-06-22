#pragma once

#include "TrainProfile.h"
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class ITrainProfilesModelEdit : public virtual ITrainProfilesModel{
    public:
        virtual void setProfile(const std::string &str, const TrainProfile &prof, const std::string &oldStr) = 0;
        virtual void deleteProfile(const std::string &str) = 0;
    };

    typedef std::shared_ptr<ITrainProfilesModelEdit> ITrainProfMEditPtr;
}
