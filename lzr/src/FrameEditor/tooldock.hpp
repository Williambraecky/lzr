
#pragma once

#include <QtWidgets>
#include <QDebug>
#include "../flowlayout.hpp"
#include "frameeditorscene.hpp"



Q_DECLARE_METATYPE(tool_t);


class ToolDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit ToolDock(QWidget* parent = 0);
    void reset();

signals:
    void tool_changed(tool_t tool);

public slots:
    void tool_toggled(bool checked);

private:
    QToolButton*makeTool(tool_t tool, const QString& tooltip, const QKeySequence& shortcut);

    QWidget* content;
    FlowLayout* layout;

    QActionGroup* actions;
    QToolButton* pointer;
    QToolButton* draw;
    QToolButton* insert;
    QToolButton* del;
    QToolButton* brush;
};
