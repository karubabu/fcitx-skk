#include <QString>
#include <fstream>
#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <fcitx-config/xdg.h>
#include <QDebug>

#include "autostarthenkankeywordsmodel.h"

AutoStartHenkanKeywordsModel::AutoStartHenkanKeywordsModel(QObject* parent) : QAbstractListModel(parent)
{

}

AutoStartHenkanKeywordsModel::~AutoStartHenkanKeywordsModel()
{

}

void AutoStartHenkanKeywordsModel::defaults()
{
    char* path = fcitx_utils_get_fcitx_path_with_filename("pkgdatadir", "skk/auto_start_henkan_keywords");
    qDebug() << "Defaults_path:" << QString(path);
    Json::Value f;
    std::ifstream config_doc(path, std::ifstream::binary);
    if(!config_doc.is_open()){
        // failed to open
        qDebug() << "faild to open: Json::Value " << QString(path);
        return;
    }
    config_doc >> f;
    if(f){
        load(f);
    }
}

void AutoStartHenkanKeywordsModel::load()
{
    char* filename_for_ifstream = NULL;
    FcitxXDGGetFileUserWithPrefix("skk", "auto_start_henkan_keywords", NULL, &filename_for_ifstream);
    qDebug() << "load()_path:" << QString(filename_for_ifstream);
    if(!filename_for_ifstream){
        return;
    }
    Json::Value f;
    std::ifstream config_doc(filename_for_ifstream , std::ifstream::binary);
    if(!config_doc.is_open()){
        // failed to open
        qDebug() << "faild to open: Json::Value " << QString(filename_for_ifstream);
        defaults();
        free(filename_for_ifstream);
        return;
    }
    config_doc >> f;
    if(!f){
        // failed to input json
        free(filename_for_ifstream);
        return;
    }
    load(f);
    free(filename_for_ifstream);
}

void AutoStartHenkanKeywordsModel::load(Json::Value& file)
{
    beginResetModel();
    m_keywords.clear();
    const Json::Value  auto_start_henkan_keywords_json_ary = file["auto_start_henkan_keywords"];
    if(!auto_start_henkan_keywords_json_ary){
        // can't find auto_start_henkan_keywords array
        qDebug() << "can't find auto_start_henkan_keywords array.";
        endResetModel();
        return;
    }

    for (int index = 0; index < auto_start_henkan_keywords_json_ary.size(); index++) {
        QString henkan_keyword(auto_start_henkan_keywords_json_ary[index].asCString());
        qDebug() << henkan_keyword;

        m_keywords << henkan_keyword;
    }
    endResetModel();
}

bool AutoStartHenkanKeywordsModel::save()
{
    char* name = NULL;
    FcitxXDGMakeDirUser("skk");
    FcitxXDGGetFileUserWithPrefix("skk", "auto_start_henkan_keywords", NULL, &name);
    qDebug() << "save()_path:" << QString(name);
    Json::Value root;
    for (int index = 0; index < m_keywords.size(); index++) {
        root["auto_start_henkan_keywords"].append(m_keywords[index].toStdString());
    }
    std::ofstream config_doc(name , std::ifstream::binary);
    config_doc << root;

    free(name);

    return true;
}

int AutoStartHenkanKeywordsModel::rowCount(const QModelIndex& parent) const
{
    return m_keywords.size();
}

QVariant AutoStartHenkanKeywordsModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if(index.row() >= m_keywords.size() || index.column() != 0){
        return QVariant();
    }

    switch(role){
        case Qt::DisplayRole:
            return m_keywords[index.row()];
    }

    return QVariant();

}
