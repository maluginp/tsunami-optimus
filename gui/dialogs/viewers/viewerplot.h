#ifndef VIEWERPLOT_H
#define VIEWERPLOT_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class ViewerPlot;
}

class ViewerPlot : public QDialog
{
    Q_OBJECT
    
public:
    explicit ViewerPlot(QWidget *parent = 0);
    void setPlot(QCustomPlot *plot);
    ~ViewerPlot();
private slots:
    void closeClickPlotter(QMouseEvent *);
private:
    Ui::ViewerPlot *ui;
};

#endif // VIEWERPLOT_H
