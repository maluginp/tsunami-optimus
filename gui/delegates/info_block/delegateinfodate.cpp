#include "delegateinfodate.h"


DelegateInfoDate::DelegateInfoDate(QObject *parent){
}

QWidget *DelegateInfoDate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0){
        return NULL;
    }

    QDateEdit *editor = new QDateEdit( parent );

    editor->installEventFilter(const_cast<DelegateInfoDate*>(this));

    editor->setDisplayFormat( "dd.MM.yyyy" );
    return editor;
}

void DelegateInfoDate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0){
        return;
    }



    QDate valueDate = index.model()->data(index, Qt::DisplayRole).toDate();


    QDateEdit *dateEditor = static_cast<QDateEdit *>(editor);
    if( valueDate.isNull() ){
        dateEditor->setDate( QDate::currentDate() );
    }else{
        dateEditor->setDate( valueDate );
    }

    return;
}

void DelegateInfoDate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 0){
        return;
    }

    QDateEdit *dateEditor = static_cast<QDateEdit *>(editor);

    QString dateString = dateEditor->date().toString( "dd.MM.yyyy" );

    model->setData(index, dateString, Qt::DisplayRole );

}

//void DelegateInfoDate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    editor->setGeometry(option.rect);
//}

void DelegateInfoDate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0){
        QColor color(51,51,51);
        QColor background(0xDA,0xDA,0xDA);
        QStyleOptionViewItemV2 opt = setOptions(index, option);
        opt.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
        opt.palette.setColor(QPalette::Text,color);
        opt.font.setBold(true);

        painter->fillRect(option.rect,background);

        painter->setBackground(background);
        QItemDelegate::paint(painter, opt, index);
    }else{


        QItemDelegate::paint(painter,option,index);
    }

    return;
}

//bool DelegateInfoDate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    if(index.column() == 0){
//        return false;
//    }
//    return false;
////    if ((event->type() == QEvent::MouseButtonRelease) ||
////        (event->type() == QEvent::MouseButtonDblClick)) {
////      QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
////      if (mouse_event->button() != Qt::LeftButton ||
////          !CheckBoxRect(option).contains(mouse_event->pos())) {
////        return false;
////      }
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
