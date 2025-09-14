#include "codeanalyzeconfigdialog.h"
#include "ui_codeanalyzeconfigdialog.h"
#include "managepropertysetdialog.h"
#include "mainwindow.h"
#include "ruledescriptdialog.h"
#include "screenfactor.h"

CodeAnalyzeConfigDialog::CodeAnalyzeConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CodeAnalyzeConfigDialog)
{
    ui->setupUi(this);
    m_parent = (MainWindow*)parentWidget();
    connect(ui->manageButton, &QPushButton::clicked, this, &CodeAnalyzeConfigDialog::managePropertySet);  //button的信号要转换，否则会出现no matching的错误
    //connect(ui->allRuleDescriptAct, &QAction::triggered, this, &MainWindow::showAllRuleDescript);
    connect(ui->ruleTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(showRuleDescript(QTreeWidgetItem*,int)));

    connect(ui->startAnalysisButton, &QPushButton::clicked, this, &CodeAnalyzeConfigDialog::startAnalysis);

    //设置checkableCombobox，这里只是示例，没有连接信号和槽的实现
    this->Model = new QStandardItemModel;

    this->Item1 = new QStandardItem;
    this->Item1->setText("All Files");
    this->Item1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    this->Item1->setData(Qt::Unchecked, Qt::CheckStateRole);

    this->Item2 = new QStandardItem;
    this->Item2->setText("File1");
    this->Item2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    this->Item2->setData(Qt::Unchecked, Qt::CheckStateRole);

    //connect(this->Model, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));

    this->Model->insertRow(0, this->Item1);
    this->Model->insertRow(1, this->Item2);

    this->Items.push_back(this->Item1);
    this->Items.push_back(this->Item2);

    ui->fileSelectBox->setModel(this->Model);

    //std::cout << comboBox->model()->rowCount() << " rows after." << std::endl;
}

CodeAnalyzeConfigDialog::~CodeAnalyzeConfigDialog()
{
    delete ui;
}

void CodeAnalyzeConfigDialog::managePropertySet()
{
    ManagePropertySetDialog* manageSet = new ManagePropertySetDialog(this);
    ScreenFactor factor;
    auto screenFactor = factor.getScreenFactor();
    manageSet->resize(manageSet->width() * screenFactor, manageSet->height() * screenFactor);
    manageSet->setModal(true);
    manageSet->show();
}

void CodeAnalyzeConfigDialog::showRuleDescript(QTreeWidgetItem*, int)
{
    RuleDescriptDialog *ruleDescript = new RuleDescriptDialog(this);
    ScreenFactor factor;
    auto screenFactor = factor.getScreenFactor();
    ruleDescript->resize(ruleDescript->width() * screenFactor, ruleDescript->height() * screenFactor);
    ruleDescript->show();
}

void CodeAnalyzeConfigDialog::startAnalysis()
{
    accept();
}
