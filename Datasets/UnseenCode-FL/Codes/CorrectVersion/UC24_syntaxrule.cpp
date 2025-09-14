#include <syntaxrule.h>


//如何让程序不匹配引号或者注释里的东西


const QStringList basicType = {"\\bint\\b", "\\bbool\\b", "\\bchar\\b",
                                     "\\bfloat\\b", "\\bdouble\\b", "\\bvoid\\b", "\\bstd::string\\b"};

//定义普通类型的临时变量
//连续定义的无法识别，比如int a = 0, b = 0;
//带作用域的无法识别，比如std::string a;
//第一行匹配基础类型
//第二行匹配*&
//第三行匹配变量名
//第四行匹配[]
//1类型，2*&，3变量名，4[]
const QString basicVarStr = "\\b(" + basicType.join("|") + ")"
                                                          "(\\*|&?)[^\\S\n]+"
                                                          "([A-Za-z_][A-Za-z0-9_]*)\\b"
                                                          "(\\[?\\]?)[^\\S\n]*[;\\):=,](?!:)";

const QRegExp basicVarPattern = QRegExp(basicVarStr);


const QString classVarInHeaderStr = "\\b([A-Za-z_][A-Za-z0-9_]*)"
                                    "(\\*|&?)[^\\S\n]+%1\\b"
                                    "(\\[?\\]?)[^\\S\n]*;";

const QRegExp classVarInHeaderPattern = QRegExp(classVarInHeaderStr);

//定义全局变量
//1类型，2*&，3变量名，4[]
const QString globalVarStr = "\\b([A-Za-z_][A-Za-z0-9_]*)"
                             "(\\*|&?)[^\\S\n]+"
                             "([A-Za-z_][A-Za-z0-9_]*)"
                             "(\\[?\\]?)[^\\S\n]*[=;]";

const QRegExp globalVarPattern = QRegExp(globalVarStr);

//定义基础和复合变量一起扫描的情况
const QString varStr = "\\b([A-Za-z_][A-Za-z0-9_]*)[^\\S\n]*"
                       "(\\*|&?)[^\\S\n]*([A-Za-z_][A-Za-z0-9_]*)";

const QRegExp varPattern = QRegExp(varStr);

QString toLowerCamelCase(const QString &target)
{
    QStringList words = target.split(" ", QString::SkipEmptyParts);
    if (words.isEmpty()) return "";

    // Make the first word lowercase
    QString lowerCamel = words[0].toLower();

    // Capitalize the first letter of the remaining words
    for (int i = 1; i < words.size(); ++i) {
        lowerCamel += words[i].left(1).toUpper() + words[i].mid(1).toLower();
    }
    return lowerCamel;
}

QString toUpperCamelCase(const QString &target)
{
    QStringList words = target.split(" ", QString::SkipEmptyParts);
    if (words.isEmpty()) return "";

    QString upperCamel;
    // Capitalize the first letter of every word
    for (const QString &word : words) {
        upperCamel += word.left(1).toUpper() + word.mid(1).toLower();
    }
    return upperCamel;
}
