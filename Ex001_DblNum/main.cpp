
#include <QtCore/QCoreApplication>
#include <qdebug>
#include <qstring>
#include <qlist>


class DblNum
{
public:
DblNum(void);
virtual ~DblNum(void);
protected:
private:
  void initExamples(void);
  QMap<qlonglong, QString> _examples;
};

DblNum::DblNum(void)
{
}

DblNum::~DblNum(void)
{
}

void DblNum::initExamples(void)
{

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Test4";
    return a.exec();
}
