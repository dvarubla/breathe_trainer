#pragma once

#include "TrainProfile.h"
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class ITrainProfilesModelEdit : public virtual ITrainProfilesModel{
    public:
        virtual void setProfile(const std::string &str, const TrainProfile &prof) = 0;
    };
}
