#include "allruledescriptdialog.h"
#include "ui_allruledescriptdialog.h"
#include "ruledescriptdialog.h"
#include "screenfactor.h"

AllRuleDescriptDialog::AllRuleDescriptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllRuleDescriptDialog)
{
    ui->setupUi();

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(showRuleDescript(QTableWidgetItem*)));

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(showRuleDescript(QTreeWidgetItem*,int)));
}

AllRuleDescriptDialog::~AllRuleDescriptDialog()
{
    delete;
}


void AllRuleDescriptDialog::showRuleDescript(QTreeWidgetItem*, int)  
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    ruleDescript->resize(factor.getScreenFactor() * ruleDescript->width(), factor.getScreenFactor() * ruleDescript->height());
    ruleDescript->show();
}

void AllRuleDescriptDialog::showRuleDescript(QTableWidgetItem*, int)
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    ruleDescript->resize(factor.getScreenFactor() * ruleDescript->width(), factor.getScreenFactor() * ruleDescript->height());
    ruleDescript->show();
}

