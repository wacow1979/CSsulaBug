#include "comicmodel.h"
#include "sfupdatehandler.h"
#include "updatehandler.h"
#include <QDebug>
#include <QStringList>

ComicModel::ComicModel(QObject *parent) :
    QAbstractListModel(parent)
{
    _updateHandler = new SFUpdateHandler(this);
    connect(_updateHandler, SIGNAL(info(const QHash<QString,QString>)),
            SLOT(_insertOneEntry(const QHash<QString,QString>)));
    connect(_updateHandler, SIGNAL(finish()), SIGNAL(updateFinish()));
}

int ComicModel::rowCount(const QModelIndex &parent) const
{
    return _comicList.size();
}

QVariant ComicModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _comicList.size())
        return QVariant();

    QHash<QString, QString> comicInfo = _comicList[index.row()];
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


void ComicModel::update()
{
    _updateHandler->update();
}

QString ComicModel::getKey(const int idx) const
{
    return data(index(idx, 0), 2).toString();
}


void ComicModel::_insertOneEntry(const QHash<QString, QString> &info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _comicList << info;
    endInsertRows();
}

void ComicModel::d_test()
{
    /*
      * 測試
      */
    update();
}
