// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickWindow>
#include <QApplication>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "h.h"

#include <QByteArray>

int main(int argc, char *argv[])
{
    // QQmlEngine::clearComponentCache();
    // QQmlJS::gc();
    // qputenv("QT_QUICK_BACKEND", "software");
    set_qt_environment();
    // QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);


    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication app(argc, argv);

    qmlRegisterType<FBO>("my_opengl", 1, 0, "FBO");
    qmlRegisterType<Rend>("my_opengl", 1, 0, "Rend");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    // qmlRegisterType<OurWidget>("my_opengl", 1, 0, "OurWidget");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
