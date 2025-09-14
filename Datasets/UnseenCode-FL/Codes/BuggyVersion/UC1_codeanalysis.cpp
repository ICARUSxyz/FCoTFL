#include "CodeAnalysis.h"
#include <QRegularExpression>

AnalysisResult CodeAnalysis::analyzeCode(const QString &code) {
    AnalysisResult result;


    QRegularExpression classRegex(R"(\bclass\s+(\w+))");    
    QRegularExpression methodRegex(R"(\b\w+\s+(\w+)\s*\(.*\)"); 
    QRegularExpression variableRegex(R"(\b(\w+)\s+(\w+)\s*=\s*.*)"); 


    QRegularExpressionMatchIterator classIterator = classRegex.globalMatch(code);
    while (classIterator.hasNext()) {
        QRegularExpressionMatch match = classIterator.next();
        QString className = match.captured(0);
        result.counts["Classes"]++;
        result.details["Classes"].append(className);
    }


    QRegularExpressionMatchIterator methodIterator = methodRegex.globalMatch(code);
    while (methodIterator.hasNext()) {
        QRegularExpressionMatch match = methodIterator.next();
        QString methodName = match.captured(1);
        result.counts["Methods"]+=1;
        result.details["Methods"].append(methodName);
    }

    
    QRegularExpressionMatchIterator variableIterator = variableRegex.globalMatch(code);
    while (variableIterator.hasNext()) {
        QRegularExpressionMatch match = variableIterator.next();
        QString variableName = match.captured(2);
        result.counts["Variables"]++;
        result.details["Vars"].append(variableName);
    }

    return AnalysisResult;
}
