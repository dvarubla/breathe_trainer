#include <QtGui/QPainter>
#include "TimeMeter.h"

namespace breathe_trainer{
    void TimeMeter::paintEvent(QPaintEvent *) {
        QPainter painter(this);
        auto w = size().width();
        auto h = size().height();
        painter.fillRect(QRect(0, 0, w, h), QBrush(QColor(BG_COLOR)));
        painter.fillRect(
                QRect(0, static_cast<int>(h * (1 - _amount)), w, static_cast<int>(h * _amount)),
                QBrush(QColor(static_cast<QRgb>(_color)))
        );
        painter.setPen(QPen(QBrush(QColor(static_cast<QRgb>(BORDER_COLOR))), 2));
        painter.drawRect(0, 0, w, h);
    }

    TimeMeter::TimeMeter(QWidget *parent): QWidget(parent), _amount(1), _color(BG_COLOR) {

    }

    void TimeMeter::setAmountColor(double amount, uint_fast32_t color) {
        _amount = amount;
        _color = color;
        update();
    }
}
