#include <QtWidgets>
#include <QPlainTextEdit>
#include <QtGlobal>

#include "mdichild.h"
#include "faultpromptdialog.h"
#include "highlighter.h"
#include "syntaxrule.h"
#include "faultlinehighlighter.h"
#include "mainwindow.h"



MdiChild::MdiChild(QWidget *parent): QTextEdit(parent)
{
    qDebug() << "-1";
    setAttribute(Qt::WA_DeleteOnClose);   //delete this widget when the widget has accepted the close event
    isUntitled = true;

    lineNumberArea = new LineNumberArea(this);
    foldingWidget = new FoldingWidget(this);
    faultPrompt = new FaultPromptDialog(this);
    classInfoHash = new QHash<QString, ClassInfo>();

    syntaxIssueList = QList<ClassUndefinedSyntaxIssue> ();
    unspecifiedTypeIssueList = QList<ClassMemberUnspecifiedIssue> ();

    Highlighter = new Highlighter(this->document());

    globalVars = new QList<Variable>();   
    definedMethods = new QList<Method>();    
    Methods = new QList<Method>(); 

}

void MdiChild::newFile(QString fileName)
{
    qDebug() << "-2";
    static int sequenceNumber = 0;

    isUntitled = true;   
   
    if(fileName.isEmpty()){
        curFile = tr("document1.txt").arg(sequenceNumber++); 
    }else{
        curFile = fileName;
    }
    setWindowTitle(curFile + "[*]");

    connect(document(), &QTextDocument::contentsChanged,
            this, &MdiChild::documentWasModified);
    qDebug() << "-2";
}



