#include "addkeyworddialog.h"
#include "ui_addkeyworddialog.h"
#include "common.h"
#include "config.h"

AddKeywordDialog::AddKeywordDialog(QWidget* parent): QDialog(parent)
    ,m_ui(new Ui::AddKeywordDialog)
{
    m_ui->setupUi(this);

}

AddKeywordDialog::~AddKeywordDialog()
{
    delete m_ui;
}

QString AddKeywordDialog::keyword()
{
    return m_ui->keywordLineEdit->text();
}
