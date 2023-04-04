# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMAddTests)

ecm_qt_declare_logging_category(akonadi_serializer_autotest_addressee_SRCS HEADER serializer_debug.h IDENTIFIER AKONADI_SERIALIZER_CONTACT_LOG CATEGORY_NAME org.kde.pim.contact_serializer)

ecm_add_test(addresseeserializertest.cpp ../akonadi_serializer_addressee.cpp ${akonadi_serializer_autotest_addressee_SRCS}
    LINK_LIBRARIES KPim6::AkonadiCore KPim6::AkonadiContact KF6::Contacts KF6::I18n Qt::Core Qt::Test
    TEST_NAME addresseeserializertest
)
