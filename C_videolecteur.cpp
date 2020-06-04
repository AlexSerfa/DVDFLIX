#include "C_videolecteur.h"
#include "ui_C_videolecteur.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>
C_videoLecteur::C_videoLecteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_videoLecteur)
{
      m_player = new QMediaPlayer(this);
       m_player->setAudioRole(QAudio::VideoRole);
       m_videoWidget = new VideoWidget(this);
       m_player->setVideoOutput(m_videoWidget);
       QBoxLayout *displayLayout = new QHBoxLayout;
       displayLayout->addWidget(m_videoWidget, 2);


       QBoxLayout *layout = new QVBoxLayout;
       layout->addLayout(displayLayout);
      // QHBoxLayout *hLayout = new QHBoxLayout;
      // hLayout->addWidget(m_slider);
      // hLayout->addWidget(m_labelDuration);
       //layout->addLayout(hLayout);
       //layout->addLayout(controlLayout);
#if defined(Q_OS_QNX)
    // On QNX, the main window doesn't have a title bar (or any other decorations).
    // Create a status bar for the status information instead.
    m_statusLabel = new QLabel;
    m_statusBar = new QStatusBar;
    m_statusBar->addPermanentWidget(m_statusLabel);
    m_statusBar->setSizeGripEnabled(false); // Without mouse grabbing, it doesn't work very well.
    layout->addWidget(m_statusBar);
#endif
    setLayout(layout);
    ui->setupUi(this);
}

C_videoLecteur::~C_videoLecteur()
{
    delete ui;
}

void C_videoLecteur::playClicked()
{

}

QMediaPlayer::State C_videoLecteur::state() const
{
    return m_playerState;
}

void  C_videoLecteur::setState(QMediaPlayer::State state)
{
    if (state != m_playerState) {
        m_playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            ui->btn_stop->setEnabled(false);
            ui->btn_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            ui->btn_stop->setEnabled(true);
            ui->btn_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            ui->btn_stop->setEnabled(true);
            ui->btn_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }

}

void C_videoLecteur::statusChanged(QMediaPlayer::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
        setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia:
        setStatusInfo(tr("Loading..."));
        break;
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
        setStatusInfo(tr("Buffering %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::StalledMedia:
        setStatusInfo(tr("Stalled %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::EndOfMedia:
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
        displayErrorMessage();
        break;
    }
}
void C_videoLecteur::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
        status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}
void C_videoLecteur::bufferingProgress(int progress)
{
    if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
        setStatusInfo(tr("Stalled %1%").arg(progress));
    else
        setStatusInfo(tr("Buffering %1%").arg(progress));
}


void C_videoLecteur::displayErrorMessage()
{
    setStatusInfo(m_player->errorString());
}
void C_videoLecteur::setStatusInfo(const QString &info)
{
    m_statusInfo = info;

    if (m_statusBar) {
        m_statusBar->showMessage(m_trackInfo);
        m_statusLabel->setText(m_statusInfo);
    } else {
        if (!m_statusInfo.isEmpty())
            setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
        else
            setWindowTitle(m_trackInfo);
    }
}

void C_videoLecteur::on_btn_play_clicked()
{
    m_player->play();
}
