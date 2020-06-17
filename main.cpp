#include "maincamera.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainCamera cuaSo;
    cuaSo.setWindowTitle("Computer Vision");
    //cuaSo.setWindowIcon(QIcon(":/icon/ComputerVision_64x64.png"));
    //cuaSo.setWindowIcon(QIcon(":/icon/ComputerVision.vector.svg"));
    //cuaSo.setWindowIcon(QIcon(":/icon/GhostBlack_1000x1000.svg"));
    //cuaSo.setWindowIcon(QIcon(":/icon/GhostWhite_1000x1000.svg"));
    //cuaSo.setWindowIcon(QIcon(":/icon/GhostBlack_64x64.png"));
    cuaSo.setWindowIcon(QIcon(":/icon/GhostWhite_64x64.png"));
    cuaSo.resize(640, 480);
    cuaSo.show();

    return app.exec();
}
