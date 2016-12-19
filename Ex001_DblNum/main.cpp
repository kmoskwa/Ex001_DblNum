
#include <QtCore/QCoreApplication>
#include <qdebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Test3";
    return a.exec();
}
