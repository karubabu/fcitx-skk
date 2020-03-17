/*
*    Copyright 2020~2020 by karubabu
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H
#define FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H

#include "autostarthenkankeywordsmodel.h"
#include <fcitxqtconfiguiwidget.h>

class AutoStartHenkanKeywordsModel;
namespace Ui {
class SkkAutoStartHenkanKeywordsWidget;
}

class SkkAutoStartHenkanKeywordsWidget : public FcitxQtConfigUIWidget
{
    Q_OBJECT
public:
    explicit SkkAutoStartHenkanKeywordsWidget(QWidget* parent = 0);
    virtual ~SkkAutoStartHenkanKeywordsWidget();

    virtual void load();
    virtual void save();
    virtual QString title();
    virtual QString addon();
    virtual QString icon();

private Q_SLOTS:
    void addKeywordClicked();
    void defaultKeywordsClicked();
    void removeKeywordClicked();
private:
    Ui::SkkAutoStartHenkanKeywordsWidget* m_ui;
    AutoStartHenkanKeywordsModel* m_keywordModel;
};

#endif // FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H
