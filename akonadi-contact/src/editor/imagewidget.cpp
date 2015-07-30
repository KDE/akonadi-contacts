/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "imagewidget.h"

#include <kcontacts/addressee.h>

#include <KLocalizedString>
#include <KMessageBox>
#include <kpixmapregionselectordialog.h>
#include <KUrlMimeData>
#include <KIO/TransferJob>
#include <QImageReader>
#include <QFileDialog>
#include <QtCore/QMimeData>
#include <QDrag>
#include <QImageWriter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMenu>
#include <QApplication>
#include <QUrl>
#include <QBuffer>
#include <QInputDialog>
/**
 * @short Small helper class to load image from network
 */
class ImageLoader
{
public:
    ImageLoader(QWidget *parent = Q_NULLPTR);

    QImage loadImage(const QUrl &url, bool *ok, bool selectPictureSize = true);

private:
    QWidget *mParent;
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
        QObject::connect(job, &KIO::TransferJob::data,
                         [&imageData](KIO::Job *, const QByteArray &data) {
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
        KMessageBox::sorry(mParent, i18n("This contact's image cannot be found."));
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
    , mImageLoader(0)
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
    mPicture = (mType == Photo ? contact.photo() : contact.logo());
    if (mPicture.isIntern() && !mPicture.data().isNull()) {
        mHasImage = true;
    } else if (!mPicture.isIntern() && !mPicture.url().isEmpty()){
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
    if (urls.isEmpty()) {   // oops, no data
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
    if ((event->buttons() & Qt::LeftButton) &&
            (event->pos() - mDragStartPos).manhattanLength() > QApplication::startDragDistance()) {

        if (mHasImage) {
            QDrag *drag = new QDrag(this);
            drag->setMimeData(new QMimeData());
            drag->mimeData()->setImageData(mPicture.data());
            drag->start();
        }
    }
}

void ImageWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    if (mType == Photo) {
        if (!mReadOnly) {
            menu.addAction(i18n("Change photo..."), this, SLOT(changeImage()));
            menu.addAction(i18n("Change url..."), this, SLOT(changeUrl()));
        }

        if (mHasImage) {
            menu.addAction(i18n("Save photo..."), this, SLOT(saveImage()));

            if (!mReadOnly) {
                menu.addAction(i18n("Remove photo"), this, SLOT(deleteImage()));
            }
        }
    } else {
        if (!mReadOnly) {
            menu.addAction(i18n("Change logo..."), this, SLOT(changeImage()));
            menu.addAction(i18n("Change url..."), this, SLOT(changeUrl()));
        }

        if (mHasImage) {
            menu.addAction(i18n("Save logo..."), this, SLOT(saveImage()));

            if (!mReadOnly) {
                menu.addAction(i18n("Remove logo"), this, SLOT(deleteImage()));
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
    const QString path = QInputDialog::getText(this, i18n("Add image url"), i18n("Url"), QLineEdit::Normal, mPicture.url());
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

void ImageWidget::changeImage()
{
    if (mReadOnly) {
        return;
    }

    const QList<QByteArray> supportedImage = QImageReader::supportedImageFormats();
    QString filter;
    Q_FOREACH (const QByteArray &ba, supportedImage) {
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
    Q_FOREACH (const QByteArray &ba, supportedImage) {
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
