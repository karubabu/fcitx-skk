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

    connect(m_ui->addKeywordButton, SIGNAL(clicked(bool)), this, SLOT(addKeywordClicked()));
    connect(m_ui->defaultKeywordsButton, SIGNAL(clicked(bool)), this,  SLOT(defaultKeywordsClicked()));
    connect(m_ui->removeKeywordButton, SIGNAL(clicked(bool)), this, SLOT(removeKeywordClicked()));

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
    Q_EMIT changed(false);
}

void SkkAutoStartHenkanKeywordsWidget::save()
{
    m_keywordModel->save();
    Q_EMIT changed(false);
}

void SkkAutoStartHenkanKeywordsWidget::addKeywordClicked()
{
}

void SkkAutoStartHenkanKeywordsWidget::defaultKeywordsClicked()
{
    m_keywordModel->defaults();
    Q_EMIT changed(true);
}

void SkkAutoStartHenkanKeywordsWidget::removeKeywordClicked()
{
    if(m_ui->autostarthenkankeywordsTable->currentIndex().isValid())
    {
        m_keywordModel->removeRow(m_ui->autostarthenkankeywordsTable->currentIndex().row());
        Q_EMIT changed(true);
    }
}
