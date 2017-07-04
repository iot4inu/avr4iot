# avr4iot
INU AVR Object Toolkit for Internet of Things

This toolkit is very similar to arduino, but different in the following points:
1. The library is transparent, and the constituent C++ classes are subject to be reviewed and modified at any time for the app's purpose.
2. The toolkit is dedicated to the AVR processor.
3. The toolkit has been developed by using the Atmel Studio V6 which is a good programmers' environment.
4. Atmel Studio V6 is also used in the development of apps.
5. This is not for kids who do not want to know the programming details.
6. This is for programmers who want to learn how to write programs for iot.
7. irRemote.h has been copied, and reformatted from arduino.
8. iotDht class has been copied, and reformatted from arduino.
9. The AVR board is equipped with a character LCD at ports A and G, and a Bluetooth serial. JMOD-128-BASE has such a configuration.
10. The AVR board is controlled by textual commands which are sent from the host (PC, Smart Phone, or Smart Pad) through bluetooth or USB serial.
11. A command line parser is prepared for each class.
