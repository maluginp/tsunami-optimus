#include "delegatecombobox.h"

DelegateComboBox::DelegateComboBox(QObject *parent)
{
    mColumn = -1;
}
DelegateComboBox::DelegateComboBox(QObject *parent,QStringList items){
    setItems( items );
    mColumn = -1;
}

DelegateComboBox::DelegateComboBox(QObject *parent, QStringList items, int column)
{
    setItems( items );
    mColumn = column;
}

QWidget *DelegateComboBox::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QComboBox *editor = new QComboBox(parent);
    editor->installEventFilter( const_cast<DelegateComboBox *>(this) );

    if(mItems.count() > 0){
        editor->addItems( mItems );
    }

    if(mColumn != -1){

        if(mColumn == index.column()){
            return editor;
        }else{

            QWidget *wdg = QItemDelegate::createEditor( parent, option, index );
            return wdg;
        }

    }



    return editor;
}

void DelegateComboBox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString val = index.model()->data(index, Qt::DisplayRole).toString();


    if(mColumn != -1 && mColumn != index.column()){
        return;
    }
    QComboBox *comboBox = static_cast<QComboBox*>(editor);


    int idx = comboBox->findText(val);
    comboBox->setCurrentIndex( idx );

}

void DelegateComboBox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(mColumn != -1 && mColumn != index.column()){
        QString val  = static_cast<QLineEdit *>(editor)->text();
        model->setData(index, val ,Qt::DisplayRole );


        return;
    }

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    qDebug() <<  comboBox->currentText();
    model->setData(index, comboBox->currentText(),Qt::DisplayRole );

//    model->setData(index, value,  Qt::CheckStateRole);


}



//bool DelegateComboBox::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
////    if ((event->type() == QEvent::MouseButtonRelease) ||
////        (event->type() == QEvent::MouseButtonDblClick)) {
////      QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
//////      if (mouse_event->button() != Qt::LeftButton ||
//////          !CheckBoxRect(option).contains(mouse_event->pos())) {
//////        return false;
//////      }
////      if (event->type() == QEvent::MouseButtonDblClick) {
////        return true;
////      }
////    } else if (event->type() == QEvent::KeyPress) {
////      if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
////          static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
////        return false;
////      }
////    } else {
////      return false;
////    }

////    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
////    return model->setData(index, !checked, Qt::EditRole);

//}
