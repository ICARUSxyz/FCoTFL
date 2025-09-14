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

void SuggestionDialog::setupUI() {
    setWindowTitle("Code Assistant");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QWidget *codeGenPage = new QWidget(this);
    QHBoxLayout *codeGenLayout = new QHBoxLayout(codeGenPage);

    codeGenLayout->addWidget(templateListCodeGen, 2);
    codeGenLayout->addWidget(editAreaCodeGen, 5);
    tabWidget->addTab(codeGenPage, "Code Generation");


    QWidget *bugFixPage = new QWidget(this);
    QHBoxLayout *bugFixLayout = new QHBoxLayout(bugFixPage);

    bugFixLayout->addWidget(templateListBugFix, 2);
    bugFixLayout->addWidget(editAreaBugFix, 5);
    tabWidget->addTab(bugFixPage, "Code Refinement");


    QWidget *annotationPage = new QWidget(this);
    QHBoxLayout *annotationLayout = new QHBoxLayout(annotationPage);

    annotationLayout->addWidget(templateListAnnotation, 2);
    annotationLayout->addWidget(editAreaAnnotation, 5);
    tabWidget->addTab(annotationPage, "Code Annotation");

   
    QVBoxLayout *resultLayout = new QVBoxLayout();

  
    QVBoxLayout *buttonAndResultLayout = new QVBoxLayout();
    buttonAndResultLayout->addWidget(generateButton, 1);
    buttonAndResultLayout->addWidget(generatedResultWidget, 4);

    resultLayout->addLayout(buttonAndResultLayout);

    mainLayout->addWidget(tabWidget, 3);
    mainLayout->addLayout(resultLayout, 8);
    setLayout(mainLayout);

 
    addContextMenu(templateListCodeGen, editAreaCodeGen);
    addContextMenu(templateListBugFix, editAreaBugFix);
    addContextMenu(templateListAnnotation, editAreaAnnotation);
}