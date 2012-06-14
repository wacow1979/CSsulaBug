#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H

#include <QObject>
#include <QHash>

class UpdateHandler : public QObject
{
    Q_OBJECT

public:

    explicit UpdateHandler(QObject *parent = 0);
    
signals:
    
    void info(const QHash<QString, QString> &info);
    void finish();

public slots:

    virtual bool isReady() const { return true;}
    virtual void update(){}
};

#endif // UPDATEHANDLER_H
