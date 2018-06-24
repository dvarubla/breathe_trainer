#pragma once

#include "ITrainerModelListener.h"
#include "ITrainerWindowListener.h"
#include <TrainProfiles/IProfileModelUpdaterListener.h>

namespace breathe_trainer {
    class ITrainerController: public ITrainerModelListener, public ITrainerWindowListener, public IProfileModelUpdaterListener {
    };
}
