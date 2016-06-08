
#include "frame.h"


Frame::Frame(lzr::Frame& f)
{
    frame = f;
    find_paths();
}

Frame::~Frame()
{
    clear_paths();
}

int Frame::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return frame.size();
}

QVariant Frame::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role);

    if(!index.isValid())
        return QVariant();

    if(index.row() >= rowCount())
        return QVariant();

    //TODO
    return QVariant();
}

int Frame::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return 1;
}

QModelIndex Frame::index(int row, int column, const QModelIndex& index) const
{
    Q_UNUSED(column);
    Q_UNUSED(index);
    //TODO
    return QModelIndex();
}

QModelIndex Frame::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}



void Frame::find_paths()
{
    clear_paths();

    bool was_lit = false;
    size_t start = 0;
    for(size_t i = 0; i < frame.size(); i++)
    {
        lzr::Point& p = frame[i];

        if(p.is_lit() && !was_lit) //if the laser just turned on
        {
            start = i;
        }
        else if(p.is_blanked() && was_lit) //if the laser just turned off
        {
            //construct and save a new path
            paths.append(new Path(this, start, i - 1));
            //will never produce -1 becuase was_lit is initialized to
            //false at the beginning of looping
        }

        was_lit = p.is_lit();
    }

    //if a path was left open, close it
    if(was_lit)
        paths.append(new Path(this, start, frame.size() - 1));
}

void Frame::clear_paths()
{
    for(Path* p : paths)
        delete p;
    paths.clear();
}







/*
 * Paths
 */

Path::Path(QAbstractItemModel* frame, size_t s, size_t e)
{
    setSourceModel(frame);
    start = s;
    end = e;
}

int Path::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return end - start;
}

int Path::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return 1;
}

QVariant Path::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    //TODO
    return QVariant();
}

QModelIndex Path::index(int row, int column, const QModelIndex& index) const
{
    return QModelIndex();
}

QModelIndex Path::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}


QModelIndex Path::mapToSource(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

QModelIndex Path::mapFromSource(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}
