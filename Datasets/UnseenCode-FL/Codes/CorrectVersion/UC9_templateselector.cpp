#include "templateselector.h"
#include "templateeditor.h"  // or the correct path to TemplateEditor's header file


TemplateSelector::TemplateSelector(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Select Comment Template");
    resize(600, 400); // Default size

    // Scrollable area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); 

    // Main layout
    QWidget *scrollWidget = new QWidget(scrollArea);
    mainLayout = new QVBoxLayout(scrollWidget);

    // Add example templates
    addTemplateBlock("Class Comment",
                     "/**\n"
                     " * @class ExampleClass\n"
                     " * @brief Description of the class\n"
                     " * @details Further details about the class functionality.\n"
                     " /// @author\n"
                     " /// @version\n"
                     " */");

    addTemplateBlock("Method Comment",
                     "/**\n"
                     " * @brief Brief description of the method\n"
                     " * @param param1 Description of param1\n"
                     " * @param param2 Description of param2\n"
                     " * @return Description of the return value\n"
                     " */");

    addTemplateBlock("Variable Comment",
                     "/**\n"
                     " * @var variableName\n"
                     " * @brief Description of the variable\n"
                     " */");

    addTemplateBlock("Function Comment",
                     "/**\n"
                     " * @fn <ReturnType> <FunctionName>(<ParameterList>)\n"
                     " * @brief <A brief description of the function's purpose>\n"
                     " *\n"
                     " * <A detailed description of the function, how it works, or any important implementation details.>\n"
                     " *\n"
                     " * @param <Parameter1> <Description of Parameter1>\n"
                     " * @param <Parameter2> <Description of Parameter2>\n"
                     " * @param <ParameterN> <Description of ParameterN>\n"
                     " *\n"
                     " * @return <Description of the return value>\n"
                     " * @retval <ReturnValue1> <Description of the meaning of ReturnValue1>\n"
                     " * @retval <ReturnValue2> <Description of the meaning of ReturnValue2>\n"
                     " *\n"
                     " * @pre <Description of the preconditions>\n"
                     " * @post <Description of the postconditions>\n"
                     " *\n"
                     " * @throws <ExceptionType> <Description of possible exceptions>\n"
                     " * @exception <ExceptionType> <Description of possible exceptions>\n"
                     " *\n"
                     " * @sa <Related functions or documentation links>\n"
                     " * @note <Special notes or remarks>\n"
                     " * @warning <Warning information>\n"
                     " * @deprecated <Deprecated function, suggested alternative>\n"
                     " *\n"
                     " * Example:\n"
                     " * 1. <Example1>\n"
                     " * 2. <Example2>\n"
                     " */");


    scrollWidget->setLayout(mainLayout);
    scrollArea->setWidget(scrollWidget);

    // Main dialog layout
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addWidget(scrollArea);

    // OK button
    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &TemplateSelector::accept);
    dialogLayout->addWidget(okButton);

    setLayout(dialogLayout);
}
