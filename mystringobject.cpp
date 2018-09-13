#include <QDebug>

#include "mystringobject.h"


MyStringObject::MyStringObject()
{
    connect(&m_timer,&QTimer::timeout,this,&MyStringObject::showNextString);
}
/*每次调用 getString（不管主动被动），都会更新 m_StringList 及 m_getString*/
void MyStringObject::setGetString(QString getString)
{
    if (m_getString == getString)
        return;

    m_getString = getString;
    emit getStringChanged(m_getString);
    if(!checkStringSame(m_getString)) {     // 没有查询到同样的数据才追加
        m_StringList << m_getString;
        qWarning() << m_getString << "m_StringList" << m_StringList;
        /*------------2018/09/13-11：11----------
     修改并添加最后获取到的字符串立即显示，
     暂停当前显示的字符串，
     并且将最后获取到的字符串添加到字符串列表的最后一位；
     显示完成最后获取到的字符串后，继续显示暂停的字符串并继续。
     -------------2018/09/13-11：11----------*/
        if(m_timer.isActive()) {
            m_timer.stop();
        }
        sendStringToQml(m_getString);
        m_timer.start(2000);
    }
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
    if(!m_timer.isActive()) {
        m_timer.start(1000);
    }
}
/*校验传入的字符串与已经存储的字符串是否相等*/
bool MyStringObject::checkStringSame(QString string)
{
    for(int i = 0; i < m_StringList.length(); i++) {
        if( string == m_StringList.at(i)) {
            return true;
        }
    }
    return false;
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
    qWarning() << "timer out m_CurrentStringIndex" << m_CurrentStringIndex;
    if(0 == m_StringList.length()) {
        return;
    }
    sendStringToQml(m_StringList.at(m_CurrentStringIndex));
    if(m_CurrentStringIndex < m_StringList.length()-1) {
        m_CurrentStringIndex++;
    }
    else {
        m_CurrentStringIndex = 0;
    }
}

