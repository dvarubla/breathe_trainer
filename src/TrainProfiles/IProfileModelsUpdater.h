#pragma once

#include <memory>

namespace breathe_trainer {
    class IProfileModelsUpdater {
    public:
        virtual void commit() = 0;
        virtual void rollback() = 0;
    };

    typedef std::shared_ptr<IProfileModelsUpdater> IProfMUpdaterPtr;
}
