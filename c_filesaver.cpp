#include "c_filesaver.h"
#include <QMutex>
#include <QFile>

const QString directoryBase= "d:/tempo68";

C_fileSaver::C_fileSaver()
{

}
bool C_fileSaver::saveFile(QString filename,QByteArray data){
    mutex.lock();
    bool result=false;
    QFile fichier;
    fichier.setFileName(filename);
    fichier.write(data);
    fichier.close();
    mutex.unlock();
    emit fileSaveFinished();
    return result;
}
