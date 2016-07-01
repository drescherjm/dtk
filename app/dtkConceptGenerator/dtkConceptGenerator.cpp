#include "dtkConceptGenerator.h"

dtkConceptGenerator::dtkConceptGenerator()
{
    addPage(new dtkIntroPage());
    addPage(new dtkNewConceptPage());
    addPage(new dtkConceptDefinitionPage());
    addPage(new dtkPluginGeneratorPage());
}

void dtkConceptGenerator::accept()
{
    QString           name=field("new.name"       ).toString();
    QString         prefix=field("new.prefix"     ).toString();
    QString          layer=field("new.layer"      ).toString();
    QString  namespaceText=field("new.namespace"  ).toString();
    QString     customName=field("def.customName" ).toString();

    QString   pluginPrefix=field("plugin.prefix"  ).toString();
    QString   pluginSuffix=field("plugin.suffix"  ).toString();

    QString outputFilesPath=field("intro.path"  ).toString();


    QMap<QString,QString> values;

    //define variables required for abstraction

    values.insert("${ABSTRACTION}", prefix+"Abstract"+name);
    values.insert("${LAYER_NAME}", prefix+layer);
    values.insert("${_LAYER_NAME}", (prefix+layer).toUpper());

    bool inheritsCustom,inheritsQObject,inheritsQRunnable,pluginSystem, inherits=false;

    inheritsQRunnable=field("def.runnable"    ).toBool();
    inheritsQObject  =field("def.qObject"     ).toBool();
    inheritsCustom   =field("def.custom"      ).toBool();
    pluginSystem     =field("def.pluginSystem").toBool();



    if(inheritsQObject)
    {
        values.insert("${QOBJECT}","QObject");
        values.insert("${QOBJECT_INCLUDE}","#include <QObject>");
        values.insert("${QOBJECT_CTR}","QObject(parent)");
        values.insert("${QOBJECT_CTR_PARAM}","QObject* parent=0");
        values.insert("${Q_OBJECT_MACRO}","Q_OBJECT");
        inherits=true;
    }
    else
    {
        values.insert("${QOBJECT}","");
        values.insert("${QOBJECT_INCLUDE}","");
        values.insert("${QOBJECT_CTR}","");
        values.insert("${QOBJECT_CTR_PARAM}","");
        values.insert("${Q_OBJECT_MACRO}","");
    }
    if(inheritsQRunnable)
    {
        QString separator=inherits?",": "";

        values.insert("${QRUNNABLE}",separator+"public QRunnable");
        values.insert("${QRUNNABLE_CTR}",separator+"QRunnable()");
        values.insert("${QRUNNABLE_INCLUDE}","#include <QRunnable>");

        inherits=true;
    }
    else
    {
        values.insert("${QRUNNABLE}","");
        values.insert("${QRUNNABLE_CTR}","");
        values.insert("${QRUNNABLE_INCLUDE}","");
    }
    if(inheritsCustom)
    {
        QString separator=inherits?",": "";

        values.insert("${CUSTOM_ANCESTOR}",separator+customName);
        values.insert("${CUSTOM_ANCESTOR_CTR}",separator+customName);
        values.insert("${CUSTOM_ANCESTOR_INCLUDE}","#include \""+customName+"\"");
        inherits=true;
    }
    else
    {
        values.insert("${CUSTOM_ANCESTOR}","");
        values.insert("${CUSTOM_ANCESTOR_CTR}","");
        values.insert("${CUSTOM_ANCESTOR_INCLUDE}","");
    }

    if(pluginSystem)
    {

       QString macroParams="("+values["${ABSTRACTION}"]+", "+values["${_LAYER_NAME}"]+"_EXPORT)";
       values.insert("${PLUGIN_SYSTEM}",
            "DTK_DECLARE_PLUGIN        "+macroParams + "\n" +
            "DTK_DECLARE_PLUGIN_FACTORY"+macroParams + "\n" +
            "DTK_DECLARE_PLUGIN_MANAGER"+macroParams);
    }

    //values for plugins

    values.insert("${PLUGIN_CLASS_NAME}",pluginPrefix+name+pluginSuffix);
    values.insert("${NAMESPACE}",namespaceText);

    //values for node
    values.insert("${NODE_CLASS_NAME}",prefix+name+"Node");


    generate("abstraction",values,outputFilesPath);
    generate("plugin",values,outputFilesPath);
    generate("node",values,outputFilesPath);

    QWizard::accept();

}
