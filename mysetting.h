#ifndef MYSETTING_H
#define MYSETTING_H

#include <QWidget>
#include<QFileDialog>
#include<QString>
#include<QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class mySetting; }
QT_END_NAMESPACE

class mySetting : public QWidget
{
    Q_OBJECT

public:
    mySetting(QWidget* parent = nullptr);
    ~mySetting();

private:
    Ui::mySetting* ui;
private slots:
    void chooseBackground();
    void chooseJewel();
    void onButtonClicked1(QAbstractButton*);
    void onButtonClicked2(QAbstractButton*);
    void chooseMusic();
    void paintEvent(QPaintEvent*);
};
#endif // MYSETTING_H
