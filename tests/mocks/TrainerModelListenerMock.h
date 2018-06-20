#pragma once

#include <TrainerWindow/ITrainerModelListener.h>
#include <gmock/gmock.h>

using breathe_trainer::ITrainerModelListener;

class TrainerModelListenerMock: public ITrainerModelListener {
public:
    MOCK_METHOD0(onStateChanged, void());
    MOCK_METHOD0(onProgressChanged, void());
};
