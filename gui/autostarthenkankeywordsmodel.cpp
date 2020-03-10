#include <QString>
#include <fstream>
#include <vector>
#include <string>
#include <json-glib-1.0/json-glib/json-glib.h>
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
    JsonParser *parser;
    JsonNode *root;
    GError *error = NULL;

    parser = json_parser_new();
    json_parser_load_from_file(parser, path, &error);

    if(error){
        qDebug() << "faild to open: Json::Value " << QString(path);
        g_print("Unable to parse `%s`: %s\n", path, error->message);
        g_error_free(error);
        g_object_unref(parser);
        return;
    }

    root = json_parser_get_root(parser);
    if(root){
        load(root);
    }
    free(path);
}

void AutoStartHenkanKeywordsModel::load()
{
    char* filename = NULL;
    FcitxXDGGetFileUserWithPrefix("skk", "auto_start_henkan_keywords", NULL, &filename);
    JsonParser *parser;
    JsonNode *root;
    GError *error = NULL;

    if(!filename){
        return;
    }

    qDebug() << "load()_path:" << QString(filename);
    parser = json_parser_new();
    json_parser_load_from_file(parser, filename, &error);

    if(error){
        if(error->code == G_FILE_ERROR_NOENT)
        {
            // failed to open
            qDebug() << "faild to open: " << QString(filename);
            g_print("Unable to parse `%s`: %s\n", filename, error->message);
            g_error_free(error);
            g_object_unref(parser);

            defaults();
            free(filename);
            return;

        }else{
            g_print("Unable to parse `%s`: %s\n", filename, error->message);
            g_error_free(error);
            g_object_unref(parser);
            free(filename);
            return;
        }
    }

    root = json_parser_get_root(parser);
    if(!root){
        // failed to input json
        g_object_unref(parser);
        free(filename);
        return;
    }
    load(root);
    free(filename);
}

void AutoStartHenkanKeywordsModel::load(JsonNode* file)
{
    beginResetModel();
    m_keywords.clear();
    JsonReader *reader = json_reader_new(file);

    if(!json_reader_read_member(reader, "auto_start_henkan_keywords"))
    {
        json_reader_end_member(reader);
        g_object_unref(reader);
        g_object_unref(file);
        g_print("Unable to read member `auto_start_henkan_keywords`");
        endResetModel();
        return;
    }
    if(!json_reader_is_array(reader))
    {
        json_reader_end_member(reader);
        g_object_unref(reader);
        g_object_unref(file);
        g_print("Unable to find `array`");
        endResetModel();
        return;
    }

    for (int index = 0; index < json_reader_count_elements(reader); index++) {
        json_reader_read_element(reader, index);
        std::string keyword(json_reader_get_string_value(reader));
        g_print("auto_start_henkan_keywords array element %d: %s\n", index, keyword.c_str());
        json_reader_end_element(reader);

        m_keywords << QString(keyword.c_str());
    }

    g_object_unref(reader);
    g_object_unref(file);
    endResetModel();
}

bool AutoStartHenkanKeywordsModel::save()
{
    char* name = NULL;
    FcitxXDGMakeDirUser("skk");
    FcitxXDGGetFileUserWithPrefix("skk", "auto_start_henkan_keywords", NULL, &name);

    if(!name)
    {
        return false;
    }

    qDebug() << "save()_path:" << QString(name);
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object(builder);

    json_builder_set_member_name(builder, "auto_start_henkan_keywords");
    json_builder_begin_array(builder);
    for (int index = 0; index < m_keywords.size(); index++) {
        std::string keyword(m_keywords[index].toStdString());
        json_builder_add_string_value(builder, keyword.c_str());
    }

    json_builder_end_array(builder);
    json_builder_end_object(builder);

    JsonGenerator *gen = json_generator_new();
    JsonNode *root = json_builder_get_root(builder);
    json_generator_set_root(gen, root);

    GError *error = NULL;
    json_generator_to_file(gen, name, &error);

    if(error)
    {
        g_print("Unable to write `%s`: %s\n", name, error->message);
        g_error_free(error);
        json_node_free(root);
        g_object_unref(gen);
        g_object_unref(builder);

        return false;
    }

    json_node_free(root);
    g_object_unref(gen);
    g_object_unref(builder);
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
