#ifndef DIALOG_H
#define DIALOG_H

#include "Character.h"
#include <QDialog>
#include <vector>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_selectInputFileButton_clicked();

private:
    Ui::Dialog *ui;
    std::vector<Character> m_characters;
    QString m_fileName;
};

#endif // DIALOG_H
