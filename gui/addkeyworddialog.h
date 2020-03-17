#ifndef ADDKEYWORDDIALOG_H
#define ADDKEYWORDDIALOG_H

#include <QDialog>

namespace Ui {
class AddKeywordDialog;
}

class AddKeywordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddKeywordDialog(QWidget* parent = 0);
    virtual ~AddKeywordDialog();
    QString keyword();

private:
    Ui::AddKeywordDialog* m_ui;
};

#endif // ADDKEYWORDDIALOG_H
