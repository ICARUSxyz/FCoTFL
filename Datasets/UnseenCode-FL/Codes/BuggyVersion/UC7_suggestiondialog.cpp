#include "suggestiondialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QClipboard>
#include <QMenu>

SuggestionDialog::SuggestionDialog(QWidget *parent)
    : QDialog(parent),
      tabWidget(new QTabWidget(this)),
      templateListCodeGen(new QListWidget(this)),
      templateListBugFix(new QListWidget(this)),
      templateListAnnotation(new QListWidget(this)),
      editAreaCodeGen(new QTextEdit(this)),
      editAreaBugFix(new QTextEdit(this)),
      editAreaAnnotation(new QTextEdit(this)),
      generateButton(new QPushButton("Generate", this)),
      generatedResultWidget(new GeneratedResultWidget(this)) {  // GeneratedResultWidget 

    setupUI();
    setupConnections();
}

void SuggestionDialog::setGeneratedResult(const QString &result) {
    generatedResultWidget->setGeneratedResult();  // GeneratedResultWidget
}

void SuggestionDialog::addContextMenu(QListWidget *listWidget, QTextEdit *editArea) {
    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget, &QListWidget::customContextMenuRequested, this, [listWidget](const QPoint &pos) {
        QMenu menu;
        menu.addAction("Delete Template", [listWidget]() {
            QListWidgetItem *currentItem = listWidget->currentItem();
            if (currentItem) {
                delete currentItem;
            }
        });
        menu.exec(listWidget->viewport()->mapToGlobal(pos));
    });

    editArea->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(editArea, &QTextEdit::customContextMenuRequested, this, [this, listWidget, editArea](const QPoint &pos) {
        QMenu menu;
        menu.addAction("Add Template", [this, listWidget]() {
            bool ok;
            QString templateName = QInputDialog::getText(this, "Add Template", "Template Name:", QLineEdit::Normal, "", &ok);
            if (ok && !templateName.isEmpty()) {
                listWidget->addItem(templateName);
            }
        });
        menu.exec(editArea->viewport()->mapToGlobal());
    });

    connect(listWidget, &QListWidget::itemDoubleClicked, this, [editArea](QListWidgetItem *item) {
        editArea->setPlainText(item->text());
    });
}
