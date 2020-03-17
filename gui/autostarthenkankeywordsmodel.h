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

#ifndef AUTOSTARTHENKANKEYWORDSMODEL_H
#define AUTOSTARTHENKANKEYWORDSMODEL_H
#include <QAbstractListModel>
#include <json-glib-1.0/json-glib/json-glib.h>

class AutoStartHenkanKeywordsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AutoStartHenkanKeywordsModel(QObject* parent = 0);
    virtual ~AutoStartHenkanKeywordsModel();
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

    void load();
    void load(JsonParser* file);
    void defaults();
    bool save();
    void add(const QString& keyword);
private:
    QList< QString > m_keywords;
};

#endif //AUTOSTARTHENKANKEYWORDSMODEL_H
