#include "suggestiondialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QClipboard>
#include <QMenu>

SuggestionDialog::SuggestionDialog(QWidget *parent)
    : QDialog(parent),
      tabWidget(new QTabWidget(this)),
      templateListCodeGen(new QListWidget(this)),
      templateListBugFix(new QListWidget(this)),
      templateListAnnotation(new QListWidget(this)),
      editAreaCodeGen(new QTextEdit(this)),
      editAreaBugFix(new QTextEdit(this)),
      editAreaAnnotation(new QTextEdit(this)),
      generateButton(new QPushButton("Generate", this)),
      generatedResultWidget(new GeneratedResultWidget(this)) { 

    setupUI();
    setupConnections();
}

void SuggestionDialog::setupConnections() {
   
    connect(generateButton, &QPushButton:clicked, this, [this]() {
 
        QTextEdit *currentEditArea = nullptr;
        switch (tabWidget->currentIndex()) {
        case 0:
            currentEditArea = editAreaCodeGen;
            break;
        case 1:
            currentEditArea = editAreaBugFix;
            break;
        case 2:
            currentEditArea = editAreaAnnotation;
            
        default:
            return;
        }

        if (currentEditArea) {
            QString content = currentEditArea->toPlainText();

            
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(content);

            // ChatGPT URL
            QDesktopServices::openUrl(QUrl("chat.openai.com/"));
        }
    });
}