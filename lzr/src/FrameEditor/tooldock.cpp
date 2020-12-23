
#include "tooldock.hpp"


ToolDock::ToolDock(QWidget* parent) : QDockWidget(parent)
{
    setWindowTitle("Tools");
    setFeatures(QDockWidget::DockWidgetMovable);

    setWidget(content = new QWidget());
    layout = new FlowLayout(content, -1, 0, 0);

    actions = new QActionGroup(content);
    actions->setExclusive(true);

    pointer = makeTool(POINTER, "Pointer", QKeySequence(Qt::Key_P));
    draw    = makeTool(DRAW,    "Draw",    QKeySequence(Qt::Key_L));
    insert  = makeTool(INSERT,  "Insert",  QKeySequence(Qt::Key_I));
    del     = makeTool(DELETE,  "Delete",  QKeySequence(Qt::Key_D));
    brush   = makeTool(BRUSH,   "Brush",   QKeySequence(Qt::Key_B));

    reset();
}

void ToolDock::reset()
{
    pointer->defaultAction()->setChecked(true);
}

void ToolDock::tool_toggled(bool checked)
{
    if(checked) //ignore the uncheck events from the previous tool
    {
        QAction* action = (QAction*) sender();
        emit tool_changed(action->data().value<tool_t>());
    }
}

QToolButton* ToolDock::makeTool(tool_t tool, const QString& tooltip, const QKeySequence& shortcut)
{
    QToolButton* button = new QToolButton(content);
    QAction* action = new QAction(tooltip, button);

    //load details into the action
    QVariant v;
    v.setValue(tool);
    action->setCheckable(true);
    action->setData(v);
    action->setShortcut(shortcut);

    connect(action, SIGNAL(toggled(bool)),
            this, SLOT(tool_toggled(bool)));

    actions->addAction(action);
    button->setDefaultAction(action);
    layout->addWidget(button);
    return button;
}
