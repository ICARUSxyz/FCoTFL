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

void CodeHistory::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#f0f0f0"));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void CodeHistory::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}