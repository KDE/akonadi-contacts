/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Felix Mauch (felix_mauch@web.de)

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

#include "smsdialog.h"

#include <kcontacts/phonenumber.h>
#include <klocalizedstring.h>
#include <kmessagebox.h>
#include <ktextedit.h>

#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

SmsDialog::SmsDialog(const KContacts::PhoneNumber &number)
    : mNumber(number.number())
{
    initUI();
}

SmsDialog::~SmsDialog()
{
}

QString SmsDialog::message() const
{
    return mText;
}

void SmsDialog::initUI()
{
    setWindowTitle(i18n("SMS text"));

    //setFixedWidth(300);

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setMargin(0);

    QLabel *label = new QLabel(i18n("Please insert SMS text for an SMS to the following number: %1", mNumber), this);
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
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
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
