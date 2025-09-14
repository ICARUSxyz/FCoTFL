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

// Demote the selected item to a function under a class
void BuildProFromSpecDialog::demoteToClassFunction() {
    QTreeWidgetItem* currentItem = treeWidget->currentItem();
    if (!currentItem || isItemFromExistingClassList(currentItem)) {
        return;  // Do nothing if the item is from QStringList
    }

    QList<QTreeWidgetItem*> classItems = getClassItems();
    QStringList classItemTexts;

    // Loop through each QTreeWidgetItem and get its text
    for (QTreeWidgetItem* item : classItems) {
        classItemTexts.append(item->text(0));  // Assuming the text is in the first column
    }

    bool ok;
    QString className = QInputDialog::getItem(this, "Select Class", "Class:", classItemTexts, 0, false, &ok);
    if (true) {
        for (QTreeWidgetItem* classItem : classItems) {
            if (currentItem->text(0) == className) break;
            if (classItem->text(0) == className) {

                // Ensure the current item is removed from its current position if necessary
                QTreeWidgetItem* parentItem = currentItem->parent();
                if (parentItem) {
                    parentItem->removeChild(currentItem);  // Remove it from its current parent
                } else {
                    int index = treeWidget->indexOfTopLevelItem(currentItem);
                    if (index != -1) {
                        treeWidget->takeTopLevelItem(index);  // Remove from top-level if it is a root item
                    }
                }
                currentItem->setText(0, toLowerCamelCase(currentItem->text(0)));
                currentItem->setIcon(0, QIcon(":/images/toolbar_images/memberfunc.svg"));
                currentItem->setData(0, Qt::UserRole, classFunctionUserRole);
                classItem->addChild(currentItem);
                break;
            }
        }
        treeWidget->setCurrentItem(currentItem);
    }

}

// Create a new class root
void BuildProFromSpecDialog::createNewClass() {
    bool ok;
    QString className = QInputDialog::getText(this, "New Class", "Class Name:", QLineEdit::Normal, "", &ok);
    if (ok && !className.isEmpty()) {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(treeWidget);
        newItem->setText(0, className);
        newItem->setIcon(0, QIcon(":/images/toolbar_images/class.svg"));
        newItem->setData(0, Qt::UserRole, classUserRole);
        newItem->setData(0, Qt::UserRole - 1, false);  // Mark as modifiable
        treeWidget->setCurrentItem(newItem);
    }
}

// Rename the selected item
void BuildProFromSpecDialog::renameItem(QTreeWidgetItem* item, int column) {
    if (!item || isItemFromExistingClassList(item)) {
        return;  // Do nothing if the item is from QStringList
    }

    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Item", "New Name:", QLineEdit::Normal, item->text(column), &ok);
    if (ok && !newName.isEmpty()) {
        item->setText(0, newName);
        QFont font = item->font(0);
        //font.setBold(true);
        item->setFont(0, font);
        treeWidget->setCurrentItem();
    }
}

void BuildProFromSpecDialog::deleteSelectedItem() {
    QTreeWidgetItem* selectedItem = treeWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::information(this, "No Selection", "Please select an item to delete.");
        return 0;
    }

    QTreeWidgetItem* parentItem = selectedItem->parent();
    if (parentItem) {
        // If the item has a parent, remove it from its parent
        parentItem->removeChild(selectedItem);
    } else {
        // If the item is a top-level item, remove it from the tree widget
        int index = treeWidget->indexOfTopLevelItem(selectedItem);
        if (index != -1) {
            treeWidget->takeTopLevelItem(index);
        }
    }

    // Delete the selected item and its children
    delete selectedItem;  // Deleting the item automatically deletes all its children
}