<?xml version="1.0" encoding="UTF-8"?>
<kcfg xmlns="http://www.kde.org/standards/kcfg/1.0"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.kde.org/standards/kcfg/1.0
      http://www.kde.org/standards/kcfg/1.0/kcfg.xsd" >

  <kcfgfile name="akonadi_contactrc"/>

  <group name="Show Address Settings">
    <entry type="Enum" name="ShowAddressAction">
      <choices>
        <choice name="UseBrowser"/>
        <choice name="UseExternalAddressApplication"/>
        <choice name="UseGooglemap"/>
        <choice name="UseMapquest"/>
        <choice name="UseOpenStreetMap"/>
      </choices>
      <whatsthis>Defines which application shall be used to show the postal address of a contact on a map. If 'Web Browser' is selected, an URL can be defined with placeholders for the single address parts. If 'External Application' is selected, a command with placeholders can be defined.</whatsthis>
      <default>UseOpenStreetMap</default>
    </entry>
    <entry type="String" name="AddressUrl">
      <default></default>
      <whatsthis>This URL defines the website that shall be used to show a contact's postal address.</whatsthis>
      <tooltip>The following placeholders can be used in the URL:
   %s: Street
   %r: Region
   %l: Location
   %z: Zip Code
   %c: Country ISO Code</tooltip>
    </entry>
    <entry type="String" name="AddressCommand">
      <label>Address Command</label>
      <whatsthis>This command defines the application that shall be executed to show a contact's postal address.</whatsthis>
      <tooltip>The following placeholders can be used in the command:
   %s: Street
   %r: Region
   %l: Location
   %z: Zip Code
   %c: Country ISO Code</tooltip>
    </entry>
  </group>

  <group name="Phone Dial Settings">
    <entry type="Enum" name="DialPhoneNumberAction">
      <choices>
        <choice name="UseSkype"/>
        <choice name="UseExternalPhoneApplication"/>
        <choice name="UseSflPhone"/>
        <choice name="UseEkiga"/>
        <choice name="UseSystemDefault"/>
      </choices>
      <whatsthis>Define how a phone number of a contact should be dialed. 'System Default' uses the default application configured for this on your system (e.g. KDE Connect). Selecting a specific application will use that (if installed), 'External Application' allows you to specify a dial command with placeholders manually.</whatsthis>
      <default>UseSystemDefault</default>
    </entry>
    <entry type="String" name="PhoneCommand">
      <label>Phone Command</label>
      <whatsthis>This command defines the application that shall be executed to dial a contact's phone number.</whatsthis>
      <tooltip>The following placeholders can be used in the command:
   %N: The raw number as stored in the address book.
   %n: The normalized number with all non-digit characters removed.</tooltip>
    </entry>
  </group>

  <group name="Send SMS Settings">
    <entry type="Enum" name="SendSmsAction">
      <choices>
        <choice name="UseSkypeSms"/>
        <choice name="UseExternalSmsApplication"/>
        <choice name="UseSflPhoneSms"/>
        <choice name="UseSystemDefaultSms"/>
      </choices>
      <whatsthis>Defines which application shall be used to send an SMS to the phone number of a contact. If 'System Default' is selected the default handler for SMS messages on your system will be used (e.g. KDE Connect), otherwise the selected application will be used to send the SMS message (if installed on the computer). If 'External Application' is selected, a command with placeholders can be defined.</whatsthis>
      <default>UseSystemDefaultSms</default>
    </entry>
    <entry type="String" name="SmsCommand">
      <label>SMS Command</label>
      <whatsthis>This command defines the application that shall be executed to send an SMS to a contact's phone number.</whatsthis>
      <tooltip>The following placeholders can be used in the command:
   %N: The raw number as stored in the address book.
   %n: The normalized number with all non-digit characters removed.
   %t: The text</tooltip>
    </entry>
  </group>

</kcfg>
