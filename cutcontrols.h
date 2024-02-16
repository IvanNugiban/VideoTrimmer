#ifndef CUTCONTROLS_H
#define CUTCONTROLS_H

#include "rangeslider.h"
#include <QWidget>

namespace Ui {
class CutControls;
}

class CutControls : public QWidget
{
    Q_OBJECT

public:

    enum TextFormat {
        time,
        percents
    };

    explicit CutControls(QWidget *parent = nullptr);
    ~CutControls();

    void setup(float maxValue, int sliderLeft, int sliderRight, TextFormat format = time);
    void setSlider(int low, int high);

    RangeSlider* getSlider();

private slots:

    void on_slider_moved(int low, int high);

private:

    Ui::CutControls *ui;
    TextFormat textFormat{};

    float max{};

    void formatText(int low, int high);
};

#endif // CUTCONTROLS_H
