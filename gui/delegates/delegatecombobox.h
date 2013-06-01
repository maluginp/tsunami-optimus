#ifndef DELEGATECOMBOBOX_H
#define DELEGATECOMBOBOX_H

#include <QtCore>
#include <QtGui>

class DelegateComboBox : public QItemDelegate
{
public:
    DelegateComboBox(QObject *parent);
    DelegateComboBox(QObject *parent,QStringList items);
    DelegateComboBox(QObject *parent,QStringList items, int column);


    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
   //Qt::ItemFlags flags ( const QModelIndex & index ) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);

    void setItems(QStringList items){
        mItems = items;
    }

private:
    QStringList mItems;
    int mColumn;


};

#endif // DELEGATECOMBOBOX_H
