#include "highlighter.h"
#include <QDebug>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

const QString ParenthesisStartStr = "{";
const QString ParenthesisEndStr = "}";

const QString RequireNoteStartStr = "/* todo:";
const QString RequireNoteEndStr = "*/";

TextBlockData::TextBlockData()
{
    // Nothing to do
}

QVector<MarkInfo *> TextBlockData::parentheses()
{
    return m_parentheses;
}

QVector<MarkInfo *> TextBlockData::todoNotes()
{
    return m_todoNotes;
}

QVector<MarkInfo *> TextBlockData::getInfos(QString targetStr)
{
    if(targetStr == ParenthesisStartStr){
        return parentheses();
    }else if(targetStr == RequireNoteStartStr){
        return todoNotes();
    }else{
        return QVector<MarkInfo*>();
    }
}

void TextBlockData::insertParenthesisInfo(MarkInfo *info)
{
    int i = 0;
    while (i < m_parentheses.size() &&
        info->position > m_parentheses.at(i)->position)
        ++i;

    m_parentheses.insert(i, info);
}

void TextBlockData::insertToDoNoteInfo(MarkInfo *info)
{
    int i = 0;
    while (i < m_todoNotes.size() &&
        info->position > m_todoNotes.at(i)->position)
        ++i;

    m_todoNotes.insert(i, info);
}


//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\breturn\\b"
                    << "\\bnew\\b" << "\\bdelete\\b" << "\\bfor\\b"
                    << "\\bwhile\\b" << "\\binclude\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2]
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
//! [2]

//! [3]
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);
//! [3]
    //单行伪码需求
    singleLineRequireFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("(>>>[^\n]*)|(<<<)");
    rule.format = singleLineRequireFormat;
    highlightingRules.append(rule);



//! [4]
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5]
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
//! [5]
}
