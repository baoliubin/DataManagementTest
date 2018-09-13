#ifndef MYSTRINGOBJECT_H
#define MYSTRINGOBJECT_H

#include <QTime>
#include <QTimer>
#include <QObject>
#include <QString>
#include <QBuffer>
#include <QByteArray>
#include <QStringList>


class MyStringObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString getString READ getString WRITE setGetString NOTIFY getStringChanged)
public:
    MyStringObject();
    ~MyStringObject() {

    }

    /*解析字符串并发送给qml*/
    QString getString() const { return m_getString; }

public slots:
    /*获取输出字符串并保存为列表*/
    void setGetString(QString getString);

    /*解析字符串列表并将整个列表发送给qml*/
    QStringList sendStringListToQml();
    /*返回解析到的数据*/
    QString sendStringToQml(QString string);

    /*线程工作*/
    void showNextString();
private slots:
    /*轮播列表内数据*/
    void loopData();

signals:
    void getStringChanged(QString getString);

private:

    QString m_getString = "";
    QStringList m_StringList;
    QString m_ShowString = "";
    int m_CurrentStringIndex = 0;

    QTimer m_timer;
};

#endif // MYSTRINGOBJECT_H
