/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <kcontacts/picture.h>

#include <QPoint>
#include <QPushButton>

namespace KContacts {
class Addressee;
}

class ImageLoader;

class ImageWidget : public QPushButton
{
    Q_OBJECT

public:
    enum Type {
        Photo,
        Logo
    };

    explicit ImageWidget(Type type, QWidget *parent = nullptr);
    ~ImageWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

protected:
    // image drop handling
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    // image drag handling
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    // context menu handling
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void updateView();

    void changeImage();
    void changeUrl();
    void saveImage();
    void deleteImage();
    ImageLoader *imageLoader();

    KContacts::Picture mPicture;
    QPoint mDragStartPos;
    ImageLoader *mImageLoader = nullptr;
    Type mType;
    bool mHasImage;
    bool mReadOnly;
};

#endif
