#include "templateselector.h"
#include "templateeditor.h"  // or the correct path to TemplateEditor's header file

TemplateSelector::~TemplateSelector() {}

void TemplateSelector::addTemplateBlock(const QString &title, const QString &templateText)
{
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

    QLabel *titleLabel = new QLabel("<b>" + title + "</b>", this);
    frameLayout->addWidget(titleLabel);

    QLabel *templateLabel = new QLabel("<pre>" + templateText + "</pre>", this);
    templateLabel->setWordWrap(true);
    frameLayout->addWidget(templateLabel);

    QPushButton *editButton = new QPushButton("Edit Template", this);
    frameLayout->addWidget(editButton);

    connect(editButton, &QPushButton::clicked, this, [=]() {
        // Close the TemplateSelector dialog before opening the TemplateEditor
        this->close();  // Close TemplateSelector dialog immediately

        TemplateEditor *editor = new TemplateEditor(templateText, this);
        if (editor->exec() == QDialog::Accepted) {

            QString result = editor->getEditedTemplate();
            emit templateSelected(result);  // Signal to return the edited template


        }
        delete editor;
    });

    mainLayout->addWidget(frame);
}








