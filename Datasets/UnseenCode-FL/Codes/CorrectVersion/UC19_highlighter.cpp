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

//! [7]
void Highlighter::highlightBlock(const QString &text)  //After a QSyntaxHighlighter object is created,
                                                        //its highlightBlock() function will be called automatically
                                                            //highlighting the given text block.
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
//! [7] //! [8]
    setCurrentBlockState(0);
//! [8]

//! [9]
    int startIndex = 0;
    // 没有/* 或 */ 对应状态0
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }

    //匹配双尖括号
    TextBlockData *data = new TextBlockData;

    int leftPos = text.indexOf(ParenthesisStartStr);
    while (leftPos != -1) {
        MarkInfo *info = new MarkInfo;
        info->character = ParenthesisStartStr;
        info->position = leftPos;

        data->insertParenthesisInfo(info);
        leftPos = text.indexOf(ParenthesisStartStr, leftPos + ParenthesisStartStr.size());
    }

    leftPos = text.indexOf(RequireNoteStartStr);
    while(leftPos != -1){
        MarkInfo *info = new MarkInfo;
        info->character = RequireNoteStartStr;
        info->position = leftPos;

        data->insertToDoNoteInfo(info);
        leftPos = text.indexOf(RequireNoteStartStr, leftPos + RequireNoteStartStr.size());
    }

    int rightPos = text.indexOf(ParenthesisEndStr);
    while (rightPos != -1) {
        MarkInfo *info = new MarkInfo;
        info->character = ParenthesisEndStr;
        info->position = rightPos;

        data->insertParenthesisInfo(info);

        rightPos = text.indexOf(ParenthesisEndStr, rightPos + ParenthesisEndStr.size());
    }

    rightPos = text.indexOf(RequireNoteEndStr);
    while (rightPos != -1) {
        MarkInfo *info = new MarkInfo;
        info->character = RequireNoteEndStr;
        info->position = rightPos;

        data->insertToDoNoteInfo(info);

        rightPos = text.indexOf(RequireNoteEndStr, rightPos + RequireNoteEndStr.size());
    }

    setCurrentBlockUserData(data);

}