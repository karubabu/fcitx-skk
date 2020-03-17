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

#ifndef ADDKEYWORDDIALOG_H
#define ADDKEYWORDDIALOG_H

#include <QDialog>

namespace Ui {
class AddKeywordDialog;
}

class AddKeywordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddKeywordDialog(QWidget* parent = 0);
    virtual ~AddKeywordDialog();
    QString keyword();

private:
    Ui::AddKeywordDialog* m_ui;
};

#endif // ADDKEYWORDDIALOG_H
