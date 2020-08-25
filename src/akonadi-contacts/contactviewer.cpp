/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactviewer.h"

#include "contactmetadataakonadi_p.h"
#include "attributes/contactmetadataattribute_p.h"
#include "customfieldmanager_p.h"
#include "standardcontactformatter.h"
#include "textbrowser_p.h"

#include <KIOCore/kio/transferjob.h>
#include <collection.h>
#include <collectionfetchjob.h>
#include <entitydisplayattribute.h>
#include <item.h>
#include <itemfetchscope.h>
#include <kcontacts/addressee.h>
#include <KColorScheme>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KStringHandler>

#include <QVBoxLayout>
#include <QIcon>
#include <QUrlQuery>
#include <QGuiApplication>
#include <QScreen>
#include <prison/Prison>
#include <kcontacts/vcardconverter.h>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactViewer::Private
{
public:
    Private(ContactViewer *parent)
        : mParent(parent)
    {
        mStandardContactFormatter = new StandardContactFormatter;
        mContactFormatter = mStandardContactFormatter;
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        mShowQRCode = group.readEntry("QRCodes", true);
        mQRCode = Prison::createBarcode(Prison::QRCode);
    }

    ~Private()
    {
        delete mStandardContactFormatter;
        delete mQRCode;
    }

    void updateView(const QVariantList &localCustomFieldDescriptions = QVariantList(), const QString &addressBookName = QString())
    {
        static QPixmap defaultPixmap = QIcon::fromTheme(QStringLiteral("user-identity")).pixmap(QSize(100, 100));
        static QPixmap defaultMapPixmap = QIcon::fromTheme(QStringLiteral("map-symbolic")).pixmap(QSize(16, 16));
        static QPixmap defaultSmsPixmap = QIcon::fromTheme(KContacts::Impp::serviceIcon(QStringLiteral("sms"))).pixmap(QSize(16, 16));

        mParent->setWindowTitle(i18nc("@title:window", "Contact %1", mCurrentContact.assembledName()));

        if (mCurrentContact.photo().isIntern()) {
            mBrowser->document()->addResource(QTextDocument::ImageResource,
                                              QUrl(QStringLiteral("contact_photo")),
                                              mCurrentContact.photo().data());
        } else if (!mCurrentContact.photo().url().isEmpty()) {
            QByteArray imageData;
            QImage image;
            KIO::TransferJob *job = KIO::get(QUrl(mCurrentContact.photo().url()), KIO::NoReload);
            QObject::connect(job, &KIO::TransferJob::data,
                             [&imageData](KIO::Job *, const QByteArray &data) {
                imageData.append(data);
            });
            if (job->exec()) {
                if (image.loadFromData(imageData)) {
                    mBrowser->document()->addResource(QTextDocument::ImageResource,
                                                      QUrl(QStringLiteral("contact_photo")),
                                                      image);
                } else {
                    mBrowser->document()->addResource(QTextDocument::ImageResource,
                                                      QUrl(QStringLiteral("contact_photo")),
                                                      defaultPixmap);
                }
            } else {
                mBrowser->document()->addResource(QTextDocument::ImageResource,
                                                  QUrl(QStringLiteral("contact_photo")),
                                                  defaultPixmap);
            }
        } else {
            mBrowser->document()->addResource(QTextDocument::ImageResource,
                                              QUrl(QStringLiteral("contact_photo")),
                                              defaultPixmap);
        }

        if (mCurrentContact.logo().isIntern()) {
            mBrowser->document()->addResource(QTextDocument::ImageResource,
                                              QUrl(QStringLiteral("contact_logo")),
                                              mCurrentContact.logo().data());
        } else if (!mCurrentContact.logo().url().isEmpty()) {
            QByteArray imageData;
            QImage image;
            KIO::TransferJob *job = KIO::get(QUrl(mCurrentContact.logo().url()), KIO::NoReload);
            QObject::connect(job, &KIO::TransferJob::data,
                             [&imageData](KIO::Job *, const QByteArray &data) {
                imageData.append(data);
            });
            if (job->exec()) {
                if (image.loadFromData(imageData)) {
                    mBrowser->document()->addResource(QTextDocument::ImageResource,
                                                      QUrl(QStringLiteral("contact_logo")),
                                                      image);
                }
            }
        }

        mBrowser->document()->addResource(QTextDocument::ImageResource,
                                          QUrl(QStringLiteral("map_icon")),
                                          defaultMapPixmap);

        mBrowser->document()->addResource(QTextDocument::ImageResource,
                                          QUrl(QStringLiteral("sms_icon")),
                                          defaultSmsPixmap);

        if (mShowQRCode) {
            KContacts::VCardConverter converter;
            KContacts::Addressee addr(mCurrentContact);
            addr.setPhoto(KContacts::Picture());
            addr.setLogo(KContacts::Picture());
            const QString data = QString::fromUtf8(converter.createVCard(addr));
            if (mQRCode) {
                mQRCode->setData(data);
                mBrowser->document()->addResource(QTextDocument::ImageResource,
                                                  QUrl(QStringLiteral("qrcode")),
                                                  mQRCode->toImage(mQRCode->preferredSize(QGuiApplication::primaryScreen()->devicePixelRatio()).toSize()));
            }
        }

        // merge local and global custom field descriptions
        QVector<QVariantMap> customFieldDescriptions;
        const CustomField::List globalCustomFields = CustomFieldManager::globalCustomFieldDescriptions();
        customFieldDescriptions.reserve(localCustomFieldDescriptions.count() + globalCustomFields.count());
        for (const QVariant &entry : qAsConst(localCustomFieldDescriptions)) {
            customFieldDescriptions << entry.toMap();
        }

        for (const CustomField &field : qAsConst(globalCustomFields)) {
            QVariantMap description;
            description.insert(QStringLiteral("key"), field.key());
            description.insert(QStringLiteral("title"), field.title());

            customFieldDescriptions << description;
        }

        KContacts::Addressee contact(mCurrentContact);
        if (!addressBookName.isEmpty()) {
            contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"), addressBookName);
        }

        mContactFormatter->setContact(contact);
        mContactFormatter->setCustomFieldDescriptions(customFieldDescriptions);

        mBrowser->setHtml(mContactFormatter->toHtml());
    }

    void slotUrlClicked(const QUrl &url)
    {
        const QUrlQuery query(url);
        const QString urlScheme(url.scheme());
        if (urlScheme == QLatin1String("http")
            || urlScheme == QLatin1String("https")) {
            Q_EMIT mParent->urlClicked(url);
        } else if (urlScheme == QLatin1String("phone")) {
            const int pos = query.queryItemValue(QStringLiteral("index")).toInt();

            const KContacts::PhoneNumber::List numbers = mCurrentContact.phoneNumbers();
            if (pos < numbers.count()) {
                Q_EMIT mParent->phoneNumberClicked(numbers.at(pos));
            }
        } else if (urlScheme == QLatin1String("sms")) {
            const int pos = query.queryItemValue(QStringLiteral("index")).toInt();

            const KContacts::PhoneNumber::List numbers = mCurrentContact.phoneNumbers();
            if (pos < numbers.count()) {
                Q_EMIT mParent->smsClicked(numbers.at(pos));
            }
        } else if (urlScheme == QLatin1String("address")) {
            const int pos = query.queryItemValue(QStringLiteral("index")).toInt();

            const KContacts::Address::List addresses = mCurrentContact.addresses();
            if (pos < addresses.count()) {
                Q_EMIT mParent->addressClicked(addresses.at(pos));
            }
        } else if (urlScheme == QLatin1String("mailto")) {
            QString name, address;

            // remove the 'mailto:' and split into name and email address
            KContacts::Addressee::parseEmailAddress(url.path(), name, address);

            Q_EMIT mParent->emailClicked(name, address);
        }
    }

    void slotParentCollectionFetched(KJob *job)
    {
        mParentCollectionFetchJob = nullptr;

        QString addressBookName;

        if (!job->error()) {
            CollectionFetchJob *fetchJob = qobject_cast<CollectionFetchJob *>(job);
            if (!fetchJob->collections().isEmpty()) {
                const Collection collection = fetchJob->collections().at(0);
                addressBookName = collection.displayName();
            }
        }

        // load the local meta data of the item
        ContactMetaDataAkonadi metaData;
        metaData.load(mCurrentItem);

        updateView(metaData.customFieldDescriptions(), addressBookName);
    }

    QMetaObject::Connection mCollectionFetchJobConnection;
    KContacts::Addressee mCurrentContact;
    Item mCurrentItem;
    ContactViewer *mParent = nullptr;
    TextBrowser *mBrowser = nullptr;
    AbstractContactFormatter *mContactFormatter = nullptr;
    AbstractContactFormatter *mStandardContactFormatter = nullptr;
    CollectionFetchJob *mParentCollectionFetchJob = nullptr;
    Prison::AbstractBarcode *mQRCode = nullptr;
    bool mShowQRCode = true;
};

ContactViewer::ContactViewer(QWidget *parent)
    : QWidget(parent)
    , d(new Private(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    d->mBrowser = new TextBrowser;

    connect(d->mBrowser, &TextBrowser::anchorClicked,
            this, [this](const QUrl &url) {
        d->slotUrlClicked(url);
    });

    layout->addWidget(d->mBrowser);

    // always fetch full payload for contacts
    fetchScope().fetchFullPayload();
    fetchScope().fetchAttribute<ContactMetaDataAttribute>();
    fetchScope().setAncestorRetrieval(ItemFetchScope::Parent);
}

ContactViewer::~ContactViewer()
{
    delete d;
}

Akonadi::Item ContactViewer::contact() const
{
    return ItemMonitor::item();
}

KContacts::Addressee ContactViewer::rawContact() const
{
    return d->mCurrentContact;
}

void ContactViewer::setContactFormatter(AbstractContactFormatter *formatter)
{
    if (formatter == nullptr) {
        d->mContactFormatter = d->mStandardContactFormatter;
    } else {
        d->mContactFormatter = formatter;
        delete d->mStandardContactFormatter;
        d->mStandardContactFormatter = nullptr;
    }
}

void ContactViewer::setContact(const Akonadi::Item &contact)
{
    ItemMonitor::setItem(contact);
}

void ContactViewer::setRawContact(const KContacts::Addressee &contact)
{
    d->mCurrentContact = contact;

    d->updateView();
}

void ContactViewer::itemChanged(const Item &contactItem)
{
    if (!contactItem.hasPayload<KContacts::Addressee>()) {
        return;
    }

    d->mCurrentItem = contactItem;
    d->mCurrentContact = contactItem.payload<KContacts::Addressee>();

    // stop any running fetch job
    if (d->mParentCollectionFetchJob) {
        disconnect(d->mCollectionFetchJobConnection);
        delete d->mParentCollectionFetchJob;
        d->mParentCollectionFetchJob = nullptr;
    }

    d->mParentCollectionFetchJob = new CollectionFetchJob(contactItem.parentCollection(), CollectionFetchJob::Base, this);
    d->mCollectionFetchJobConnection = connect(d->mParentCollectionFetchJob, &CollectionFetchJob::result, this, [this](KJob *job) {d->slotParentCollectionFetched(job);});
}

void ContactViewer::itemRemoved()
{
    d->mBrowser->clear();
}

void ContactViewer::updateView()
{
    itemChanged(d->mCurrentItem);
}

void ContactViewer::setShowQRCode(bool b)
{
    if (d->mShowQRCode != b) {
        d->mShowQRCode = b;
        updateView();
    }
}

bool ContactViewer::showQRCode() const
{
    return d->mShowQRCode;
}

#include "moc_contactviewer.cpp"
