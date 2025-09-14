#include "faultpromptdialog.h"
#include "ui_faultpromptdialog.h"
#include "ruledescriptdialog.h"
#include "screenfactor.h"
#include <QDebug>

void CustomButton::enterEvent(QEvent *event) {
    // Handle enter event for the button
    qDebug() << "Mouse entered the button!";
    QPushButton::enterEvent(event);  // Call base class implementation
    emit enterSignal();
}

void CustomButton::leaveEvent(QEvent *event){
    qDebug() << "Leave the button";
    QPushButton::leaveEvent(event);
    emit leaveSignal();
}



FaultPromptDialog::FaultPromptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaultPromptDialog)
{
//    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowFlags(windowFlags() & ~Qt::WindowTitleHint);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);
    connect(ui->detailButton, &QPushButton::clicked, this, &FaultPromptDialog::showRuleDescript);

//    CustomButton *fixButton = new CustomButton(this);
//    fixButton->setText("Quick fix");
//    ui->horizontalLayout->replaceWidget(ui->fixButton, fixButton);
//    delete ui->fixButton;

    connect(ui->fixButton, &QPushButton::clicked, this, &FaultPromptDialog::fixButtonClicked);
    //connect(fixButton, &CustomButton::enterSignal, this, &FaultPromptDialog::fixButtonEntered);
    connect(ui->fixButton, &QPushButton::released, this, &FaultPromptDialog::fixButtonReleased);
    connect(ui->unfixButton, &QPushButton::clicked, this, &FaultPromptDialog::unfixButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &FaultPromptDialog::okButtonClicked);
    //connect(fixButton, &CustomButton::leaveSignal, this, &FaultPromptDialog::fixButtonLeft);
}

FaultPromptDialog::~FaultPromptDialog()
{
    delete ui;
}

void FaultPromptDialog::showRuleDescript()
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    ruleDescript->resize(factor.getScreenFactor() * ruleDescript->width(), factor.getScreenFactor() * ruleDescript->height());
    ruleDescript->show();
}

void FaultPromptDialog::fixButtonClicked()
{
    emit clickedSignal();
}

void FaultPromptDialog::fixButtonEntered()
{
    emit enteredSignal();
}

void FaultPromptDialog::fixButtonReleased()
{
    emit releasedSignal();
}

void FaultPromptDialog::fixButtonLeft()
{
    emit leftSignal();
}

void FaultPromptDialog::unfixButtonClicked()
{
    emit unfixSignal();
}

void FaultPromptDialog::okButtonClicked()
{
    emit okclicked();
}
