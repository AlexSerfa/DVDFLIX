#ifndef C_VIDEOLECTEUR_H
#define C_VIDEOLECTEUR_H

#include <QWidget>
#include <QMediaPlayer>
#include "videowidget.h"

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QMediaPlayer;
class QStatusBar;
class QLabel;
class QVideoProbe;
class QVideoWidget;
class QAudioProbe;
QT_END_NAMESPACE
namespace Ui {
class C_videoLecteur;
}

class C_videoLecteur : public QWidget
{
    Q_OBJECT

public:
    explicit C_videoLecteur(QWidget *parent = nullptr);
    ~C_videoLecteur();

public slots:
    void statusChanged(QMediaPlayer::MediaStatus status);
    void setState(QMediaPlayer::State state);
    void bufferingProgress(int progress);


    void displayErrorMessage();
signals:
    void play();
    void pause();
    void stop();
private:
    Ui::C_videoLecteur *ui;
    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
    QMediaPlayer *m_player = nullptr;
    QVideoWidget *m_videoWidget = nullptr;
    QMediaPlayer::State state() const;
    void updateDurationInfo(qint64 currentInfo);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void setStatusInfo(const QString &info);
    QVideoProbe *m_videoProbe = nullptr;
    QAudioProbe *m_audioProbe = nullptr;
    QStatusBar *m_statusBar = nullptr;
    QLabel *m_statusLabel = nullptr;
    QString m_trackInfo;
    QString m_statusInfo;
private slots:
    void playClicked();
    void on_btn_play_clicked();
};



#endif // C_VIDEOLECTEUR_H
