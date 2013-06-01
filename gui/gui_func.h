#ifndef GUI_FUNC_H
#define GUI_FUNC_H
#include <QObject>
#include <QMessageBox>

inline void messageInfo( char* text ){
    QMessageBox::information( 0, QObject::trUtf8("Информация"), QObject::trUtf8(text) );
}
inline void messageError( char* text ){
    QMessageBox::critical( 0, QObject::trUtf8("Ошибка"), QObject::trUtf8(text) );
}
inline void messageWarning( char* text ){
    QMessageBox::warning( 0, QObject::trUtf8("Предупреждение"), QObject::trUtf8(text) );
}
#endif // GUI_FUNC_H
