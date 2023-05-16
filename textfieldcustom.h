#ifndef TEXTFIELDCUSTOM_H
#define TEXTFIELDCUSTOM_H

#include <QKeyEvent>
#include <QLineEdit>

class TextfieldCustom : public QLineEdit
{
    Q_OBJECT
public:
    TextfieldCustom(QWidget *widget);
    void keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Return) {
            emit submitted();
        } else {
            QLineEdit::keyPressEvent(event);
        }
    }
signals:
    void submitted();
};

#endif // TEXTFIELDCUSTOM_H
