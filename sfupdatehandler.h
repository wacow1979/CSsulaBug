#ifndef SFUPDATEHANDLER_H
#define SFUPDATEHANDLER_H

#include <QStringList>
#include "updatehandler.h"
#include "convertz.h"

class NetworkAccessor;
class QNetworkReply;

class SFUpdateHandler : public UpdateHandler
{
    Q_OBJECT

public:

    explicit SFUpdateHandler(QObject *parent = 0);
    bool isReady();

    void d_test();

public slots:

    void update();

private slots:

    void _onAccessorReply(const int &id, QNetworkReply *networkReply);
    void _onAccessorFinish(const int &id);

private:

    enum State { NothingDoing, ALLPageUrlListGetting, ComicInfoGetting, Finishing};
    State _currentState;
    NetworkAccessor *_networkAccessor;
    QStringList _allPageUrlList;
    ConvertZ _convertz;

    void _clear();
    void _startProcess(const State &state);
    void _getPageUrl(const QString &html);
    void _getComicInfo(const QString &html);
};

#endif // SFUPDATEHANDLER_H