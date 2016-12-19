
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
  _examples[0x3ff0000000000000] = "1";
  _examples[0x3ff0000000000001] = "1.0000000000000002, the smallest number > 1";
  _examples[0x3ff0000000000002] = "1.0000000000000004";
  _examples[0x4000000000000000] = "2";
  _examples[0xc000000000000000] = "-2";
  _examples[0x8000000000000000] = "-0";
  _examples[0x0000000000000000] = "0";
  _examples[0x7ff0000000000000] = "Infinity";
  _examples[0xfff0000000000000] = "-Infinity";
  _examples[0x7fffffffffffffff] = "NaN";
  _examples[0x3fd5555555555555] = "1/3";
  _examples[0x4008000000000000] = "3 = (1+2^-1) * 2^1024-1023";
  _examples[0x4010000000000000] = "4 = 1 * 2^1025-1023";
  _examples[0x4014000000000000] = "5 = (1+2^-2) * 2^1025-1023";
  _examples[0x4018000000000000] = "6 = (1+2^-1) * 2^1025-1023";
  _examples[0x401c000000000000] = "7 = (1+2^-1+2^-2) * 2^1025-1023";
  _examples[0x0000000000000001] = "2^-1022-52 = 2^-1074 == 5 * 10^-324 (Min subnormal positive double)";
  _examples[0x000fffffffffffff] = "2*-1022 * 2^-1022-52 == 2.2250738585072009 * 10^-308 (Ma* subnormal double)";
  _examples[0x0010000000000000] = "2^-1022 == 2.2250738585072014 * 10^-308 (Min normal positive double)";
  _examples[0x7fefffffffffffff] = "(1 + (1 * 2^-52)) × 2^1023  == 1.7976931348623157 × 10^308 (Ma* Double)";
}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  qDebug() << "Test4";
  return a.exec();
}
