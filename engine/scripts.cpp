#include "scripts.h"

Scripts::Scripts(const QString& path)
{
    jsEngine.installExtensions(QJSEngine::AllExtensions);

    QFile scriptFile(path);
    scriptFile.open(QIODevice::ReadOnly);

    QTextStream stream(&scriptFile);
    QString fileContent = stream.readAll();

    scriptFile.close();

    jsEngine.evaluate(fileContent, path);
}

void Scripts::setVariable(const QString &name, QObject* object)
{
    jsEngine.globalObject().setProperty(name, jsEngine.newQObject(object));
}

void Scripts::setVariable(const QString &name, QJSValue value)
{
    jsEngine.globalObject().setProperty(name, value);
}

QJSValue Scripts::variable(const QString &name)
{
    return jsEngine.globalObject().property(name);
}

QJSValue Scripts::eval(const QString& program)
{
    return jsEngine.evaluate(program);
}

QJSValue Scripts::getNewQObject(QObject* object)
{
    return jsEngine.newQObject(object);
}

QJSValue Scripts::getNewObject()
{
    return jsEngine.newObject();
}
