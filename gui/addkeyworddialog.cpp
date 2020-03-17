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

#include "addkeyworddialog.h"
#include "ui_addkeyworddialog.h"
#include "common.h"
#include "config.h"

AddKeywordDialog::AddKeywordDialog(QWidget* parent): QDialog(parent)
    ,m_ui(new Ui::AddKeywordDialog)
{
    m_ui->setupUi(this);

}

AddKeywordDialog::~AddKeywordDialog()
{
    delete m_ui;
}

QString AddKeywordDialog::keyword()
{
    return m_ui->keywordLineEdit->text();
}
