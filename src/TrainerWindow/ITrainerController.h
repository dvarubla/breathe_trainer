#pragma once

#include "ITrainerModelListener.h"
#include "ITrainerWindowListener.h"

namespace breathe_trainer {
    class ITrainerController: public ITrainerModelListener, public ITrainerWindowListener {
    };
}
