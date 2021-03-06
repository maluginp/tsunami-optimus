#ifndef DELEGATEINFODATE_H
#define DELEGATEINFODATE_H

#include <QtCore>
#include <QtGui>

class DelegateInfoDate : public QItemDelegate
{
public:
    DelegateInfoDate(QObject *parent);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


};

#endif // DELEGATEINFODATE_H
