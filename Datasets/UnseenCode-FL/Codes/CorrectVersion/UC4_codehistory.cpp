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

void CodeHistory::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeHistory::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeHistory::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy) {
        lineNumberArea->scroll(0, dy);
    } else {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}
