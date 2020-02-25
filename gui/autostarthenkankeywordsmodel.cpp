#include <QFile>
#include <fcitx-config/xdg.h>

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
    QFile f(path);
    if(f.open(QIODevice::ReadOnly)) {
        load(f);
    }
}

void AutoStartHenkanKeywordsModel::load()
{
    FILE* fp = FcitxXDGGetFileWithPrefix("skk", "auto_start_henkan_keywords", "r", NULL);
    if(!fp){
        return;
    }
    QFile f;
    if(!f.open(fp, QIODevice::ReadOnly)) {
        fclose(fp);
        return;
    }

    load(f);
    f.close();
    fclose(fp);
}

void AutoStartHenkanKeywordsModel::load(QFile& file)
{
    beginResetModel();
}
