Homematic Wired Homebrew PWM/0-10V Master Dimmer + 10 digital Eing�nge
======================================================================

*** In Entwicklung! *** Work in progress! ***
// TODO: Implement dim peering params: ON_LEVEL_PRIO, RAMP_START_STEP


Das Modul HBW-IO-10-Dim-6 bietet 6 analoge Ausg�nge, davon 4 mit PWM Ausgang und 10 digitale Eing�nge.
Basis ist ein Arduino NANO mit RS485-Interface.
(Hinweis Hex Dateien: Geeignet f�r Atmel ATMEGA328p! *with_bootloader* ist ebenfalls f�r ATMEGA328p, aber inkl. dem Arduino NANO Bootloader!)

Direktes Peering m�glich (HBWLinkDimmerAdvanced & HBWLinkKey).

Die 6 analogen Ausgangskan�le geben eine Spannung von "0-10V" (alternativ "1-10V") als Dimmer aus (0-100%). Vier dieser Sechs Ausg�nge k�nnen das PWM Signal direkt ausgeben (12V Ausgangsspannung, 122,5Hz). Der PWM, bzw. Spannungsbereich kann auf ein Maximalwert von 40-100% pro Kanal konfiguriert werden.
[4..20mA, 0..20mA per Jumper?]

Die 10 Eing�nge sind galvanisch getrennt und k�nnen mit einer Gleichspannung von 4-24V betrieben werden. Die Eing�nge stehen als Sensor oder Schalterkanal gleichzeitig zur Verf�gung, d.h. pro Eingang sind zwei Kan�le vorhanden.
Die Schalterkan�le k�nnen normal als Taster/Schalter inkl. Peering genutzt werden. M�gliche Typen: PUSHBUTTON, SWITCH, MOTIONSENSOR, DOORSENSOR. (Weitere Details in HBWKey.h)
Die Sensor Kan�le m�ssen abgefragt werden (kein Peering), und liefern dann "sensor_open" oder "sensor_closed" zur�ck. (M�glichkeit der Invertierung �ber Kanalkonfiguration)
[6 mit, 4 ohne galvanische Trennung? Anschluss von PIR-Modul direkt?]

Damit FHEM das Homebrew-Device richtig erkennt, muss die hbw_io-10_dim-6.xml Datei in den Ordner FHEM/lib/HM485/Devices/xml kopiert werden (Das Device gibt sich als HW-Typ 0x96 aus).

M�gliche Dimmer-"Endstufen":
0-10V: LED Dimmer, Finder Typ 15.11 - Slave Dimmer, etc.
0-90% PWM: Eltako LUD12-230V


Standard-Pinbelegung:
(Seriell �ber USART - #define USE_HARDWARE_SERIAL)
0  - Rx RS485
1  - Tx RS485
2  - RS485 Enable
13 - Status LED
A6 - Bedientaster (Reset)
3  - PWM out (controlled by timer2)
5  - PWM out (controlled by timer0)
6  - PWM out (controlled by timer0)
9  - PWM out (controlled by timer1)
10 - PWM out (controlled by timer1)
11 - PWM out (controlled by timer2)
4  - IO1
7  - IO2
8  - IO3
12 - IO4
A0 - ADC1
A1 - ADC2
A2 - ADC3
A3 - ADC4
A4 - ADC5
A5 - ADC6


"Debug"-Pinbelegung:
4  - Rx RS485
2  - Tx RS485
3  - RS485 Enable
13 - Status LED
8 - Bedientaster (Reset)
5  - PWM out (controlled by timer0)
6  - PWM out (controlled by timer0)
9  - PWM out (controlled by timer1)
10 - PWM out (controlled by timer1)
11 - PWM out (controlled by timer2)
4  - IO1
7  - IO2
A5 - IO3
12 - IO4
A0 - ADC1
A1 - ADC2
A2 - ADC3
A3 - ADC4
A4 - ADC5
