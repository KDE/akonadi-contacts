/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Felix Mauch (felix_mauch@web.de)

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SMSDIALOG_H
#define SMSDIALOG_H

#include <QDialog>

class QLabel;

class KTextEdit;

namespace KContacts
{
class PhoneNumber;
}

class SmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SmsDialog(const KContacts::PhoneNumber &number);
    ~SmsDialog();

    Q_REQUIRED_RESULT QString message() const;

private:
    /**
     * Calculates the needed amount of sms and the number of characters left in the current sms.
     * Shows the result in the QLabel mLengthLabel.
     */
    void updateCounter();
    void initUI();

    QString mNumber;
    KTextEdit *mSmsTextEdit = nullptr;
    QLabel *mLengthLabel = nullptr;
    QString mText;
};

#endif
