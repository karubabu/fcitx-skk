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
