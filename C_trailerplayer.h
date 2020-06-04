#ifndef C_TRAILERPLAYER_H
#define C_TRAILERPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include "videowidget.h"

namespace Ui {
class C_TrailerPlayer;
}

class C_TrailerPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit C_TrailerPlayer(QWidget *parent = nullptr);
    ~C_TrailerPlayer();

public slots:
    void setState(QMediaPlayer::State state);


signals:
    void play();
    void pause();
    void stop();

private:
    Ui::C_TrailerPlayer *ui;
/*    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
    QMediaPlayer *m_player = nullptr;
    QVideoWidget *m_videoWidget = nullptr;
    QMediaPlayer::State state() const;*/


private slots:
    void playClicked();
};

#endif // C_TRAILERPLAYER_H
