#include "init.h"

int main(int argc, char ** argv) {
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    return breathe_trainer::run(a);
}