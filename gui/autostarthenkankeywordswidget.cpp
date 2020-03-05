#include "common.h"
#include "autostarthenkankeywordswidget.h"
#include "autostarthenkankeywordsmodel.h"
#include "ui_autostarthenkankeywordswidget.h"
#include <fcitx-config/xdg.h>

SkkAutoStartHenkanKeywordsWidget::SkkAutoStartHenkanKeywordsWidget(QWidget* parent): FcitxQtConfigUIWidget(parent),m_ui(new Ui::SkkAutoStartHenkanKeywordsWidget)
{
    m_ui->setupUi(this);
    m_keywordModel = new AutoStartHenkanKeywordsModel(this);

    m_ui->autostarthenkankeywordsTable->setModel(m_keywordModel);

    load();
}

SkkAutoStartHenkanKeywordsWidget::~SkkAutoStartHenkanKeywordsWidget()
{
    delete m_ui;
}

QString SkkAutoStartHenkanKeywordsWidget::addon()
{
    return "fcitx-skk";
}

QString SkkAutoStartHenkanKeywordsWidget::title()
{
    return _("Auto Start Henkan Keywords");
}

QString SkkAutoStartHenkanKeywordsWidget::icon()
{
    return "fcitx-skk";
}

void SkkAutoStartHenkanKeywordsWidget::load()
{
    m_keywordModel->load();
}

void SkkAutoStartHenkanKeywordsWidget::save()
{
    m_keywordModel->save();
    Q_EMIT changed(false);
}
