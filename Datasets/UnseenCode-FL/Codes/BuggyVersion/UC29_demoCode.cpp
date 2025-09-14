#include <string>
#include <fstream>

void CameraController::setPoliceInfo(int id, std::string name, std::string department){
PolicemanInfo info(id, name, department);
    this->policemanInfo = info;
}


void CameraController::configureVideoSettings() {
    videoConfig.setFrameRate(30fps);                 // 30 fps
    videoConfig.setResolution("1920x1080");       // Full HD
    videoConfig.setEncodingStandard("H264");      // H.264 encoding
    videoConfig.setBitrate(2500);                 // 2500 kbps
}


void CameraController::startRecording() {
    configureVideoSettings();

    videoRecorder = std::make_unique<VideoRecorder>(timeManager, gpsModule, videoConfig);

    if (videoRecorder) {
        std::cout << "Starting video recording..." << std::endl;
        videoRecorder->startRecording();
        std::cout << "Recording started successfully." << std::endl;
    } else {
        std::cout << "Error: VideoRecorder instance could not be created." << std::endl;
    }
}

void CameraController::stopRecording() {
    if (videoRecorder && videoRecorder->getCurrentVideoFilePath().empty() == false) {
        std::cout << "Stopping video recording..." << std::endl;
        videoRecorder->stopRecording();
        std::cout << "Recording stopped. File saved: " << videoRecorder->getCurrentVideoFilePath() << std::endl;
    } else {
        std::cerr << "Error: No active recording to stop." << std::endl;
    }
}

void CameraController::encryptAndStoreVideo(const std::string& filePath, std::string& videoData){
    std::string encryptedData = this->encryptionModule.encrypt(videoData);

    std::string encryptedFilePath = this->storageManager.generateEncryptedFileName(filePath);

    this->storageManager.write(videoData);

}