# digital-stop-watch-Atmega16
Stop Watch with ATmega16 Microcontroller using six 7-segments display using the multiplexed technique Connect 7447 decoder 4-pins to the first 4-pins in PORTC.

Use first 6-pins in PORTA as the enable/disable pins for the six 7-segments. Stop Watch counting should start once the power is connected to the MCU. Configure External Interrupt INT0 with falling edge. Connect a push button with the internal pull-up resistor. If a falling edge detected the Stop Watch time should be reset. Configure External Interrupt INT1 with raising edge. Connect a push button with the external pull-down resistor. If a raising edge detected the Stop Watch time should be paused. Configure External Interrupt INT2 with falling edge. Connect a push button with the internal pull-up resistor. If a falling edge detected the Stop Watch time should be resumed.
![image](https://user-images.githubusercontent.com/70959607/136106904-a669f68d-22ca-4ed5-9dc6-37723f2dd43e.png)

