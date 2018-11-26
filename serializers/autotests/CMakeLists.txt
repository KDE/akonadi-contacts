include(ECMAddTests)

ecm_qt_declare_logging_category(akonadi_serializer_autotest_addressee_SRCS HEADER serializer_debug.h IDENTIFIER AKONADI_SERIALIZER_CONTACT_LOG CATEGORY_NAME org.kde.pim.contact_serializer)

ecm_add_test(addresseeserializertest.cpp ../akonadi_serializer_addressee.cpp ${akonadi_serializer_autotest_addressee_SRCS}
    LINK_LIBRARIES KF5::AkonadiCore KF5::AkonadiContact KF5::Contacts KF5::I18n Qt5::Core Qt5::Test
    TEST_NAME addresseeserializertest
)
