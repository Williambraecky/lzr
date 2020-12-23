
#include "frame.hpp"


Frame::Frame(const lzr::Frame& frame)
  : paths(lzr::split_frame(frame))
{
}

int Frame::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return paths.size();
}

QVariant Frame::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role);
    QVariant v;
    v.setValue(get_path(index));
    return v;
}

bool Frame::setData(const QModelIndex& index, const QVariant& value, int role)
{
    Q_UNUSED(role);
    return set_path(index, value.value<lzr::Frame>());
}

int Frame::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return 1;
}

QModelIndex Frame::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    if(column != 0)
        return QModelIndex();

    if(row < 0 || row >= rowCount())
        return QModelIndex();

    return createIndex(row, 0);
}

QModelIndex Frame::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

bool Frame::removeRow(int row, const QModelIndex& parent)
{
    if(row < 0 || row >= rowCount())
        return false;

    beginRemoveRows(parent, row, row);
    paths.erase(paths.begin() + row);
    endRemoveRows();
    return true;
}

/*
 * Custom model functions
 */

QModelIndex Frame::duplicate(const QModelIndex& index)
{
    if(!index.isValid())
        return QModelIndex();

    if(index.row() < 0 || index.row() >= rowCount())
        return QModelIndex();

    return add_path(paths[index.row()]);
}

QModelIndex Frame::add_path(const lzr::Frame& path)
{
    int newRow = paths.size();

    beginInsertRows(QModelIndex(), newRow, newRow);
    paths.push_back(path); //copy the data to the new path
    endInsertRows();

    return this->index(newRow);
}

lzr::Frame Frame::get_path(const QModelIndex& index) const
{
    if(!index.isValid())
        return lzr::Frame();

    if(index.row() < 0 || index.row() >= rowCount())
        return lzr::Frame();

    return paths[index.row()];
}

bool Frame::set_path(const QModelIndex& index, lzr::Frame path)
{
    if(!index.isValid())
        return false;

    if(index.row() < 0 || index.row() >= rowCount())
        return false;

    //store the new vector data
    paths[index.row()] = path;

    emit dataChanged(index, index); //only every updates one index at a time
    return true;
}
