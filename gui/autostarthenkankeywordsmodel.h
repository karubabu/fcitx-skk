#ifndef AUTOSTARTHENKANKEYWORDSMODEL_H
#define AUTOSTARTHENKANKEYWORDSMODEL_H
#include <QAbstractListModel>
#include <QFile>

class AutoStartHenkanKeywordsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AutoStartHenkanKeywordsModel(QObject* parent = 0);
    virtual ~AutoStartHenkanKeywordsModel();

    void load();
    void load(Json::Value& file);
    void defaults();
    bool save();
    void add();
private:
    QList< QString > m_keywords;
};

#endif //AUTOSTARTHENKANKEYWORDSMODEL_H
