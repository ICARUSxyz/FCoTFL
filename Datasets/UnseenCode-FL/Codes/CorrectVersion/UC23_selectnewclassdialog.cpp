#include "selectnewclassdialog.h"
#include "ui_selectnewclassdialog.h"

SelectNewClassDialog::SelectNewClassDialog(const QStringList& newItems, const QStringList& preItems, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectNewClassDialog)
{
    ui->setupUi(this);
    for (const QString &item : newItems) {
        QListWidgetItem *listItem = new QListWidgetItem(item);
        listItem->setCheckState(Qt::Unchecked);
        ui->newListWidget->addItem(listItem);
    }

    for(const QString& item : preItems){
        QListWidgetItem *listItem = new QListWidgetItem(item);
        //listItem->setCheckState(Qt::PartiallyChecked);
        ui->preListWidget->addItem(listItem);
    }
    connect(ui->okButton, &QPushButton::clicked, this, &SelectNewClassDialog::accept);
}

QStringList SelectNewClassDialog::checkedItems() const {
    QStringList items;
    for (int i = 0; i < ui->newListWidget->count(); ++i) {
        QListWidgetItem *item = ui->newListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            items.append(item->text());
        }
    }
    return items;
}

QStringList SelectNewClassDialog::uncheckedItems() const {
    QStringList items;
    for (int i = 0; i < ui->newListWidget->count(); ++i) {
        QListWidgetItem *item = ui->newListWidget->item(i);
        if (item->checkState() == Qt::Unchecked) {
            items.append(item->text());
        }
    }
    return items;
}

SelectNewClassDialog::~SelectNewClassDialog()
{
    delete ui;
}
