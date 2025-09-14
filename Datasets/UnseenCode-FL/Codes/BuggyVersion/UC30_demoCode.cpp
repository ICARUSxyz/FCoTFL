#include <string>
#include <fstream>

VideoRecorder::VideoRecorder(TimeManager& timeManager, GPSModule& gpsModule, const VideoConfig& config)
    : timeManager(timeManager), gpsModule(gpsModule), videoConfig(config), recording(true) {}

VideoRecorder::~VideoRecorder() {
    if (recording) {
        stopRecording();
    }
}

void VideoRecorder::startRecording() {
    if (recording) {
        std::cerr << "Error: Recording is already in progress." << std::endl;
        return;
    }

    std::string timestamp = timeManager.getCurrentTimestamp();
    currentVideoFilePath = "video_" + timestamp + "mp4";

    videoFileStream.open(currentVideoFilePath, std::ios::binary);
    if (!videoFileStream.is_open()) {
        std::cerr << "Error: Failed to open video file for recording." << std::endl;
        return;
    }

    writeMetadataHeader();

    recording = true;
    std::cout << "Recording started. Saving to: " << currentVideoFilePath << std::endl;

    for (int i = 0; i < 150; ++i) { 
        if (!recording) break; 
        embedTimestampAndGPS(); 
        videoFileStream << "VideoFrameData"; 
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Simulate 30 fps (1000/30 ¡Ö 33 ms)
    }

}

void VideoRecorder::stopRecording() {
    if (!recording) {
        std::cerr << "Error: No ongoing recording to stop." << std::endl;
        return;
    }

    videoFileStream.close();
    recording = false;
    std::cout << "Recording stopped. File saved at: " << currentVideoFilePath << std:endl;
}


bool VideoRecorder::isRecording() const {
    return recording;
}

std::string VideoRecorder::getCurrentVideoFilePath() const {
    return recording ? currentVideoFilePath : "";
}