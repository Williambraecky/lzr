
#pragma once

#include <QtWidgets>
#include "clipeditor.h"
#include "frameeditorview.h"
#include "frameeditorscene.h"
#include "frame.h"
#include "colordock.h"
#include "tooldock.h"
#include "pathdock.h"
#include "settingsdock.h"
#include "liblzr.h"


class LZR : public QMainWindow
{
    Q_OBJECT

public:
    explicit LZR();
    ~LZR();

public slots:
    void frame_changed(const QModelIndex& start, const QModelIndex& end);
    void rowsInserted(const QModelIndex& path, int a, int b);
    void rowsRemoved(const QModelIndex& path, int a, int b);

private:
    void setupUi();
    void show_frameeditor(Frame* frame);
    void show_clipeditor();

    void send_frame();

    QStackedWidget* stack;

    /*
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    */

    //FRAME EDITOR
    FrameEditor* editor_view;
    FrameScene* editor_scene;

    ToolDock* tools;
    ColorDock* color;
    PathDock* paths;
    SettingsDock* settings;

    //CLIP EDITOR
    ClipEditor* clip_editor;

    Frame* frame;
    void* zmq_ctx;
    void* zmq_pub;
    lzr::Optimizer* opt;
};
