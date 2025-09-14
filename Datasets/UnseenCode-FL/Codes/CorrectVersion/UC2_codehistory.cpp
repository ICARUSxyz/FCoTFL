#include "codehistory.h"
#include "historylinenumberarea.h"
#include <QPainter>
#include <QTextBlock>

CodeHistory::CodeHistory(QWidget *parent)
    : QPlainTextEdit(parent),
      lineNumberArea(new HistoryLineNumberArea(this)),  
      highlighter(new SyntaxHighlighter(this->document()))  
{
    
    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeHistory::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeHistory::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeHistory::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setEditorFont("Courier",10);  
}

void CodeHistory::setEditorFont(const QString &fontFamily, int fontSize)
{
    QFont font(fontFamily, fontSize);
    this->setFont(font);
}

void CodeHistory::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
    lineNumberAreaPaintEvent(event);
}

int CodeHistory::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}