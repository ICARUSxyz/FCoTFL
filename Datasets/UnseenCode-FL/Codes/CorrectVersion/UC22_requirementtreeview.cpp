#include "requirementtreeview.h"
#include "syntaxrule.h"
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QLabel>
#include "ui_cscrtooldialog.h"

// Get all class items from the tree
QList<QTreeWidgetItem*> BuildProFromSpecDialog::getClassItems() {
    QList<QTreeWidgetItem*> classItems;
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = treeWidget->topLevelItem(i);
        if (item->data(0, Qt::UserRole).toString() == classUserRole) {
            classItems.append(item);
        }
    }
    return classItems;
}

// Collect the tree structure as a QList of QHash values
QList<ClassInfo> BuildProFromSpecDialog::getClassStructure() {
    QList<ClassInfo> treeStructure;
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = treeWidget->topLevelItem(i);
        if(item->data(0, Qt::UserRole + 1).toBool() == true) continue;
        if(item->data(0, Qt::UserRole).toString() == classUserRole){
            ClassInfo info(item->text(0));
            for (int i = 0; i < item->childCount(); ++i) {
                QTreeWidgetItem* child = item->child(i);
                Method m(child->text(0), item->text(0));
                info.methods->append(m);
            }
            treeStructure.append(info);
        }else if (item->data(0, Qt::UserRole).toString() == globalFunctionUserRole){
            //independent function to do:
        }
    }
    return treeStructure;
}

CscrToolDialog::~CscrToolDialog()
{
    delete ui;  // Clean up the UI
}

void CscrToolDialog::onOkClicked()
{
    if (ui->loadButton->isChecked()) {
        emit loadBugReportFile(bugReportFilePath);
    } else if (ui->reviewButton->isChecked()) {
        emit reviewMethod(ui->methodComboBox->currentText());
    }
    accept();
}

void CscrToolDialog::handleOptionChanged(int id)
{
    if (id == 1) {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(0);
    } else if (id == 2) {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(1);
    }
}
