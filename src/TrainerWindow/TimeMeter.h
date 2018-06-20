#pragma once

#include <QtWidgets/QWidget>
#include "TrainerCommon.h"

namespace breathe_trainer {
    class TimeMeter : public QWidget{
        Q_OBJECT
    public:
    private:
        const static uint_fast32_t BORDER_COLOR = 0x888888;
        const static uint_fast32_t BG_COLOR = 0xFFFFFF;
        double _amount;
        uint_fast32_t _color;
    public:
        explicit TimeMeter(QWidget *parent = nullptr);
        void setAmountColor(double amount, uint_fast32_t color);
    protected:
        void paintEvent(QPaintEvent *event) override;
    };
}
