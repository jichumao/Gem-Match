#include "mysetting.h"
#include "ui_mysetting.h"
#include<QPainter>
#include <QStyleOption>
mySetting::mySetting(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::mySetting)
{
    ui->setupUi(this);

    //connect(p_QPushButton,SIGNAL(clicked()),this,SLOT(ShowFile()));

    QButtonGroup* m_pButtonGroup1 = new QButtonGroup(this);
    // 设置互斥
    m_pButtonGroup1->setExclusive(true);
    m_pButtonGroup1->addButton(ui->radioButton);
    m_pButtonGroup1->addButton(ui->radioButton_2);
    QButtonGroup* m_pButtonGroup2 = new QButtonGroup(this);
    // 设置互斥
    m_pButtonGroup2->setExclusive(true);
    m_pButtonGroup2->addButton(ui->radioButton_3);
    m_pButtonGroup2->addButton(ui->radioButton_4);
    ui->lineEdit->setEnabled(false);
    ui->choose1->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->choose2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->choose3->setEnabled(false);


    connect(ui->choose1, SIGNAL(clicked()), this, SLOT(chooseBackground()));
    connect(ui->choose2, SIGNAL(clicked()), this, SLOT(chooseJewel()));
    connect(ui->choose3, SIGNAL(clicked()), this, SLOT(chooseMusic()));

    // 连接信号槽
    connect(m_pButtonGroup1, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked1(QAbstractButton*)));
    connect(m_pButtonGroup2, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked2(QAbstractButton*)));
}

mySetting::~mySetting()
{
    delete ui;
}
void  mySetting::chooseBackground() {
    QString FileName = QFileDialog::getOpenFileName(this, "标题", ".", "*.png");
    ui->lineEdit->setText(FileName);

}
void  mySetting::chooseJewel() {
    QString FileName = QFileDialog::getOpenFileName(this, "标题", ".", "*.png");
    ui->lineEdit_2->setText(FileName);
}
void  mySetting::chooseMusic() {
    QString FileName = QFileDialog::getOpenFileName(this, "标题", ".", "*.wav");
    ui->lineEdit_3->setText(FileName);
}
void mySetting::onButtonClicked1(QAbstractButton*) {
    if (ui->radioButton->isChecked()) {
        ui->lineEdit->setEnabled(false);
        ui->choose1->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->choose2->setEnabled(false);
    }
    else {
        ui->lineEdit->setEnabled(true);
        ui->choose1->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->choose2->setEnabled(true);
    }

}
void mySetting::onButtonClicked2(QAbstractButton*) {
    if (ui->radioButton_3->isChecked()) {
        ui->lineEdit_3->setEnabled(false);
        ui->choose3->setEnabled(false);
    }
    else {
        ui->lineEdit_3->setEnabled(true);
        ui->choose3->setEnabled(true);
    }

}

void mySetting::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

