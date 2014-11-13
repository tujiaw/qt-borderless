#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>

class TitleBar;

class MainFrame : public QFrame
{
public:
    MainFrame();

    // Allows you to access the content area of the frame
    // where widgets and layouts can be added
    QMainWindow *mainWindow() const { return mMainWindow; }
    TitleBar *titleBar() const { return mTitleBar; }
    void setContentWidget(QWidget *content);

    void mousePressEvent(QMouseEvent *e);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMove(QPoint newPos, QPoint oldPos);

private:
    TitleBar *mTitleBar;
    QMainWindow *mMainWindow;
    QPoint mClickedPos;
    bool mMousePressed;
    bool left;
    bool right;
    bool top;
    bool bottom;
};

