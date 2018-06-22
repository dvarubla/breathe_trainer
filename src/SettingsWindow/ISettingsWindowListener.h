#pragma once

namespace breathe_trainer {
    class ISettingsWindowListener {
    public:
        virtual void onPositionChanged(const std::string &curStr) = 0;
    };

    typedef std::weak_ptr<ISettingsWindowListener> ISettWinListWPtr;
}
