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

void CutControls::setup(float maxValue, int sliderLeft, int sliderRight,  TextFormat format)
{
    max = maxValue;
    textFormat = format;

    setSlider(sliderLeft, sliderRight);
}

void CutControls::setSlider(int low, int high)
{
    ui->slider->setLow(low);
    ui->slider->setHigh(high);
    ui->slider->repaint();

    formatText(low, high);
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
    if (textFormat == time) {
        QTime time(0,0,0,0);

        QTime first = time.addSecs(std::round(max / Constants::sliderMaxValue * low));
        QTime second = time.addSecs(std::round(max / Constants::sliderMaxValue * high));

        QString firstResult = first.toString("mm:ss");
        QString secondResult = second.toString("mm:ss");

        ui->info->setText(QString{"%1-%2"}.arg(firstResult, secondResult));
    }

    else {
        ui->info->setText(QString{"%1%-%2%"}.arg(QString::number(low + 1), QString::number(high + 1)));
    }
}
