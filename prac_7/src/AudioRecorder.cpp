#include "AudioRecorder.h"


AudioRecorder::AudioRecorder(QObject *parent) : QAudioRecorder(parent)
{
    // Quality and format of audio recording are configured here
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/PCM");
    audioSettings.setQuality(QMultimedia::HighQuality);
    this->setEncodingSettings(audioSettings);
    this->setContainerFormat("wav");
}
