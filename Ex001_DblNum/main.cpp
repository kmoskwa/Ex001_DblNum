
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
  void iterateRange(quint64 start, quint64 end);
protected:
private:
  void initExamples(void);
  QString outNumber(quint64 value);

  QFile _outputFile;
  QMap<quint64, QString> _examples;
};

DblNum::DblNum(void)
{
  initExamples();
  _outputFile.setFileName("out.txt");
  _outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
}

DblNum::~DblNum(void)
{
  _outputFile.close();
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
  _examples[0x000fffffffffffff] = "2*-1022 * 2^-1022-52 == 2.2250738585072009 * 10^-308 (Max subnormal double)";
  _examples[0x0010000000000000] = "2^-1022 == 2.2250738585072014 * 10^-308 (Min normal positive double)";
  _examples[0x7fefffffffffffff] = "(1 + (1 * 2^-52)) × 2^1023  == 1.7976931348623157 × 10^308 (Max Double)";
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
  quint64 min = std::numeric_limits<quint64>::min();
  quint64 max = std::numeric_limits<quint64>::max();
  iterateRange(min, max);
}

void DblNum::iterateRange(quint64 start, quint64 end)
{
  QTextStream out(&_outputFile);
  for (quint64 i = start; i <= end; i++)
  {
    quint64 val = i;
    QString line = outNumber(val).toStdString().c_str();
    out << line << endl;
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
