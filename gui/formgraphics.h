#ifndef FORMGRAPHICS_H
#define FORMGRAPHICS_H

#include <QMainWindow>

namespace Ui {
class FormGraphics;
}

class FormGraphics : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FormGraphics(QWidget *parent = 0);
    ~FormGraphics();
    
private:
    Ui::FormGraphics *ui;
};

#endif // FORMGRAPHICS_H
