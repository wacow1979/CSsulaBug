﻿#include "comicmodel.h"
#include "sfupdatehandler.h"
#include "aupdatehandler.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(AUpdateHandler *updateHandler, QObject *parent) :
    QAbstractListModel(parent), _updateHandler(updateHandler)
{
    connect(_updateHandler, SIGNAL(info(const StringHash&)),
            SLOT(_insertOneEntry(const StringHash&)));
    connect(_updateHandler, SIGNAL(finish()), SIGNAL(updateFinish()));
    connect(&_updateThread, SIGNAL(finished()), _updateHandler, SLOT(deleteLater()));

    connect(this, SIGNAL(_update()), _updateHandler, SLOT(update()), Qt::QueuedConnection);

    _updateHandler->moveToThread(&_updateThread);
    _updateThread.start();

    emit _update();
}

int ComicModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _comicList.size();
}

QVariant ComicModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _comicList.size())
        return QVariant();

    StringHash comicInfo = _comicList[index.row()];
    return comicInfo[roleNames()[role]];
}

QHash<int, QByteArray> ComicModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[0] = "coverUrl";
    roleNames[1] = "name";
    roleNames[2] = "key";
    roleNames[3] = "site";
    roleNames[4] = "type";
    roleNames[5] = "author";
    roleNames[6] = "lastUpdated";
    return roleNames;
}

void ComicModel::_insertOneEntry(const StringHash &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();
}

ComicModel::~ComicModel()
{
    _updateThread.quit();
    _updateThread.wait();
}
