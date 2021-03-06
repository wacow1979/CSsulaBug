﻿#include "stubservice.h"

#include <comicmodel.h>
#include <sortfilterproxycomicmodel.h>

#include <QTimer>
#include <QThread>
#include <QDebug>

StubService::StubService(QObject *parent)
    :AService(parent)
{
    _model = new ComicModel(this);
    _proxyModel = new SortFilterProxyComicModel(this);
    _proxyModel->setSourceModel(_model);


    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/347639a1-530a-4550-988c-bab00a95c0fe.jpg";
        comicInfo["key"] = "JDZJ";
        comicInfo["name"] = "間諜之家";
        //comicInfo["author"] = "真刈信二";
        comicInfo["type"] = "推理類";
        comicInfo["updateStatus"] = "[011話連載中]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/04595fd1-746a-4ddc-9c82-05a28ba42aec.jpg";
        comicInfo["key"] = "CGX";
        comicInfo["name"] = "椿鬼";
        comicInfo["author"] = "押切蓮介";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "001卷[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/fd877ece-1ce2-45a3-9589-7f1893f23420.jpg";
        comicInfo["key"] = "SUGAR";
        comicInfo["name"] = "SUGARLESS無糖";
        comicInfo["author"] = "細川雅巳";
        comicInfo["type"] = "熱血類";
        comicInfo["updateStatus"] = "023話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/baa9dd71-d46e-4e65-96bd-26ab8efa27a3.jpg";
        comicInfo["key"] = "GWLRE";
        comicInfo["name"] = "怪物獵人Epic";
        comicInfo["author"] = "布施龍太";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "007話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/e9e72c53-323c-410e-bf64-d3797515d4f1.jpg";
        comicInfo["key"] = "DYDF";
        comicInfo["name"] = "地獄刀鋒";
        comicInfo["author"] = "柳濟泰";
        comicInfo["type"] = "魔幻類";
        comicInfo["updateStatus"] = "021話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/167a1629-5581-480d-aebc-2474323a48a6.jpg";
        comicInfo["key"] = "WDQCL";
        comicInfo["name"] = "我的青春戀愛喜劇果然有問題";
        comicInfo["author"] = "佳月玲茅";
        comicInfo["type"] = "校園類";
        comicInfo["updateStatus"] = "022話[未完結]";

        _comicInfos.append(comicInfo);
    }

    {
        StringHash comicInfo;
        comicInfo["site"] = "SF";
        comicInfo["coverUrl"] = "http://mh.sfacg.com/Logo/c235c24f-40d3-4593-8387-4b3b5e5a815b.jpg";
        comicInfo["key"] = "LSWDH";
        comicInfo["name"] = "獵殺瓦達漢加";
        comicInfo["author"] = "藤澤勇希";
        comicInfo["type"] = "冒險類";
        comicInfo["updateStatus"] = "003卷[已完結]";

        _comicInfos.append(comicInfo);
    }
}

SortFilterProxyComicModel *StubService::getModel()
{
    return _proxyModel;
}

QStringList StubService::getChapterNames(const QString &comicKey)
{
    Q_UNUSED(comicKey)
    QThread::sleep(2);
    return QStringList() << "024話" << "023話" << "022話" << "021話"
                         << "020話" << "019話" << "018話" << "017話"
                         << "016話" << "015話" << "014話" << "013話"
                         << "012話" << "011話" << "010話" << "009話"
                         << "008話" << "007話" << "006話" << "005話"
                         << "004話" << "003話" << "002話" << "001話";

}

void StubService::update()
{
    setProperty("isUpdatingStatus", true);
    for(int i=0; i< _comicInfos.size(); i++)
    {
        QTimer::singleShot(i * 500, this, SLOT(_onUpdate()));
    }
}


void StubService::setComicNameFilter(const QString &pattern)
{
    _proxyModel->setComicNameFilter(pattern);
}


void StubService::download(const QString &comicKey)
{
    download(comicKey, getChapterNames(comicKey));
}

void StubService::download(const QString &comicKey, const QStringList &chapterNames)
{
    setProperty("isDownloadingStatus", true);

    qDebug() << "下載" << chapterNames;
    QModelIndex modelIndex = _proxyModel->match(_proxyModel->index(0, 0), 2, comicKey)[0];

    _currentTask = _proxyModel->data(modelIndex, ComicModel::Name).toString();
    for(int i=0; i< 10; i++)
    {
        QTimer::singleShot(i * 1000, this, SLOT(_onDownload()));
    }
}

void StubService::_onUpdate()
{
    static int i=0;
    _model->insertComicInfo(_comicInfos[i]);

    if(i == _comicInfos.size() - 1)
    {
        setProperty("isUpdatingStatus", false);

        emit updateFinishedSignal();
    }

    i+=1;
}

void StubService::_onDownload()
{
    static int i=1;

    setProperty("downloadProgress", QString("[進度 %1%] 下載 %2").arg(i * 10).arg(_currentTask));
    if(i == 10)
    {
        i = 1;
        setProperty("isDownloadingStatus", false);

        emit downloadFinishSignal();
    }

    i+=1;
}



