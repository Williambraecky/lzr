
#pragma once

#include <liblzr.hpp>
#include <QAbstractListModel>
#include <QColor>
#include "effects.hpp"


Q_DECLARE_METATYPE(Effect*);


class Clip : public QAbstractListModel
{
    Q_OBJECT

public:
    Clip();
    ~Clip();
    lzr::Frame run(Time& t);

    //Qt Model interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const;
    QModelIndex index(int row, int column=0, const QModelIndex& parent=QModelIndex()) const;
    Effect* get_effect(const QModelIndex& index) const;

    QString name;
    QList<Effect*> effects;
};
