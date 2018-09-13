#include <QDebug>

#include "mystringobject.h"


MyStringObject::MyStringObject()
{
    connect(&m_timer,&QTimer::timeout,this,&MyStringObject::showNextString);
    m_timer.start(1000);

}
/*每次调用 getString（不管主动被动），都会更新 m_StringList 及 m_getString*/
void MyStringObject::setGetString(QString getString)
{
    if (m_getString == getString)
        return;

    m_getString = getString;
    emit getStringChanged(m_getString);
    m_StringList << m_getString;
    qWarning() << m_getString << "m_StringList" << m_StringList;
}
/*调用这个函数可以获取到一个 QStringList 的返回值*/
QStringList MyStringObject::sendStringListToQml()
{
    return m_StringList;
}
/*应该解析字符串列表并返回每一个解析到的数据*/
/*发送信号*/
void MyStringObject::loopData()
{
    /*每2秒显示下一个，直至最后一个*/
    for(int i = 0; i < m_StringList.length(); i++) {
        sendStringToQml(m_StringList.at(i));
        qWarning() << "m_StringList.(" << i << "): " << m_StringList.at(i);
    }
}
/*返回解析到的数据*/
QString MyStringObject::sendStringToQml(QString string)
{
    m_ShowString = string;
    qWarning() << "m_ShowString" << m_ShowString;
    return m_ShowString;
}
/*获取字符串列表中下一个字符串*/
void MyStringObject::showNextString()
{
    sendStringToQml(m_StringList.at(m_CurrentStringIndex));
    if(m_CurrentStringIndex < m_StringList.length()-1) {
        m_CurrentStringIndex++;
    }
    else {
        m_CurrentStringIndex = 0;
    }
}

