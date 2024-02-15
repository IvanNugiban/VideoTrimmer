#include "cutcontrols.h"
#include "qdatetime.h"
#include "ui_cutcontrols.h"
#include "constants.h"

CutControls::CutControls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CutControls)
{
    ui->setupUi(this);

    QObject::connect(ui->slider, SIGNAL(sliderMoved(int, int)), this, SLOT(on_slider_moved(int,int)));
}

CutControls::~CutControls()
{
    delete ui;
}

void CutControls::Setup(float maxValue, int sliderLeft, int sliderRight)
{
    max = maxValue;

    ui->slider->setLow(sliderLeft);
    ui->slider->setHigh(sliderRight);

    formatText(sliderLeft, sliderRight);
}

RangeSlider *CutControls::getSlider()
{
    return ui->slider;
}


void CutControls::on_slider_moved(int low, int high)
{
    formatText(low, high);
}

void CutControls::formatText(int low, int high)
{
    qDebug() << high;

    QTime time(0,0,0,0);

    QTime first = time.addSecs(max / Constants::sliderMaxValue * low);
    QTime second = time.addSecs(max / Constants::sliderMaxValue * high);

    QString firstResult = first.toString("mm:ss");
    QString secondResult = second.toString("mm:ss");

    ui->info->setText(QString{"%1-%2"}.arg(firstResult).arg(secondResult));
}
