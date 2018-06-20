#include "init.h"

int main(int argc, char ** argv) {
    QApplication a(argc, argv);
    return breathe_trainer::run(a);
}