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

CreateProjectPage::CreateProjectPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Create a new project"));
    projectNameLabel = new QLabel(tr("Project &Name:"));
    projectNameLineEdit = new QLineEdit;
    projectNameLabel->setBuddy(projectNameLineEdit);

    projectPathLabel = new QLabel(tr("Project &Directory:"));
    projectPathLineEdit = new QLineEdit;
    projectPathLineEdit->setReadOnly(true);
    projectPathLabel->setBuddy(projectPathLineEdit);

    projectSpecPathLabel = new QLabel(tr("S&pecification Directory:"));
    projectSpecPathEdit = new QLineEdit;
    projectSpecPathEdit->setReadOnly(true);
    projectSpecPathLabel->setBuddy(projectSpecPathEdit);

    QPixmap pixmap(":/images/toolbar_images/folder.png");
    QPixmap scaledPixmap = pixmap.scaled(16, 16, Qt::KeepAspectRatio); // Adjust the size as needed

    // Set the icon on the button
    QIcon icon(scaledPixmap);
    openDirectoryButton = new QPushButton;
    openDirectoryButton->setIcon(icon);
    openDirectoryButton->resize(16, 16);

    connect(openDirectoryButton, &QPushButton::clicked, this, &CreateProjectPage::getProjectDirectory);

    openSpecButton = new QPushButton;
    openSpecButton->setIcon(icon);
    openSpecButton->resize(16, 16);
    connect(openSpecButton, &QPushButton::clicked, this, &CreateProjectPage::getSpecDirectory);

    targetLanguageLabel = new QLabel(tr("Target &Language:"));
    targetLanguageBox = new QComboBox;
    targetLanguageBox->addItem("C++");
    targetLanguageBox->addItem("Java");
    targetLanguageBox->addItem("C#");

    registerField("project name*", projectNameLineEdit);
    registerField("project path*", projectPathLineEdit);
    registerField("specification path", projectSpecPathEdit);
    //registerField("target language*", targetLanguageBox);
    registerField("target language*", targetLanguageBox, "currentText", SIGNAL(currentIndexChanged(int)));


    QGridLayout* layout = new QGridLayout;
    layout->addWidget(projectNameLabel, 0, 0);
    layout->addWidget(projectNameLineEdit, 0, 1);
    layout->addWidget(projectPathLabel, 1, 0);
    layout->addWidget(projectPathLineEdit, 1, 1);
    layout->addWidget(openDirectoryButton, 1, 2);

    layout->addWidget(projectSpecPathLabel, 2, 0);
    layout->addWidget(projectSpecPathEdit, 2, 1);
    layout->addWidget(openSpecButton, 2, 2);
    layout->addWidget(targetLanguageLabel, 3, 0);
    layout->addWidget(targetLanguageBox, 3, 1);
    setLayout(layout);

}

int CreateProjectPage::nextId() const
{
    return GuideWizard::Page_Conclusion;
}

bool CreateProjectPage::validatePage()
{
    if (projectNameLineEdit->text().isEmpty()) {
        qDebug() << "projectName is empty.";
        QMessageBox::warning(this, "Input Error", "Please enter your project name before proceeding.");
        return false; // Prevent going to the next page
    }

    if (projectPathLineEdit->text().isEmpty()) {
        qDebug() << "projectPath is empty";
        QMessageBox::warning(this, "Input Error", "Please select your project directory before proceeding.");
        return false; // Prevent going to the next page
    }
    return true; // Allow going to the next page
}

bool CreateProjectPage::isComplete() const
{
    return targetLanguageBox->currentIndex() >= 0 && !projectNameLineEdit->text().isEmpty()
            && !projectPathLineEdit->text().isEmpty();
}

void CreateProjectPage::getProjectDirectory()
{
    const QString proDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath(),
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!proDir.isEmpty()){
        projectPathLineEdit->setText(proDir);
    }

}

void CreateProjectPage::getSpecDirectory()
{
    const QString filePath = QFileDialog::getOpenFileName(this);    //打开文件对话框
    if(!filePath.isEmpty()){
        projectSpecPathEdit->setText(filePath);
    }
}
