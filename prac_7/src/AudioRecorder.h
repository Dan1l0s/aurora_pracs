#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

// To use audio recording functions
// "QT += multimedia" must be added to the pro-file
// "qt5-qtmultimedia-plugin-mediaservice-gstmediacapture" should be added
// to the section "Requires" of the yaml-file
#include <QAudioRecorder>


// The successor of QAudioRecorder is used to pre-configure
// the quality and format of audio recording.
class AudioRecorder : public QAudioRecorder
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = 0);
};

#endif // AUDIORECORDER_H
