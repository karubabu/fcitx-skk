#include <QFile>
#include <fcitx-config/xdg.h>
#include <jsoncpp/json/json.h>
#include <fstream>

#include "autostarthenkankeywordsmodel.h"

AutoStartHenkanKeywordsModel::AutoStartHenkanKeywordsModel(QObject* parent) : QAbstractListModel(parent)
{
    m_keywords;
}

AutoStartHenkanKeywordsModel::~AutoStartHenkanKeywordsModel()
{

}

void AutoStartHenkanKeywordsModel::defaults()
{
    char* path = fcitx_utils_get_fcitx_path_with_filename("pkgdatadir", "skk/auto_start_henkan_keywords");
    Json::Value f;
    std::ifstream config_doc(path, std::ifstream::binary);
    if(!config_doc.is_open()){
        // failed to open
        return;
    }
    config_doc >> f;
    if(!f){
        load(f);
    }
    //QFile f(path);
    //if(f.open(QIODevice::ReadOnly)) {
    //    load(f);
    //}
}

void AutoStartHenkanKeywordsModel::load()
{
    char** filename_for_ifstream;
    FILE* fp = FcitxXDGGetFileWithPrefix("skk", "auto_start_henkan_keywords", "r", filename_for_ifstream);
    if(!fp){
        return;
    }
    //QFile f;
    //if(!f.open(fp, QIODevice::ReadOnly)) {
    //    fclose(fp);
    //    return;
    //}
    Json::Value f;
    std::ifstream config_doc(*filename_for_ifstream , std::ifstream::binary);
    if(!config_doc.is_open()){
        // failed to open
        return;
    }
    config_doc >> f;
    if(!f){
        fclose(fp);
        return;
    }
    load(f);
    fclose(fp);

    //load(f);
    //f.close();
    //fclose(fp);
}

void AutoStartHenkanKeywordsModel::load(Json::Value& file)
{
    beginResetModel();
    m_keywords.clear();

    QByteArray bytes;
    endResetModel();
}
