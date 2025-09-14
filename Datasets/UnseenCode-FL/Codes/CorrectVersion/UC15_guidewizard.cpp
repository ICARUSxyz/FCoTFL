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

void GuideWizard::done(int result)
{
    if (result == QDialog::Accepted) {
        createNewFlag = hasVisitedPage(Page_CreateNewProject);
    }
    QWizard::done(result);
}

void GuideWizard::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Intro:
        message = tr("The decision you make here will affect which page you "
                     "get to see next.");
        break;
    case Page_CreateNewProject:
        message = tr("Create a new project and develop it in HMPP tool.");
        break;
    case Page_OpenExistingProject:
        message = tr("Open an existing project and continue developing it"
                     "in HMPP tool.");
        break;
    case Page_Conclusion:
        message = tr("The HMPP tool is developed by XiaYing in the Dependable"
                     "System in Hiroshima University.");       
        break;
    default:
        message = tr("This help is likely not to be of any help.");
    }

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

    QMessageBox::information(this, tr("HMPP Guide Help"), message);

    lastHelpMessage = message;
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/toolbar_images/watermark.png"));

    topLabel = new QLabel(tr("This wizard will guide you to create your own "
                             "new project or open an existing project "
                             "in the HMPP tool."));
    topLabel->setWordWrap(true);

    createNewProjectButton = new QRadioButton(tr("&Create a new project"));
    openExistingProjectButton = new QRadioButton(tr("&Open an existing project"));
    createNewProjectButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(createNewProjectButton);
    layout->addWidget(openExistingProjectButton);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    if (createNewProjectButton->isChecked()) {
        return GuideWizard::Page_CreateNewProject;
    } else {
        return GuideWizard::Page_OpenExistingProject;
    }
}
