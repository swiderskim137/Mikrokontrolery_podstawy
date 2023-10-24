For Windows Vista X64 and Windows 7 X64:

First enable the "testsigning" mode,
manually by selecting Start->All Programs->Accessories->Command Prompt,
right-clicking on it, selecting "Run as administrator"
and typing the following command:
>> bcdedit -set TESTSIGNING ON

To disable testsigning mode, you need to run the following command:
>> bcdedit -set TESTSIGNING OFF

Note that you will need to restart your computer for this change to take effect.