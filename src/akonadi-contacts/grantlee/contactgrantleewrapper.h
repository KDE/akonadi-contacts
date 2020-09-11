/*
   SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AKONADICONTACTS_CONTACTGRANTLEEWRAPPER_H
#define AKONADICONTACTS_CONTACTGRANTLEEWRAPPER_H

#include <KContacts/Addressee>

namespace KAddressBookGrantlee {

/**
 * Additional properties for the KContacts::Addressee Grantlee model.
 */
class ContactGrantleeWrapper : public KContacts::Addressee
{
    Q_GADGET
    // ### those probably should eventually become i18n calls in the template itself
    Q_PROPERTY(QString addressBookLabel READ addressBookLabel)
    Q_PROPERTY(QString anniversaryLabel READ anniversaryLabel)
    Q_PROPERTY(QString assistantLabel READ assistantLabel)
    Q_PROPERTY(QString birthdayLabel READ birthdayLabel)
    Q_PROPERTY(QString departmentLabel READ departmentLabel)
    Q_PROPERTY(QString noteLabel READ noteLabel)
    Q_PROPERTY(QString managerLabel READ managerLabel)
    Q_PROPERTY(QString officeLabel READ officeLabel)
    Q_PROPERTY(QString professionLabel READ professionLabel)
    Q_PROPERTY(QString spouseLabel READ spouseLabel)

    Q_PROPERTY(QString addressBookName READ addressBookName)
    Q_PROPERTY(int age READ age)
    Q_PROPERTY(QString cryptoPreference READ cryptoPreference)
    Q_PROPERTY(QString signaturePreference READ signaturePreference)

    // ### this shouldn't be returning assembled HTML, that's a job for Grantlee
    Q_PROPERTY(QString photo READ photoImgElement)
    Q_PROPERTY(QString logo READ logoImgElement)

    // ### those two would be unnecessary if we had a proper way for formatting dates in Grantlee
    Q_PROPERTY(QString formattedBirthday READ formattedBirthday)
    Q_PROPERTY(QString formattedAnniversary READ formattedAnniversary)

public:
    ContactGrantleeWrapper();
    ContactGrantleeWrapper(const KContacts::Addressee &addr);

private:

    QString addressBookLabel() const;
    QString anniversaryLabel() const;
    QString assistantLabel() const;
    QString managerLabel() const;
    QString officeLabel() const;
    QString professionLabel() const;
    QString spouseLabel() const;

    QString addressBookName() const;
    int age() const;
    QString cryptoPreference() const;
    QString signaturePreference() const;

    QString photoImgElement() const;
    QString logoImgElement() const;

    QString formattedBirthday() const;
    QString formattedAnniversary() const;

    QVariantList imAddresses() const;
};

}

Q_DECLARE_METATYPE(KAddressBookGrantlee::ContactGrantleeWrapper)

#endif // KADDRESSBOOKGRANTLEE_CONTACTGRANTLEEWRAPPER_H
