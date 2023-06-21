/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "textbrowser_p.h"
#include <KCodecs>
#include <KLocalizedString>
#include <KStandardAction>
#include <QAction>
#include <QUrl>

#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QMenu>
#include <QRegularExpression>
#include <QTextBlock>

using namespace ContactEditor;

TextBrowser::TextBrowser(QWidget *parent)
    : QTextBrowser(parent)
{
    setOpenLinks(false);
}

void TextBrowser::slotCopyData()
{
#ifndef QT_NO_CLIPBOARD
    QClipboard *clip = QApplication::clipboard();
    // put the data into the mouse selection and the clipboard
    if (mDataToCopy.userType() == QMetaType::QPixmap) {
        clip->setPixmap(mDataToCopy.value<QPixmap>(), QClipboard::Clipboard);
        clip->setPixmap(mDataToCopy.value<QPixmap>(), QClipboard::Selection);
    } else {
        clip->setText(mDataToCopy.toString(), QClipboard::Clipboard);
        clip->setText(mDataToCopy.toString(), QClipboard::Selection);
    }
#endif
}

#ifndef QT_NO_CONTEXTMENU
void TextBrowser::contextMenuEvent(QContextMenuEvent *event)
{
#ifndef QT_NO_CLIPBOARD
    QMenu popup;

    QAction *act = KStandardAction::copy(this, &TextBrowser::copy, this);
    act->setEnabled(!textCursor().selectedText().isEmpty());
    act->setShortcut(QKeySequence());
    popup.addAction(act);

    // Create a new action to correspond with what is under the click
    act = new QAction(i18nc("@action:inmenu Copy the text of a general item", "Copy Item"), this);

    mDataToCopy.clear(); // nothing found to copy yet

    QString link = anchorAt(event->pos());
    if (!link.isEmpty()) {
        if (link.startsWith(QLatin1String("mailto:"))) {
            mDataToCopy = KCodecs::decodeRFC2047String(QUrl(link).path());
            // Action text matches that used in KMail
            act->setText(i18nc("@action:inmenu Copy a displayed email address", "Copy Email Address"));
        } else {
            // A link, but it could be one of our internal ones.  There is
            // no point in copying these.  Internal links are always in the
            // form "protocol:?argument", whereas valid external links should
            // be in the form starting with "protocol://".
            if (!link.contains(QRegularExpression(QStringLiteral("^\\w+:\\?")))) {
                mDataToCopy = link;
                // Action text matches that used in Konqueror
                act->setText(i18nc("@action:inmenu Copy a link URL", "Copy Link URL"));
            }
        }
    }

    if (!mDataToCopy.isValid()) { // no link was found above
        QTextCursor curs = cursorForPosition(event->pos());
        QString text = curs.block().text(); // try the text under cursor

        if (!text.isEmpty()) {
            // curs().block().text() over an image (contact photo or QR code)
            // returns a string starting with the character 0xFFFC (Unicode
            // object replacement character).  See the documentation for
            // QTextImageFormat.
            if (text.startsWith(QChar(0xFFFC))) {
                QTextCharFormat charFormat = curs.charFormat();
                if (charFormat.isImageFormat()) {
                    const QTextImageFormat imageFormat = charFormat.toImageFormat();
                    const QString imageName = imageFormat.name();
                    const QVariant imageResource = document()->resource(QTextDocument::ImageResource, QUrl(imageName));

                    const auto pix = imageResource.value<QPixmap>();
                    if (!pix.isNull()) {
                        // There may be other images (e.g. contact type icons) that
                        // there is no point in copying.
                        if (imageName == QLatin1String("contact_photo")) {
                            mDataToCopy = pix;
                            act->setText(i18nc("@action:inmenu Copy a contact photo", "Copy Photo"));
                        } else if (imageName == QLatin1String("qrcode")) {
                            mDataToCopy = pix;
                            act->setText(i18nc("@action:inmenu Copy a QR code image", "Copy Code"));
                        }
                    }
                }
            } else {
                // Added by our formatter (but not I18N'ed) for a mobile
                // telephone number.  See
                // kdepim/kaddressbook/grantlee/grantleecontactformatter.cpp and
                // kdepimlibs/akonadi/contact/standardcontactformatter.cpp
                text.remove(QRegularExpression(QStringLiteral("\\s*\\(SMS\\)$")));

                // For an item which was formatted with line breaks (as <br>
                // in HTML), the returned text contains the character 0x2028
                // (Unicode line separator).  Convert any of these back to newlines.
                text.replace(QChar(0x2028), QLatin1Char('\n'));

                mDataToCopy = text;
            }
        }
    }

    if (mDataToCopy.isValid()) {
        connect(act, &QAction::triggered, this, &TextBrowser::slotCopyData);
    } else {
        act->setEnabled(false);
    }

    popup.addAction(act);
    popup.exec(event->globalPos());
#endif
}

#endif

#include "moc_textbrowser_p.cpp"
