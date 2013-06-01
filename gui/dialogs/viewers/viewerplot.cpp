#include "viewerplot.h"
#include "ui_viewerplot.h"


ViewerPlot::ViewerPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewerPlot)
{
    ui->setupUi(this);

    QAction *action =new QAction("Close",this);

    action->setShortcut(Qt::Key_Control+Qt::Key_W);
    connect(action,SIGNAL(triggered()),this,SLOT(close()));



}

void ViewerPlot::setPlot(QCustomPlot *plot)
{
    ui->plotter->xAxis->setLabel( plot->xAxis->label()  );
    ui->plotter->yAxis->setLabel( plot->yAxis->label()  );


    ui->plotter->xAxis->setRange( plot->xAxis->range() );
    ui->plotter->yAxis->setRange( plot->yAxis->range() );

    int graph_count = plot->graphCount();

//    for(int i=0; i < graph_count;i++){
//        QCPGraph *graph = ui->plotter->addGraph( );
//        const QCPDataMap *data = ui->plotter->graph(i)->;
//        foreach(QCPData _data,data->values()){
//            graph->addData( _data );
//        }


//    }



    connect(ui->plotter,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(closeClickPlotter(QMouseEvent*)));

    ui->plotter->replot();
}

ViewerPlot::~ViewerPlot()
{
    delete ui;
}

void ViewerPlot::closeClickPlotter(QMouseEvent *)
{
    close();
}
