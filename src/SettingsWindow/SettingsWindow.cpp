#include "SettingsWindow.h"

namespace breathe_trainer{
    SettingsWindow::SettingsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
    }

    void SettingsWindow::showWindow() {
        show();
    }

    SettingsWindow::~SettingsWindow() {
        delete ui;
    }
}