/*
 * Bundled icon rendering acceptance, without receiver or recording.
 * This file is part of welle.io and was generated with the help of an AI
 * assistant (OpenAi Codex 6 Astra).
 *
 * welle.io is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * welle.io is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with welle.io; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <QDir>
#include <QIcon>
#include "gui_test_main.h"
#include "ui_test_case.h"

class UiIconTests : public UiTestCase {
    Q_OBJECT
private slots:
    void initTestCase() {
        hideDebugOutput();
        UiApp::writeSettings({{"device", 0}, {"enableAutoSdr", false}});
        QVERIFY(app.start());
    }
    void bundledIconsRender() {
        const QDir icons(":/icons/welle_io_icons/scalable");
        const auto names = icons.entryList({"*.svg"}, QDir::Files);
        QVERIFY(!names.isEmpty());
        for (const auto &file : names) {
            const auto image = QIcon::fromTheme(file.chopped(4)).pixmap(24,24).toImage();
            QVERIFY2(!image.isNull(), qPrintable("Empty icon: " + file));
            bool painted = false;
            for (int y=0; y<image.height(); ++y)
                for (int x=0; x<image.width(); ++x)
                    painted |= qAlpha(image.pixel(x,y)) != 0;
            QVERIFY2(painted, qPrintable("Transparent icon: " + file));
        }
        app.screenshot("icons-loaded");
    }
};
WELLE_GUI_TEST_MAIN(UiIconTests)
#include "tst_ui_icons.moc"
