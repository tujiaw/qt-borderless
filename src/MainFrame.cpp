#include "MainFrame.h"
#include "TitleBar.h"
#include "HoverMoveFilter.h"

MainFrame::MainFrame()
{
    mMousePressed = false;
    setFrameShape(Panel);

    // Make this a borderless window which can't
    // be resized or moved via the window system
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Dialog);

    // Event tricks
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    installEventFilter(new HoverMoveFilter(this));

    // Title
    mTitleBar = new TitleBar(this, "Borderless window");

    mMainWindow = new QMainWindow(this);
    mMainWindow->setWindowFlags(Qt::Widget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mTitleBar);
    mainLayout->setMargin(WINDOW_MARGIN);
    mainLayout->setSpacing(0);

    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->addWidget(mMainWindow);
    contentLayout->setMargin(WINDOW_MARGIN);
    contentLayout->setSpacing(0);
    mainLayout->addLayout(contentLayout);
}

void MainFrame::setContentWidget(QWidget *content)
{
    mMainWindow->setCentralWidget(content);
}

bool MainFrame::nativeEvent(const QByteArray &, void *message, long *result) {
    MSG* msg = reinterpret_cast<MSG*>(message);

    switch(msg->message) {
      case WM_NCCALCSIZE:
        *result = 0;
        return true;
    }

    return false;
}

void MainFrame::mousePressEvent(QMouseEvent *e)
{
    // mOldPos = e->pos();
    mMousePressed = e->button() == Qt::LeftButton;
    if (mMousePressed) {
        if (left) {
            mClickedPos.setX(e->pos().x());
        }
        if (right) {
            mClickedPos.setX(width() - e->pos().x());
        }
        if (top) {
            mClickedPos.setY(e->pos().y());
        }
        if (bottom) {
            mClickedPos.setY(height() - e->pos().y());
        }
    }
    setWindowTitle("Resizing");
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mMousePressed = false;
    }
    setWindowTitle("Borderless window");
}

void MainFrame::mouseMove(QPoint newPos, QPoint oldPos)
{
    if (mMousePressed) {
        int dx = newPos.x() - oldPos.x();
        int dy = newPos.y() - oldPos.y();

        QRect g = geometry();
        QSize minSize = minimumSize();

        // We don't resize if the windows has the minimum size
        if (left) {
            if (dx < 0 && oldPos.x() > mClickedPos.x() ) {
                dx += oldPos.x() - mClickedPos.x();
                if (dx > 0) {
                    dx = 0;
                }
            } else if ( dx > 0 && g.width() - dx < minSize.width()) {
                dx = g.width() - minSize.width();
            }
            g.setLeft(g.left() + dx);
        }

        if (right) {
            if (dx > 0 && (width() - newPos.x() > mClickedPos.x())) {
                dx -= width() - newPos.x() - mClickedPos.x();
                if (dx < 0) {
                    dx = 0;
                }
            }
            g.setRight(g.right() + dx);
        }

        if (top) {
            if (dy < 0 && (oldPos.y() > mClickedPos.y())) {
                dy += oldPos.y() - mClickedPos.y();
                if (dy > 0) {
                    dy = 0;
                }
            } else if (dy > 0 && g.height() - dy < minSize.height()) {
                dy = g.height() - minSize.height();
            }
            g.setTop(g.top() + dy);
        }

        if (bottom) {
            if (dy > 0 && (height() - newPos.y() > mClickedPos.y())) {
                dy -= height() - newPos.y() - mClickedPos.y();
                if (dy < 0) {
                    dy = 0;
                }
            }
            g.setBottom(g.bottom() + dy);
        }

        setGeometry(g);

    } else {
        QRect r = rect();
        left = qAbs(newPos.x()- r.left()) <= WINDOW_MARGIN;
        right = qAbs(newPos.x() - r.right()) <= WINDOW_MARGIN;
        top = qAbs(newPos.y() - r.top()) <= WINDOW_MARGIN;
        bottom = qAbs(newPos.y() - r.bottom()) <= WINDOW_MARGIN;

        if ((left && bottom) || (right && top)) {
            setCursor(Qt::SizeBDiagCursor);
        } else if ((left && top) || (right && bottom)) {
            setCursor(Qt::SizeFDiagCursor);
        } else if (left || right) {
            setCursor(Qt::SizeHorCursor);
        } else if (top || bottom) {
            setCursor(Qt::SizeVerCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
}
