﻿#ifndef BLCOMICSITEHANDLER_H
#define BLCOMICSITEHANDLER_H

#include "../acomicsitehandler.h"
#include "../convertz.h"

class NetworkAccessor;

class BLComicSiteHandler : public AComicSiteHandler
{
    Q_OBJECT

public:

    explicit BLComicSiteHandler(QObject *parent = 0);

    QList<StringPair> getChapters(const QString &comicKey);
    QStringList getImageUrls(const QString &comicKey, const QString &chapterKey);

public slots:

    void update();

private slots:

    void _getComicInfo(const int &id, const QString &url, const QByteArray &data);

private:

    NetworkAccessor *_networkAccessor;
    ConvertZ _convertz;
};

#endif // BLCOMICSITEHANDLER_H
