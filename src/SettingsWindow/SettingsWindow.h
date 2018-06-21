#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "ISettingsWindow.h"
#include <ui_settings.h>

namespace breathe_trainer {
    class SettingsWindow : public QMainWindow, public ISettingsWindow {
    public:
        explicit SettingsWindow(QWidget *parent);

        ~SettingsWindow();

        void showWindow() override;

    private:
        Ui::SettingsWindow *ui;
    };
}