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

#include <QString>
#include <fstream>
#include <vector>
#include <string>
#include <json-glib-1.0/json-glib/json-glib.h>
#include <fcitx-config/xdg.h>

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
    JsonParser *parser;
    GError *error = NULL;

    parser = json_parser_new();
    json_parser_load_from_file(parser, path, &error);

    if(error){
        g_error_free(error);
        g_object_unref(parser);
        return;
    }

    load(parser);
    free(path);
}

void AutoStartHenkanKeywordsModel::load()
{
    char* filename = NULL;
    FcitxXDGGetFileUserWithPrefix("skk", "auto_start_henkan_keywords", NULL, &filename);
    JsonParser *parser;
    GError *error = NULL;

    if(!filename){
        return;
    }

    parser = json_parser_new();
    json_parser_load_from_file(parser, filename, &error);

    if(error){
        if(error->code == G_FILE_ERROR_NOENT)
        {
            g_error_free(error);
            g_object_unref(parser);

            defaults();
            free(filename);
            return;

        }else{
            g_error_free(error);
            g_object_unref(parser);
            free(filename);
            return;
        }
    }

    load(parser);
    free(filename);
}

void AutoStartHenkanKeywordsModel::load(JsonParser* parser)
{
    beginResetModel();
    m_keywords.clear();
    JsonReader *reader = json_reader_new(json_parser_get_root(parser));
    if(!reader)
    {
        g_object_unref(parser);
        endResetModel();
        return;
    }

    if(!json_reader_read_member(reader, "auto_start_henkan_keywords"))
    {
        json_reader_end_member(reader);
        g_object_unref(reader);
        g_object_unref(parser);
        endResetModel();
        return;
    }
    if(!json_reader_is_array(reader))
    {
        json_reader_end_member(reader);
        g_object_unref(reader);
        g_object_unref(parser);
        endResetModel();
        return;
    }

    for (int index = 0; index < json_reader_count_elements(reader); index++) {
        json_reader_read_element(reader, index);
        std::string keyword(json_reader_get_string_value(reader));
        json_reader_end_element(reader);

        m_keywords << QString(keyword.c_str());
    }

    g_object_unref(reader);
    g_object_unref(parser);
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

bool AutoStartHenkanKeywordsModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if(parent.isValid())
    {
        return false;
    }

    if(count == 0
        || row >= m_keywords.size()
        || row + count > m_keywords.size())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    m_keywords.erase(m_keywords.begin() + row, m_keywords.begin() + row + count);
    endRemoveRows();

    return true;
}

void AutoStartHenkanKeywordsModel::add(const QString& keyword)
{
    beginInsertRows(QModelIndex(), m_keywords.size(), m_keywords.size());
    m_keywords << keyword;
    endInsertRows();
}
