#ifndef FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H
#define FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H

#include <fcitxqtconfiguiwidget.h>

// class KeywordModel;
namespace Ui {
class SkkAutoStartHenkanKeywordsWidget;
}

class SkkAutoStartHenkanKeywordsWidget : public FcitxQtConfigUIWidget
{
    Q_OBJECT
public:
    explicit SkkAutoStartHenkanKeywordsWidget(QWidget* parent = 0);
    virtual ~SkkAutoStartHenkanKeywordsWidget();

    virtual void load();
    virtual void save();
    virtual QString title();
    virtual QString addon();
    virtual QString icon();

// private Q_SLOTS:
private:
    Ui::SkkAutoStartHenkanKeywordsWidget* m_ui;
    // KeywordModel* m_keywordModel;
};

#endif // FCITX_SKK_GUI_AUTOSTARTHENKANKEYWORDSWIDGET_H