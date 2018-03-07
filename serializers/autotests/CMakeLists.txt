include(ECMAddTests)

ecm_add_test(addresseeserializertest.cpp ../akonadi_serializer_addressee.cpp
    LINK_LIBRARIES KF5::AkonadiCore KF5::AkonadiContact KF5::Contacts KF5::I18n Qt5::Core Qt5::Test
    TEST_NAME addresseeserializertest
)
