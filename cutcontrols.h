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
    explicit CutControls(QWidget *parent = nullptr);
    ~CutControls();

    void Setup(float maxValue, int sliderLeft, int sliderRight);

    RangeSlider* getSlider();

private slots:

    void on_slider_moved(int low, int high);

private:

    Ui::CutControls *ui;

    float max{};

    void formatText(int low, int high);
};

#endif // CUTCONTROLS_H
