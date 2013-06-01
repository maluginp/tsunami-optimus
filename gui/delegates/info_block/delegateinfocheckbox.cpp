#include "delegateinfocheckbox.h"

static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) {
  QStyleOptionButton check_box_style_option;
  QRect check_box_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&check_box_style_option);
  QPoint check_box_point(view_item_style_options.rect.x() +
                         view_item_style_options.rect.width() / 2 -
                         check_box_rect.width() / 2,
                         view_item_style_options.rect.y() +
                         view_item_style_options.rect.height() / 2 -
                         check_box_rect.height() / 2);
  return QRect(check_box_point, check_box_rect.size());
}


DelegateInfoCheckBox::DelegateInfoCheckBox(QObject *parent){
}

QWidget *DelegateInfoCheckBox::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0){
        return NULL;
    }

    QCheckBox *editor = new QCheckBox(parent);
    editor->installEventFilter(const_cast<DelegateInfoCheckBox*>(this));

//     return editor;
    return NULL;
}

void DelegateInfoCheckBox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0){
        return;
    }

    bool value = index.model()->data(index, Qt::DisplayRole).toBool();
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);

    if(value){
        checkBox->setCheckState(Qt::Checked);
    }else{
        checkBox->setCheckState(Qt::Unchecked);
    }
}

void DelegateInfoCheckBox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 0){
        return;
    }

    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);

    int value = 0;

    if(checkBox->checkState() == Qt::Checked){
        value = 1;
    }else{
        value = 0;
    }

    model->setData(index, value,  Qt::CheckStateRole);

}

void DelegateInfoCheckBox::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void DelegateInfoCheckBox::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    }else if(index.column() == 1){


        bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

        QStyleOptionButton check_box_style_option;
        check_box_style_option.state |= QStyle::State_Enabled;
        if (checked) {
            check_box_style_option.state |= QStyle::State_On;
        } else {
            check_box_style_option.state |= QStyle::State_Off;
        }
        check_box_style_option.rect = CheckBoxRect(option);

        QApplication::style()->drawControl(QStyle::CE_CheckBox,&check_box_style_option,painter);
    }
}

bool DelegateInfoCheckBox::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 0){
        return false;
    }

    if ((event->type() == QEvent::MouseButtonRelease) ||
        (event->type() == QEvent::MouseButtonDblClick)) {
      QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
      if (mouse_event->button() != Qt::LeftButton ||
          !CheckBoxRect(option).contains(mouse_event->pos())) {
        return false;
      }
      if (event->type() == QEvent::MouseButtonDblClick) {
        return true;
      }
    } else if (event->type() == QEvent::KeyPress) {
      if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
          static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
        return false;
      }
    } else {
      return false;
    }

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
    return model->setData(index, !checked, Qt::EditRole);

}
