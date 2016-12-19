
#include <iostream>

#include <QtCore/QCoreApplication>
#include <qdebug>
#include <qstring>
#include <qlist>
#include <QFile>

//extern ostream cout;


class DblNum
{
public:
  DblNum(void);
  virtual ~DblNum(void);
  void iterateExamples(void);
  void iterateAll(void);
protected:
private:
  void initExamples(void);
  QFile outputFile;
  QString outNumber(quint64 value);
  QMap<quint64, QString> _examples;
};

DblNum::DblNum(void)
{
  initExamples();
  outputFile.setFileName("out.txt");
  outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
}

DblNum::~DblNum(void)
{
  outputFile.close();
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

QString DblNum::outNumber(quint64 value)
{
  union representation
  {
    double  dblRepresentation;
    quint64 bitRepresentation;
  } repr;
  QString out;
  repr.bitRepresentation = value;
  double dblNum = repr.dblRepresentation;
  QString hexRepresentation = QString("0x%1").arg(value, 16, 16, QChar('0')).toUpper();
  QString doubleRepresentation = QVariant(dblNum).toString();
  QString comment;
  if (true == _examples.contains(value))
  {
    comment = _examples[value];
  }
  out = QString("%1\t%2\t%3").arg(hexRepresentation).arg(doubleRepresentation).arg(comment);
  return out;
}

void DblNum::iterateAll(void)
{
  QTextStream out(&outputFile);
  quint64 min = std::numeric_limits<quint64>::min();
  quint64 max = std::numeric_limits<quint64>::max();
  for (quint64 i = min; i <= max; i++)
  //for (quint64 i = min; i <= 100; i++)
  {
    quint64 val = i;
    QString line = outNumber(val).toStdString().c_str();
    out << line << endl;
    //qint64 a = i % 0x1000;
    if ((i % 0x10000) == 0)
    {
      qDebug() << line;
    }
  }
}

void DblNum::iterateExamples(void)
{
  QMapIterator<quint64, QString> i(_examples);
  while (i.hasNext())
  {
    quint64 val = i.next().key();
    //qDebug() << outNumber(val);
  }
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  DblNum dblNum;
  dblNum.iterateAll();
  return a.exec();
}
