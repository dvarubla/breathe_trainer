#pragma once

#include "TrainProfile.h"
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class ITrainProfilesModelEdit : public virtual ITrainProfilesModel{
    public:
        virtual bool setProfile(const std::string &str, const TrainProfile &prof, const std::string &oldStr) = 0;
        virtual bool moveDown(const std::string &str) = 0;
        virtual bool moveUp(const std::string &str) = 0;
        virtual bool addProfile(const std::string &name) = 0;
        virtual void deleteProfile(const std::string &str) = 0;
    };

    typedef std::shared_ptr<ITrainProfilesModelEdit> ITrainProfMEditPtr;
}
