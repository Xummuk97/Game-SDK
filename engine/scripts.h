#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <QtCore>
#include <QtQml>

class Scripts
{
public:
    Scripts(const QString& path);
    ~Scripts() = default;

    void setVariable(const QString& name, QObject* object);
    void setVariable(const QString& name, QJSValue value);

    QJSValue variable(const QString& name);

    template<class T>
    void registerClass(const QString& name)                             // Регистрация C++ класса в JS
    {
        jsEngine.globalObject().setProperty(name, jsEngine.newQMetaObject(&T::staticMetaObject));
    }

    QJSValue eval(const QString& program);

    // Методы по работе с JS объектами
    QJSValue getNewQObject(QObject* object);
    QJSValue getNewObject();

private:
    QJSEngine jsEngine;
};

#endif // SCRIPTS_H
