/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Felix Mauch (felix_mauch@web.de)

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "smsdialog.h"

#include <KContacts/PhoneNumber>
#include <KLocalizedString>
#include <KTextEdit>

#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SmsDialog::SmsDialog(const KContacts::PhoneNumber &number)
    : mNumber(number.number())
{
    initUI();
}

SmsDialog::~SmsDialog() = default;

QString SmsDialog::message() const
{
    return mText;
}

void SmsDialog::initUI()
{
    setWindowTitle(i18nc("@title:window", "SMS text"));

    auto topLayout = new QVBoxLayout(this);

    auto label = new QLabel(i18n("Please insert SMS text for an SMS to the following number: %1", mNumber), this);
    topLayout->addWidget(label);
    label->setWordWrap(true);

    mSmsTextEdit = new KTextEdit(this);
    mSmsTextEdit->setAcceptRichText(false);
    label->setBuddy(mSmsTextEdit);
    topLayout->addWidget(mSmsTextEdit);

    connect(mSmsTextEdit, &KTextEdit::textChanged, this, &SmsDialog::updateCounter);

    mLengthLabel = new QLabel(QStringLiteral("-"), this);
    topLayout->addWidget(mLengthLabel);

    mSmsTextEdit->setFocus();
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    topLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SmsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SmsDialog::reject);

    updateCounter();
}

void SmsDialog::updateCounter()
{
    mText = mSmsTextEdit->toPlainText();
    unsigned int messageSize = 160;

    const int size = mText.length();
    for (int i = 0; i < size; ++i) {
        if (mText[i].row() > 0) {
            messageSize = 70;
            break;
        }
    }
    const int numberSms = (size - (size % messageSize)) / messageSize + 1;
    const int numberChars = messageSize * numberSms;

    mLengthLabel->setText(i18n("%1/%2 (%3 SMS)", size, numberChars, numberSms));
}
