#include "guidewizard.h"
#include <QtWidgets>

GuideWizard::GuideWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_CreateNewProject, new CreateProjectPage);
    setPage(Page_OpenExistingProject, new OpenProjectPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);

#ifndef Q_OS_MAC

    setWizardStyle(ModernStyle);
#endif

    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/toolbar_images/hmpp.png"));

    setWindowTitle(tr("HMPP Tool Guide"));
}

OpenProjectPage::OpenProjectPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Open an existing project"));
    projectPathLabel = new QLabel(tr("Project Path:"));
    projectPathLineEdit = new QLineEdit;
    projectPathLineEdit->setReadOnly(true);
    projectPathLabel->setBuddy(projectPathLineEdit);

    projectNameLineEdit = new QLineEdit;

    projectSpecPathLabel = new QLabel(tr("S&pecification Path:"));
    projectSpecPathEdit = new QLineEdit;
    projectSpecPathEdit->setReadOnly(true);
    projectSpecPathLabel->setBuddy(projectSpecPathEdit);
    targetLanguageLineEdit = new QLineEdit;

    QPixmap pixmap(":/images/toolbar_images/folder.png");
    QPixmap scaledPixmap = pixmap.scaled(16, 16, Qt::KeepAspectRatio); // Adjust the size as needed

    // Set the icon on the button
    QIcon icon(scaledPixmap);
    openFileButton = new QPushButton;
    openFileButton->setIcon(icon);
    openFileButton->resize(16, 16);

//    registerField("project name*", projectNameLineEdit, "text", SIGNAL(textChanged(QString)));
//    registerField("project path*", projectPathLineEdit, "text", SIGNAL(textChanged(QString)));
//    registerField("target language*", targetLanguageLineEdit, "text", SIGNAL(textChanged(QString)));

    targetLanguageLineEdit->setText("C++");

    connect(openFileButton, &QPushButton::clicked, this, &OpenProjectPage::getProjectDirectory);

    openSpecButton = new QPushButton;
    openSpecButton->setIcon(icon);
    openSpecButton->resize(16);
    connect(openSpecButton, &QPushButton::clicked, this, &OpenProjectPage::getSpecDirectory);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(projectPathLabel, 0, 0);
    layout->addWidget(projectPathLineEdit, 0, 1);
    layout->addWidget(openFileButton, 0, 2);
    layout->addWidget(projectSpecPathLabel, 1, 0);
    layout->addWidget(projectSpecPathEdit, 1, 1);
    layout->addWidget(openSpecButton, 1, 2);
    setLayout(layout);
}

int OpenProjectPage::nextId() const
{
    return GuideWizard::Page_Conclusion;
}

bool OpenProjectPage::validatePage()
{
    if (projectPathLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select your project file before proceeding.");
        return false; // Prevent going to the next page
    }
    return true;
}

void OpenProjectPage::getProjectDirectory()
{
    const QString filePath = QFileDialog::getOpenFileName();  
    if (!filePath.isEmpty()){
        QFileInfo fileInfo(filePath);
        QString directoryPath = fileInfo.absolutePath();
        QString fileName = fileInfo.fileName();

        qDebug() << "path:" << directoryPath;
        qDebug() << "file:" << fileName;

        projectPathLineEdit->setText(directoryPath);
        projectNameLineEdit->setText(fileName);
        targetLanguageLineEdit->setText("C++");

        setField("project name", projectNameLineEdit->text());
        setField("project path", projectPathLineEdit->text());
        setField("target language", targetLanguageLineEdit->text());
    }
}

void OpenProjectPage::getSpecDirectory()
{
    const QString filePath = QFileDialog::getOpenFileName(this);   
    if (!filePath.isEmpty()){
        projectSpecPathEdit->setText(filePath);

        setField("specification path", projectSpecPathEdit->text());
    }
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Welcome to HMPP tool"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/toolbar_images/watermark.png"));

    label = new QLabel(tr("You are going to working on the following project:"));
    projectName = new QLabel;
    projectPath = new QLabel;
    targetLanguage = new QLabel;
    specPath = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(projectName);
    layout->addWidget(projectPath);
    layout->addWidget(specPath);
    layout->addWidget(targetLanguage);
    setLayout(layout);
}


int ConclusionPage::nextId() const
{
    return 1;
}

void ConclusionPage::initializePage()
{
    QString proName = field("project name").toString();
    qDebug() << "proName:" << proName;
    QString proPath = field("project path").toString();
    qDebug() << "proPath:" << proPath;
    QString targetLang = field("target language").toString();
    qDebug() << "target Lang:" << targetLang;

    projectName->setText("Project Name: " + field("project name").toString());
    projectPath->setText("Project Directory: " + field("project path").toString());
    targetLanguage->setText("Target Language: " + field("target language").toString());
    specPath->setText("Specification Directory: " + field("specification path").toString());
}
