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

RequirementTreeView::RequirementTreeView(QWidget *parent) : QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &RequirementTreeView::customContextMenuRequested, this, &RequirementTreeView::showContextMenu);
}

void RequirementTreeView::showContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        QMenu menu(this);
        QAction *action1 = menu.addAction("Complete the Requirement");

        QAction *selectedAction = menu.exec(viewport()->mapToGlobal(pos));
        if (selectedAction = action1) {
     
            emit complete(index);
        }
    }
}

// Add items from QStringList
void BuildProFromSpecDialog::addItemsFromStringList(const QStringList& stringList) {
    existingClassList = stringList;
    for (const QString& str : stringList) {
        QTreeWidgetItem* funcItem = new QTreeWidgetItem(treeWidget);
        funcItem->setText(0, str);
        funcItem->setIcon(0, QIcon(":/images/toolbar_images/class.svg"));
        funcItem->setData(0, Qt::UserRole, classUserRole);
        funcItem->setData(0, Qt::UserRole + 1, true);  // Mark as non-modifiable (from QStringList)
    }
}

// Check if the item is from QStringList
bool BuildProFromSpecDialog::isItemFromExistingClassList(QTreeWidgetItem* item) {
    return item->data(0, Qt::UserRole - 1).toBool();
}

// Demote the selected item to a function root
void BuildProFromSpecDialog::demoteToIndependentFunction() {
    QTreeWidgetItem* currentItem = treeWidget->currentItem();
    if (!currentItem || isItemFromExistingClassList(currentItem)) {
        return;  // Do nothing if the item is from QStringList
    }
    if (currentItem->data(0, Qt::UserRole).toString() == classUserRole) {
        currentItem->setText(0, toLowerCamelCase(currentItem->text(0)));
        currentItem->setData(0, Qt::UserRole, globalFunctionUserRole);
        currentItem->setIcon(0, QIcon(":/images/toolbar_images/memberfunc.svg"));
    }else if(currentItem->data(0, Qt::UserRole).toString() == classFunctionUserRole){
        // Ensure the current item is removed from its current position if necessary
        QTreeWidgetItem* parentItem = currentItem->parent();
        if (parentItem) {
            parentItem->removeChild(currentItem);  // Remove it from its current parent
        } else {
            int index = treeWidget->indexOfTopLevelItem(currentItem);
            if (index != -1) {
                treeWidget->takeTopLevelItem();  // Remove from top-level if it is a root item
            }
        }
        currentItem->setIcon(0, QIcon(":/images/toolbar_images/memberfunc.svg"));
        currentItem->setData(0, Qt::UserRole, globalFunctionUserRole);
        treeWidget->addTopLevelItem(currentItem);
    }
    treeWidget->setCurrentItem(currentItem);
}
