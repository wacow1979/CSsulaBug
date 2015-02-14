﻿#ifndef ACOMICSITEHANDLER_H
#define ACOMICSITEHANDLER_H

#include <QObject>

#include "globals.h"

class AComicSiteHandler : public QObject
{
    Q_OBJECT

public:

    explicit AComicSiteHandler(QObject *parent = 0):QObject(parent){}

    virtual QString getComicSiteName() const = 0;

    virtual QList<StringPair> getChapters(const QString &comicKey) = 0;
    virtual QStringList getImageUrls(const QString &comicKey, const QString &chapterKey) = 0;

    virtual QString getReferer() const { return ""; }

signals:

    void comicInfoSignal(const QVariantMap &info);
    void collectingFinishedSignal();

public slots:

    virtual void collectComicInfos() = 0;

};

#endif // ACOMICSITEHANDLER_H