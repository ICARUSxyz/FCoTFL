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

    highlighter = new Highlighter(this->document());

    globalVars = new QList<Variable>();   //全局变量表
    definedMethods = new QList<Method>();    //已经有函数体的函数表，比如类内函数或全局函数
    Methods = new QList<Method>();   //调用的函数表

}

void MdiChild::newFile(QString fileName)
{
    qDebug() << "-2";
    static int sequenceNumber = 1;

    isUntitled = true;    //新建的文档没有被保存过
    //新建文件，curFile存的不是文件的完整路径，所以不推荐直接新建文件，最好是先新建项目
    if(fileName.isEmpty()){
        curFile = tr("document%1.txt").arg(sequenceNumber++);  //当前文件命名
    }else{
        curFile = fileName;
    }
    setWindowTitle(curFile + "[*]");

    connect(document(), &QTextDocument::contentsChanged,
            this, &MdiChild::documentWasModified);
    qDebug() << "-2";
}



