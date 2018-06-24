#pragma once

#include <memory>

namespace breathe_trainer {
    class IProfileModelUpdaterListener {
    public:
        virtual void onCommit() = 0;
    };

    typedef std::weak_ptr<IProfileModelUpdaterListener> IProfMUpdListWPtr;
}
