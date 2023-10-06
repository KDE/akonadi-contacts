/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "imagewidget.h"

#include <KContacts/Addressee>

#include <KIO/TransferJob>
#include <KLocalizedString>
#include <KMessageBox>
#include <KPixmapRegionSelectorDialog>
#include <KUrlMimeData>
#include <QApplication>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenu>
#include <QMimeData>
#include <QUrl>
using namespace Akonadi;
/**
 * @short Small helper class to load image from network
 */
class Akonadi::ImageLoader
{
public:
    ImageLoader(QWidget *parent = nullptr);

    [[nodiscard]] QImage loadImage(const QUrl &url, bool *ok, bool selectPictureSize = true);

private:
    QWidget *const mParent;
};

ImageLoader::ImageLoader(QWidget *parent)
    : mParent(parent)
{
}

QImage ImageLoader::loadImage(const QUrl &url, bool *ok, bool selectPictureSize)
{
    QImage image;

    if (url.isEmpty()) {
        return image;
    }

    (*ok) = false;

    if (url.isLocalFile()) {
        if (image.load(url.toLocalFile())) {
            (*ok) = true;
        }
    } else {
        QByteArray imageData;
        KIO::TransferJob *job = KIO::get(url, KIO::NoReload);
        QObject::connect(job, &KIO::TransferJob::data, [&imageData](KIO::Job *, const QByteArray &data) {
            imageData.append(data);
        });
        if (job->exec()) {
            if (image.loadFromData(imageData)) {
                (*ok) = true;
            }
        }
    }

    if (!(*ok)) {
        // image does not exist (any more)
        KMessageBox::error(mParent, i18n("This contact's image cannot be found."));
        return image;
    }

    if (selectPictureSize) {
        QPixmap pixmap = QPixmap::fromImage(image);
        image = KPixmapRegionSelectorDialog::getSelectedImage(pixmap, 1, 1, mParent);
        if (image.isNull()) {
            (*ok) = false;
            return image;
        }
    }

    if (image.height() > 720 || image.width() > 720) {
        if (image.height() > image.width()) {
            image = image.scaledToHeight(720);
        } else {
            image = image.scaledToWidth(720);
        }
    }

    (*ok) = true;

    return image;
}

ImageWidget::ImageWidget(Type type, QWidget *parent)
    : QPushButton(parent)
    , mImageLoader(nullptr)
    , mType(type)
    , mHasImage(false)
    , mReadOnly(false)
{
    setAcceptDrops(true);

    setIconSize(QSize(100, 100));
    setFixedSize(QSize(120, 120));

    connect(this, &ImageWidget::clicked, this, &ImageWidget::changeImage);

    if (mType == Photo) {
        setToolTip(i18n("The photo of the contact (click to change)"));
    } else {
        setToolTip(i18n("The logo of the company (click to change)"));
    }

    updateView();
}

ImageWidget::~ImageWidget()
{
    delete mImageLoader;
}

void ImageWidget::loadContact(const KContacts::Addressee &contact)
{
    mPicture = (mType == Photo) ? contact.photo() : contact.logo();
    if (mPicture.isIntern() && !mPicture.data().isNull()) {
        mHasImage = true;
    } else if (!mPicture.isIntern() && !mPicture.url().isEmpty()) {
        mHasImage = true;
    }

    updateView();
}

void ImageWidget::storeContact(KContacts::Addressee &contact) const
{
    if (mType == Photo) {
        contact.setPhoto(mPicture);
    } else {
        contact.setLogo(mPicture);
    }
}

void ImageWidget::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;
    setAcceptDrops(!mReadOnly);
}

void ImageWidget::updateView()
{
    if (mHasImage) {
        if (mPicture.isIntern()) {
            setIcon(QPixmap::fromImage(mPicture.data()));
        } else {
            bool ok = false;
            const QPixmap pix = QPixmap::fromImage(imageLoader()->loadImage(QUrl(mPicture.url()), &ok, false));
            if (ok) {
                setIcon(pix);
            }
        }
    } else {
        if (mType == Photo) {
            setIcon(QIcon::fromTheme(QStringLiteral("user-identity")));
        } else {
            setIcon(QIcon::fromTheme(QStringLiteral("image-x-generic")));
        }
    }
}

void ImageWidget::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    event->setAccepted(mimeData->hasImage() || mimeData->hasUrls());
}

void ImageWidget::dropEvent(QDropEvent *event)
{
    if (mReadOnly) {
        return;
    }

    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasImage()) {
        mPicture.setData(qvariant_cast<QImage>(mimeData->imageData()));
        mHasImage = true;
        updateView();
    }

    const QList<QUrl> urls = KUrlMimeData::urlsFromMimeData(mimeData);
    if (urls.isEmpty()) { // oops, no data
        event->setAccepted(false);
    } else {
        bool ok = false;
        const QImage image = imageLoader()->loadImage(urls.first(), &ok);
        if (ok) {
            mPicture.setData(image);
            mHasImage = true;
            updateView();
        }
    }
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    mDragStartPos = event->pos();
    QPushButton::mousePressEvent(event);
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && (event->pos() - mDragStartPos).manhattanLength() > QApplication::startDragDistance()) {
        if (mHasImage) {
            auto drag = new QDrag(this);
            drag->setMimeData(new QMimeData());
            drag->mimeData()->setImageData(mPicture.data());
            drag->exec(Qt::CopyAction);
        }
    }
}

void ImageWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    if (mType == Photo) {
        if (!mReadOnly) {
            menu.addAction(i18n("Change photo..."), this, &ImageWidget::changeImage);
            menu.addAction(i18n("Change URL..."), this, &ImageWidget::changeUrl);
        }

        if (mHasImage) {
            menu.addAction(i18n("Save photo..."), this, &ImageWidget::saveImage);

            if (!mReadOnly) {
                menu.addAction(i18n("Remove photo"), this, &ImageWidget::deleteImage);
            }
        }
    } else {
        if (!mReadOnly) {
            menu.addAction(i18n("Change logo..."), this, &ImageWidget::changeImage);
            menu.addAction(i18n("Change URL..."), this, &ImageWidget::changeUrl);
        }

        if (mHasImage) {
            menu.addAction(i18n("Save logo..."), this, &ImageWidget::saveImage);

            if (!mReadOnly) {
                menu.addAction(i18n("Remove logo"), this, &ImageWidget::deleteImage);
            }
        }
    }

    menu.exec(event->globalPos());
}

void ImageWidget::changeUrl()
{
    if (mReadOnly) {
        return;
    }
    bool okPath = false;
    const QString path = QInputDialog::getText(this, i18n("Change image URL"), i18n("Image URL:"), QLineEdit::Normal, mPicture.url(), &okPath);
    if (okPath) {
        if (!path.isEmpty()) {
            bool ok;
            const QImage image = imageLoader()->loadImage(QUrl(path), &ok, false);
            if (ok && !image.isNull()) {
                mPicture.setUrl(path);
                mHasImage = true;
                updateView();
            }
        }
    }
}

void ImageWidget::changeImage()
{
    if (mReadOnly) {
        return;
    }

    const QList<QByteArray> supportedImage = QImageReader::supportedImageFormats();
    QString filter;
    for (const QByteArray &ba : supportedImage) {
        if (!filter.isEmpty()) {
            filter += QLatin1Char(' ');
        }
        filter += QLatin1String("*.") + QString::fromLatin1(ba);
    }

    const QUrl url = QFileDialog::getOpenFileUrl(this, QString(), QUrl(), i18n("Images (%1)", filter));
    if (url.isValid()) {
        bool ok = false;
        const QImage image = imageLoader()->loadImage(url, &ok);
        if (ok) {
            mPicture.setData(image);
            mHasImage = true;
            updateView();
        }
    }
}

void ImageWidget::saveImage()
{
    const QList<QByteArray> supportedImage = QImageWriter::supportedImageFormats();
    QString filter;
    for (const QByteArray &ba : supportedImage) {
        if (!filter.isEmpty()) {
            filter += QLatin1Char(' ');
        }
        filter += QLatin1String("*.") + QString::fromLatin1(ba);
    }

    const QString fileName = QFileDialog::getSaveFileName(this, QString(), QString(), i18n("Images (%1)", filter));
    if (!fileName.isEmpty()) {
        mPicture.data().save(fileName);
    }
}

void ImageWidget::deleteImage()
{
    mHasImage = false;
    mPicture.setData(QImage());
    mPicture.setUrl(QString());
    updateView();
}

ImageLoader *ImageWidget::imageLoader()
{
    if (!mImageLoader) {
        mImageLoader = new ImageLoader;
    }

    return mImageLoader;
}

#include "moc_imagewidget.cpp"
