#ifndef C_FILESAVER_H
#define C_FILESAVER_H

#include <QObject>
#include <QMutex>

class C_fileSaver:public QObject
{
    Q_OBJECT
public:
    C_fileSaver();
    bool saveFile(QString filename, QByteArray data);

private:
    QMutex mutex;
signals:
   void fileSaveFinished();
};

#endif // C_FILESAVER_H
