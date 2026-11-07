/*
 * App-bar contrast acceptance without a receiver or private recording.
 * This file is part of welle.io and was generated with the help of an AI
 * assistant (OpenAi Codex 6 Astra).
 *
 * welle.io is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later version.
 * welle.io is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details. You should have received a
 * copy along with welle.io; if not, see https://www.gnu.org/licenses/.
 */
#include <algorithm>
#include <cmath>
#include <QColor>
#include <QImage>
#include <QQmlProperty>
#include <QQuickWindow>
#include "gui_test_main.h"
#include "ui_test_case.h"

namespace {
double luminance(const QColor &color) {
    const auto linear = [](double c) {
        return c <= 0.04045 ? c / 12.92 : std::pow((c + 0.055) / 1.055, 2.4);
    };
    return 0.2126 * linear(color.redF()) + 0.7152 * linear(color.greenF())
        + 0.0722 * linear(color.blueF());
}
double contrast(const QColor &a, const QColor &b) {
    const double x = luminance(a), y = luminance(b);
    return (std::max(x, y) + 0.05) / (std::min(x, y) + 0.05);
}
}

class UiAppBarTests : public UiTestCase {
    Q_OBJECT
private slots:
    void foregroundContrast_data() {
        QTest::addColumn<int>("theme");
        QTest::addColumn<int>("width");
        QTest::newRow("light-compact") << 0 << 360;
        QTest::newRow("light-wide") << 0 << 800;
        QTest::newRow("dark-compact") << 1 << 360;
        QTest::newRow("dark-wide") << 1 << 800;
    }
    void foregroundContrast() {
        QFETCH(int, theme);
        QFETCH(int, width);
        hideDebugOutput();
        app.stop();
        UiApp::writeSettings({{"device", 0}, {"enableAutoSdr", false},
                              {"qQStyleTheme", theme}});
        QVERIFY(app.start());
        app.resize(width, 640);
        UiApp::settle();
        QImage frame;
        QTRY_VERIFY(!(frame = app.window()->grabWindow()).isNull());
        // Empty top-left padding of the actual rendered app-bar background.
        const QColor background = frame.pixelColor(2, 2);
        const QColor title = app.property("appTitle", "color").value<QColor>();
        QVERIFY(title.isValid());
        app.screenshot(QString("appbar-%1-%2").arg(theme).arg(width));
        QVERIFY2(contrast(title, background) >= 4.5,
                 qPrintable(QString("Title contrast %1").arg(contrast(title, background))));
        for (const auto &name : {"navButton", "playStopButton", "volumeButton"}) {
            auto *button = app.find(name);
            QVERIFY(button != nullptr);
            const QColor icon = QQmlProperty(button, "icon.color").read().value<QColor>();
            QVERIFY(icon.isValid());
            QVERIFY2(contrast(icon, background) >= 3.0, name);
        }
    }
};
WELLE_GUI_TEST_MAIN(UiAppBarTests)
#include "tst_ui_appbar.moc"
