﻿#include "networkaccessor.h"
#include <QtNetwork>
#include <QDebug>

NetworkAccessor::NetworkAccessor(QObject *parent) :
    QObject(parent), _idCount(0), _isAccessing(false)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            SLOT(_onManagerFinish(QNetworkReply*)));
}

int NetworkAccessor::get(const QString &url)
{
    /*
    *   id 為識別值，url 是要下載的網址
    *   get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
    */

    _Task newTask;
    newTask.id = _idCount++;
    newTask.urlList.append(url);

    _taskQueue.enqueue(newTask);
    _startAccess();

    return newTask.id;
}

int NetworkAccessor::get(const QStringList &urlList)
{
    /*
     *id 為識別值，url 是要下載的網址urlList 是要下載的網址清單
     *get 是決定將要下載的任務，實際的下載是由 _startAccess 操作
     */

    _Task newTask;
    newTask.id = _idCount++;
    newTask.urlList = urlList;

    _taskQueue.enqueue(newTask);
    _startAccess();

    return newTask.id;
}

void NetworkAccessor::_startAccess()
{
    /*
      *若是現在沒有實際執行下載任務，便開始執行。
      */

    if(!_isAccessing && !_taskQueue.isEmpty())
    {
        _isAccessing = true;
        _currentTask = _taskQueue.dequeue();

        foreach(QString url, _currentTask.urlList)
        {
            QNetworkRequest request = _makeRequest(url);
            qDebug() << "NetworkAccessor:_startAccess:開始下載 " << url;
            _networkAccessManager->get(request);
        }
    }
}

void NetworkAccessor::_onManagerFinish(QNetworkReply *networkReply)
{
    /*
      * 當 NetWorkAcessManager finish 時，若沒問題，就發送完成任務的訊號，
      * 若是發現還有其他的任務，就會繼續執行
      */

    const QString url = networkReply->url().toString();
    qDebug() << "NetworkAccessor:_onManagerFinish: 收到 " << url;

    if(networkReply->error())
    {
        qCritical() << "NetworkAccessor:onManagerFinish:error " << url;
        networkReply->deleteLater();
        return;
    }

    _currentTask.urlList.removeOne(url);
    emit reply(_currentTask.id, networkReply);
    networkReply->deleteLater();

    if(_currentTask.urlList.isEmpty())
    {
        emit finish(_currentTask.id);
        _isAccessing = false;
        _startAccess();
    }
}

QNetworkRequest NetworkAccessor::_makeRequest(const QString &url)
{
    /*
      *利用 url 加上一些必要的 header 模擬瀏覽器的行為製作 request
      */

    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)"
                         "AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0."
                         "1084.1 Safari/536.5");
    return request;
}

void NetworkAccessor::d_test()
{
    /*
      * 測試
      */

    const QString url1 = "http://cssula.nba.nctu.edu.tw/~marco/DoNotPress.exe";
    const QString url2 = "http://cssula.nba.nctu.edu.tw/~marco/GameOfLife.exe";

    get(url1);
    get(QStringList() << url1 << url2);
}