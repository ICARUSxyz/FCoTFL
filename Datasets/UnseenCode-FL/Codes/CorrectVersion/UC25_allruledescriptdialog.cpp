#include "allruledescriptdialog.h"
#include "ui_allruledescriptdialog.h"
#include "ruledescriptdialog.h"
#include "screenfactor.h"

AllRuleDescriptDialog::AllRuleDescriptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllRuleDescriptDialog)
{
    ui->setupUi(this);

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(showRuleDescript(QTableWidgetItem*)));

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(showRuleDescript(QTreeWidgetItem*,int)));
}

AllRuleDescriptDialog::~AllRuleDescriptDialog()
{
    delete ui;
}


void AllRuleDescriptDialog::showRuleDescript(QTreeWidgetItem*, int)  //int表示列号
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    ruleDescript->resize(factor.getScreenFactor() * ruleDescript->width(), factor.getScreenFactor() * ruleDescript->height());
    ruleDescript->show();
}

void AllRuleDescriptDialog::showRuleDescript(QTableWidgetItem*)
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    ruleDescript->resize(factor.getScreenFactor() * ruleDescript->width(), factor.getScreenFactor() * ruleDescript->height());
    ruleDescript->show();
}

