#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent, const QString &text)
    : QWidget(parent)
{
    // Don't let this widget inherit the parent's backround color
    setAutoFillBackground(true);
    // Use a brush with a Highlight color role to render the background
    //setBackgroundRole(QPalette::Highlight);
    setPalette(QPalette(Qt::darkBlue));


    mMinimizeButton = new QToolButton(this);
    mMaximizeButton = new QToolButton(this);
    mCloseButton= new QToolButton(this);

    // Use the style to set the button pixmaps
    QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    mCloseButton->setIcon(pix);

    mMaxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    mMaximizeButton->setIcon(mMaxPix);

    pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    mMinimizeButton->setIcon(pix);

    mRestorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    mMinimizeButton->setMinimumHeight(20);
    mCloseButton->setMinimumHeight(20);
    mMaximizeButton->setMinimumHeight(20);


    mLabel = new QLabel(this);
    mLabel->setText(text);

    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(mLabel);
    hbox->addWidget(mMinimizeButton);
    hbox->addWidget(mMaximizeButton);
    hbox->addWidget(mCloseButton);

    hbox->insertStretch(1, 500);
    hbox->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mMaxNormal = false;

    connect(mCloseButton, SIGNAL( clicked() ), parent, SLOT(close()));
    connect(mMinimizeButton, SIGNAL( clicked() ), this, SLOT(showSmall()));
    connect(mMaximizeButton, SIGNAL( clicked() ), this, SLOT(showMaxRestore()));
}

void TitleBar::setTitleText(const QString &text)
{
    mLabel->setText(text);
}

void TitleBar::showSmall()
{
    parentWidget()->showMinimized();
}

void TitleBar::showMaxRestore()
{
    if (mMaxNormal) {
        parentWidget()->showNormal();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(mMaxPix);
    } else {
        parentWidget()->showMaximized();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(mRestorePix);
    }
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    mStartPos = me->globalPos();
    mClickPos = mapToParent(me->pos());
}

void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (mMaxNormal) {
        return;
    }

    if (mClickPos.x() < WINDOW_MARGIN || mClickPos.x() > this->width() - WINDOW_MARGIN || mClickPos.y() <  WINDOW_MARGIN) {
        return;
    }
    parentWidget()->move(me->globalPos() - mClickPos);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        showMaxRestore();
    }
}
