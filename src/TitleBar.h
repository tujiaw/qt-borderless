#include <QtWidgets/QtWidgets>
#include <QMouseEvent>

#define WINDOW_MARGIN 5

class TitleBar : public QWidget
{
Q_OBJECT

public:
    TitleBar(QWidget *parent, const QString &text = QString());
    void setTitleText(const QString &text);

public slots:
    void showSmall();
    void showMaxRestore();

protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
	void mouseDoubleClickEvent(QMouseEvent *event);

    QLabel *mLabel;
    QToolButton *mMinimizeButton;
    QToolButton *mMaximizeButton;
    QToolButton *mCloseButton;
    QPixmap mRestorePix;
    QPixmap mMaxPix;
    bool mMaxNormal;
    QPoint mStartPos;
    QPoint mClickPos;
};
