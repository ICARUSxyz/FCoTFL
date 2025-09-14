#include "chatgptclient.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>

ChatgptClient::ChatgptClient(QWidget *parent)
    : QWidget(parent), networkManager(new QNetworkAccessManager(this)) {

    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatgptClient::onReplyFinished);
}



void ChatgptClient::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response_data = reply->readAll();
        qDebug() << "Raw JSON Response:" << response_data;
        QJsonDocument responseDoc = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObj = responseDoc.object();  // 获取根对象
        QJsonArray choicesArray = jsonObj["choices"].toArray();  // 获取 "choices" 数组
        QJsonObject firstChoice = choicesArray[0].toObject();  // 取第一个元素
        QString chatGptReply = firstChoice["message"].toObject()["content"].toString();  // 获取"message"的"content"字段
        chatgptReply = "ChatGPT: " + chatGptReply;
    } else {
        chatgptReply = "Error: " + reply->errorString();
        qWarning() << "Network error occurred:" << reply->errorString();
        qDebug() << "SSL Lib version:" << QSslSocket::sslLibraryVersionString();
    }
    emit replyIsReady(chatgptReply);
    reply->deleteLater();
}

void ChatgptClient::sendUserMessage(const QString &value)
{
    userInput = value;
    QString userQuestion = userInput;

    qDebug() << "project directory: " << QCoreApplication::applicationDirPath();
    QDir currentDir(QCoreApplication::applicationDirPath());
    currentDir.cdUp(); // Navigate to the parent directory
    QString configFilePath = currentDir.path() + "/config/OpenAIkey.json";
    QFile file(configFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open openai key config file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QString apiKey = doc.object().value("api_key").toString();
    if (apiKey.isEmpty()) {
        qDebug() << "API key not found in the config file";
        return;
    }

    QNetworkRequest request(QUrl("https://api.openai.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());

    QJsonObject json;
    json["model"] = "gpt-4o-mini";
    QJsonArray messages;
    messages.append(QJsonObject{{"role", "user"}, {"content", userQuestion}});
    json["messages"] = messages;

    networkManager->post(request, QJsonDocument(json).toJson());

}

QString ChatgptClient::getChatgptReply() const
{
    return chatgptReply;
}
