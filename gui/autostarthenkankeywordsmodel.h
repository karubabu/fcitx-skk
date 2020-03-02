#ifndef AUTOSTARTHENKANKEYWORDSMODEL_H
#define AUTOSTARTHENKANKEYWORDSMODEL_H
#include <QAbstractListModel>
#include <jsoncpp/json/json.h>

class AutoStartHenkanKeywordsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AutoStartHenkanKeywordsModel(QObject* parent = 0);
    virtual ~AutoStartHenkanKeywordsModel();
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void load();
    void load(Json::Value& file);
    void defaults();
    bool save();
    void add();
private:
    QList< QString > m_keywords;
};

#endif //AUTOSTARTHENKANKEYWORDSMODEL_H
