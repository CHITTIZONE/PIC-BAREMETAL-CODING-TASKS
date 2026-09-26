# ⚡ PIC Microcontroller Bare-Metal Coding Tasks & Mini-Projects

[![GitHub license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Microcontroller](https://img.shields.io/badge/Microcontroller-PIC16F877A%20%7C%20PIC16F887-orange.svg)](https://www.microchip.com/)
[![Toolchain](https://img.shields.io/badge/Toolchain-MPLAB%20X%20IDE%20%2F%20XC8-green.svg)](https://www.microchip.com/mplab/)
[![Coding Standard](https://img.shields.io/badge/Style-Bare--Metal%20Embedded%20C-red.svg)]()
[![Repository](https://img.shields.io/badge/Status-Public-brightgreen.svg)]()

Welcome to the **PIC Bare-Metal Coding Tasks** repository. This repository contains a complete suite of **78 bare-metal embedded C firmware modules, peripheral drivers, and mini-projects** designed and implemented from scratch without high-level abstraction libraries or RTOS overhead.

All code is written for Microchip's **PIC16F877A** and **PIC16F887** 8-bit microcontrollers, directly configuring Special Function Registers (SFRs) such as `TRIS`, `PORT`, `ANSEL`, `ADCON`, `TMR0/1/2`, `TXSTA`, `RCSTA`, `SSPCON`, and `INTCON`.

---

## 📑 Table of Contents
- [Architecture & Target Hardware](#-architecture--target-hardware)
- [Repository Structure & Project Catalog](#-repository-structure--project-catalog)
  - [1. GPIO & LED Patterns](#1-gpio--led-patterns)
  - [2. 7-Segment Displays](#2-7-segment-displays)
  - [3. 16x2 Character LCD Modules](#3-16x2-character-lcd-modules)
  - [4. Analog-to-Digital Conversion (ADC) & Sensors](#4-analog-to-digital-conversion-adc--sensors)
  - [5. Timers, Counters & Hardware Interrupts](#5-timers-counters--hardware-interrupts)
  - [6. Pulse Width Modulation (PWM)](#6-pulse-width-modulation-pwm)
  - [7. Serial Communication Protocols (USART, I2C, SPI)](#7-serial-communication-protocols-usart-i2c-spi)
  - [8. Embedded Mini-Projects & Automation Systems](#8-embedded-mini-projects--automation-systems)
- [Key Peripherals & Registers Overview](#-key-peripherals--registers-overview)
- [How to Build and Simulate](#-how-to-build-and-simulate)
- [Author & Acknowledgments](#-author--acknowledgments)

---

## 🏛 Architecture & Target Hardware

| Feature | Specification |
| :--- | :--- |
| **Core Architecture** | Microchip 8-bit PIC RISC Architecture (35 Single-Word Instructions) |
| **Target Microcontrollers** | **PIC16F877A** / **PIC16F887** |
| **System Clock ($F_{OSC}$)** | 4 MHz / 8 MHz / 20 MHz Quartz Crystal or Internal Oscillator |
| **Core Supply Voltage** | 5.0 V DC |
| **IDE / Toolchains** | MPLAB X IDE v5.xx / v6.xx, MPLAB v8, Microchip XC8 Compiler, HI-TECH C |
| **Simulation Platform** | Labcenter Electronics Proteus VSM |
| **Programmer / Debugger** | PICkit 2 / PICkit 3 / PICkit 4 / ICD3 |

---

## 📂 Repository Structure & Project Catalog

The repository is organized into distinct standalone modules and MPLAB X projects (`.X`):

### 1. GPIO & LED Patterns
Bare-metal bitwise manipulation of `TRIS` (direction) and `PORT`/`LAT` registers with pushbuttons, cascading sequences, and decorative algorithmic sweeps:

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`BLINK`](BLINK/) | `BLINK_LED.c` | Fundamental bare-metal LED blink with software timing delay loop. |
| [`INPUT_LED_BLINK`](INPUT_LED_BLINK/) | `PUSH_BTN_LED.c` | Pushbutton active-low/high input polling driving LED status. |
| [`7_BTN_7_LED`](7_BTN_7_LED/) | `7_BTN_7_LED.C` | 7-to-7 mapping: 7 discrete tactile switches controlling 7 independent LEDs. |
| [`TASK1 Sequence 2 Led`](TASK1%20Sequence%202%20Led/) | `SEQ_2_LED.c` | Alternating 2-LED sequencing pattern. |
| [`TASK2 8 LED`](TASK2%208%20LED/) | `8_LED_sequence.c` | 8-LED sequential running chase / cascade on `PORTD`. |
| [`LED SERIES BLINK`](LED%20SERIES%20BLINK/) | `SERIESLED_BLINK.C` | Progressive cascading series LED illumination. |
| [`LED WITH NUMBER`](LED%20WITH%20NUMBER/) | `LED_COUNT_NUMBER.c` | Binary counter output rendered across PORT LEDs. |
| [`FORWARD BACKWARD LED`](FORWARD%20BACKWARD%20LED/) | `FRD_BCK_LED.c` | Bidirectional Knight Rider / Larson scanner LED chase. |
| [`Vpattern`](Vpattern/) | `V_pattern.c` | V-shaped symmetrical sweeping LED pattern. |
| [`V_PATTEREN_4_LED`](V_PATTEREN_4_LED/) | `V_PATTERN_4_FOR.c` | Multi-loop structured V-sweep with synchronized 4-LED clusters. |
| [`XPAETTERN`](XPAETTERN/) | `X_patteren.c` | Symmetrical X-shaped matrix LED crossing pattern. |
| [`interchange`](interchange/) | `interchange.c` | Alternating nibble and bit-swap visual pattern on PORTB. |
| [`INTERLOCK`](INTERLOCK/) | `interlock.c` | Safety interlock logic preventing conflicting simultaneous activations. |
| [`TEST_LED.X`](TEST_LED.X/) | `newmain.c` | MPLAB X structured template for GPIO diagnostic and validation. |

---

### 2. 7-Segment Displays
Driving single and multiplexed 7-segment Common Cathode (CC) and Common Anode (CA) displays:

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`SEGMENT DISPLAY`](SEGMENT%20DISPLAY/) | `segment.c` | Basic 0–9 hex/decimal digit decoder mapped to 7-segment segments. |
| [`7_segment_2CC`](7_segment_2CC/) | `7_segment_2d.c` | 2-digit Common Cathode (CC) multiplexed counter with persistence of vision (POV). |
| [`7 X2 segment single for`](7%20X2%20segment%20single%20for/) | `single_for.c` | Memory-efficient 2-digit multiplexing algorithm using a single unified `for` loop. |
| [`7 segment display intreupt`](7%20segment%20display%20intreupt/) | `segment_intrupt.c` | Hardware interrupt-driven display refresh to eliminate CPU busy-wait loops. |
| [`INTERRUPT_SEG`](INTERRUPT_SEG/) | `INTERRUPT_SEG.c` | External interrupt (`INT0`) edge-triggered increment/decrement for 7-segment counter. |
| [`TIMER_SEGMENT`](TIMER_SEGMENT/) | `TIMER_SEGMENT.c` | Timer overflow ISR multiplexing display digits at standard 100 Hz refresh rate. |
| [`KEYPAD WITH 7 SEGMENT DISPLAY`](KEYPAD%20WITH%207%20SEGMENT%20DISPLAY/) | `7SEGMENT_DISPLAY_KEYPAD.C` | 4x4 matrix keypad scanner displaying pressed numerical key directly on 7-segment. |

---

### 3. 16x2 Character LCD Modules
HD44780-compliant 16-column x 2-row alphanumeric LCD drivers implementing command, data, and cursor handling:

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`16X2 LCD`](16X2%20LCD/) | `lcd.c` | Core 16x2 LCD initialization (8-bit bus, function set `0x38`, display on `0x0E`, cursor `0x80`). |
| [`16X2LCDFORWARD AND BACKWARD`](16X2LCDFORWARD%20AND%20BACKWARD/) | `16X2LCD_FRD_BCK.c` | Dynamic bidirectional text shift and scrolling effects. |
| [`16X2LCD_NUMBER_CHECK`](16X2LCD_NUMBER_CHECK/) | `LCD_NUMBER_CHECK.c` | ASCII numeric decomposition and verification on LCD. |
| [`16x2_lcd_cust_function`](16x2_lcd_cust_function/) | `custfunction_lcd.c` | Custom character generation via CGRAM (Custom Graphics RAM) programming. |
| [`LCD16X2VALUE`](LCD16X2VALUE/) | `LCD_VALUVE_KEYPAD.c` | Real-time multi-digit value entry with 4x4 matrix keypad onto LCD. |
| [`PASSWPRD`](PASSWPRD/) | `PASS_WTH_KEYPAD.C` | Secure digital passcode entry system with star masking (`*`) and access validation. |

---

### 4. Analog-to-Digital Conversion (ADC) & Sensors
10-bit Successive Approximation Register (SAR) ADC drivers for analog signal acquisition:

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`ADC.X`](ADC.X/) | `adc_lcd_raw.c` | Direct reading of `ADRESH:ADRESL` (Right-justified) and raw conversion display on LCD. |
| [`ADC_INTERRUPT.X`](ADC_INTERRUPT.X/) | `newmain.c` | Non-blocking ADC conversion utilizing the `ADIE` interrupt flag. |
| [`ADC_LED.X`](ADC_LED.X/) | `ADC_LED.c` | Analog input level represented as an 8-stage LED bar-graph. |
| [`ADC_TEMP_LM35.X`](ADC_TEMP_LM35.X/) | `ADC_LCD_LM35.c` | Precision temperature sensor interfacing ($10\text{ mV}/^\circ\text{C}$) with Celsius calculation. |
| [`ADC_VOLTAGE_LCD.X`](ADC_VOLTAGE_LCD.X/) | `ADC_VOLTAGE_LCD.c` | Digital voltmeter measuring $0.00\text{ V} - 5.00\text{ V}$ with floating-point display on LCD. |
| [`ADC_v_v2.X`](ADC_v_v2.X/) | `newmain.c` | Enhanced ADC multi-channel scanning implementation. |
| [`PROJECT_THEROMOTER.X`](PROJECT_THEROMOTER.X/) | `newmain.c` | Complete digital room thermometer system with high-temperature alert threshold. |
| [`TEMP_v2.X`](TEMP_v2.X/) | `newmain.c` | Calibrated temperature measurement module with smoothing filter. |

---

### 5. Timers, Counters & Hardware Interrupts
Precision hardware timing using on-chip Timer0 (8-bit), Timer1 (16-bit), and Timer2 (8-bit with PR2 match):

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`TIMER`](TIMER/) | `timer.c` | Bare-metal polling of timer overflow flag (`T0IF`). |
| [`TIMER0_INTERRUPT`](TIMER0_INTERRUPT/) | `Timer0_interrupt.c` | High-precision tick generator utilizing Timer0 overflow ISR. |
| [`TIMER1_TASK1.X`](TIMER1_TASK1.X/) | `TIMER1_TASK.c` | 16-bit Timer1 configuration with prescaler for long-period timing. |
| [`TIMER2_LED.X`](TIMER2_LED.X/) | `main.c` | Timer2 period match (`PR2`) driving LED state toggle. |
| [`TIMER2_LEDBLINK.X`](TIMER2_LEDBLINK.X/) | `TIMER_BLINK.C` | Timer2 prescaler and postscaler multi-rate LED blinking. |
| [`TIMER2_LEDBLINK2.X`](TIMER2_LEDBLINK2.X/) | `LEDBLINKYIMER2.c` | Precise millisecond timing generator using Timer2. |
| [`COUNTER0_LCD_COUNT.X`](COUNTER0_LCD_COUNT.X/) | `COUNTER_LCD_COUNT.c` | Timer0 configured as asynchronous external pulse counter (`T0CKI`) displayed on LCD. |
| [`INTRRUPT`](INTRRUPT/) | `interrupt_pic.c` | External interrupt on `RB0/INT` with edge-trigger configuration in `OPTION_REG`. |
| [`INTERRUPT_FRD_BCK_WITH_2BTN`](INTERRUPT_FRD_BCK_WITH_2BTN/) | `frd_bck_with_2btn_interrupt.c` | Dual external interrupt handlers toggling motor/LED direction forward and reverse. |

---

### 6. Pulse Width Modulation (PWM)
Hardware Capture/Compare/PWM (CCP) peripheral control:

| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`PWM.X`](PWM.X/) | `pwm.c` | Hardware CCP1 PWM generator setting frequency via `PR2` and duty cycle via `CCPR1L` (motor speed / brightness control). |

---

### 7. Serial Communication Protocols (USART, I2C, SPI)
Bare-metal serial communication drivers configured directly at register level:

#### Universal Synchronous Asynchronous Receiver Transmitter (USART / UART)
| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`USART_ex.X`](USART_ex.X/) | `newmain.c` | Baud rate generator setup (`SPBRG`), asynchronous TX/RX enabled. |
| [`USART_RECIVE.X`](USART_RECIVE.X/) | `newmain.c` | UART receiver with circular buffering and frame error handling. |
| [`USART_FULLY_DUPLEX.X`](USART_FULLY_DUPLEX.X/) | `newmain.c` | Full-duplex simultaneous serial transmission and reception. |
| [`USART_2_BTN.X`](USART_2_BTN.X/) | `newmain.c` | Pushbutton event serializer sending command packets over UART. |
| [`USART_TX_3BTN_3LED.X`](USART_TX_3BTN_3LED.X/) | `newmain.c` | Transmitter node: 3 pushbuttons encoded into serialized packets. |
| [`USART_RX_3BTN_3LED.X`](USART_RX_3BTN_3LED.X/) | `newmain.c` | Receiver node: Decodes incoming packets and controls 3 remote LEDs. |
| [`PIC_USART_LED_RECIVE.X`](PIC_USART_LED_RECIVE.X/) | `newmain.c` | Serial telemetry & control for switching onboard actuators. |
| [`USART_LEDON_LEDOFF_RECIVEMODE.X`](USART_LEDON_LEDOFF_RECIVEMODE.X/) | `newmain.c` | ASCII command interpreter parsing `"LEDON"` and `"LEDOFF"` over serial line. |
| [`USART_NAME_LCD_DISPLAY.X`](USART_NAME_LCD_DISPLAY.X/) | `newmain.c` | Serial message receiver streaming incoming characters directly to 16x2 LCD. |

#### Inter-Integrated Circuit (I2C)
| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`I2C_START.X`](I2C_START.X/) | `I2C_START.c` | Bare-metal I2C master protocol: Start bit, 7-bit slave address, ACK/NACK, and Stop bit generation. |
| [`I2C_DS1307.X`](I2C_DS1307.X/) | `newmain.c` | Interfacing **DS1307 Real-Time Clock (RTC)** via I2C: Reading & writing BCD time (Hours, Minutes, Seconds) and date. |

#### Serial Peripheral Interface (SPI)
| Folder | Source Files | Description |
| :--- | :--- | :--- |
| [`SPI_MASTER.X`](SPI_MASTER.X/) | `newmain.c` | Master Synchronous Serial Port (MSSP) configured as SPI Master (`SSPCON`, `SSPSTAT`, `SSPBUF`). |
| [`SPI_MASTER_STRING.X`](SPI_MASTER_STRING.X/) | `newmain.c` | Multi-byte string streaming over high-speed SPI bus. |
| [`MASTER_SLAVE_LCD.X`](MASTER_SLAVE_LCD.X/) | `newmain.c` | SPI Master-Slave communication with LCD feedback on transaction status. |
| [`DUAL_MASTER_LCD.X`](DUAL_MASTER_LCD.X/) | `DUAL_MASTER.c` | Multi-master SPI bus arbitration protocol. |
| [`FULL DUPLEX_ MASTER.X`](FULL%20DUPLEX_%20MASTER.X/) | `FULL_DUPLEX_MASTER.c` | Full-duplex SPI Master exchanging simultaneous byte streams. |
| [`FULL_DUPLEX_MASTER_SLAVE_LCD.X`](FULL_DUPLEX_MASTER_SLAVE_LCD.X/) | `FULL_DUPLEX_SLAVE.c` | Full-duplex SPI Slave receiving bytes and rendering them on 16x2 LCD. |
| [`MULTIPLE_MASTER.X`](MULTIPLE_MASTER.X/) | `MULTIPLE_MASTER.c` | Distributed multi-microcontroller SPI Master node. |
| [`MULTIPLE_SLAVE.X`](MULTIPLE_SLAVE.X/) | `MULTIPLE_SLAVE.c` | Distributed multi-microcontroller SPI Slave node with chip-select line decoding. |

---

### 8. Embedded Mini-Projects & Automation Systems
Complete working embedded applications simulating industrial control and automated systems:

| Project | Key Technologies | Description |
| :--- | :--- | :--- |
| **Intelligent Traffic Light Controller**<br>([`TIMER1 TRAFFIC`](TIMER1%20TRAFFIC/), [`TIMER_TRAFIC`](TIMER_TRAFIC/), [`TRAFFIC_INERRIPT.X`](TRAFFIC_INERRIPT.X/)) | Timer1, External Interrupts, State Machine | Multi-phase 4-way traffic junction sequencer with configurable green/yellow/red timing intervals and pedestrian interrupt override. |
| **Traffic Controller with LCD Countdown**<br>([`TIMER_TRAFFIC_LCD`](TIMER_TRAFFIC_LCD/)) | Timer0/1, 16x2 Character LCD | Real-time digital countdown timer showing exact seconds remaining for each traffic lane on 16x2 LCD display. |
| **Automated Washing Machine Controller**<br>([`TIMER_INTERRUPT_WASHING`](TIMER_INTERRUPT_WASHING/), [`test_washimg`](test_washimg/)) | Hardware Timers, State Machine, Relays/LEDs | Industrial automation cycle controller managing sequential Soak $\rightarrow$ Wash $\rightarrow$ Rinse $\rightarrow$ Spin operations with pause/resume functionality. |
| **Digital Thermometer & Overheat Protection**<br>([`PROJECT_THEROMOTER.X`](PROJECT_THEROMOTER.X/)) | ADC, LM35 Sensor, 16x2 LCD | Continuous ambient temperature monitoring with Celsius readouts on LCD and automatic relay/buzzer trigger on exceeding safe temperature threshold. |
| **Passcode Security Lock**<br>([`PASSWPRD`](PASSWPRD/)) | 4x4 Matrix Keypad, 16x2 LCD | Security keypad lock with hidden entry masking, master passcode comparison, success unlock pulse, and retry limit penalty. |
| **PIR Motion Security Detection**<br>([`pir_ORDER.X`](pir_ORDER.X/)) | Passive Infrared (PIR) Sensor, GPIO | Motion detector triggering security sequence and alarm upon detecting human infrared radiation. |
| **Relay Actuation Controller**<br>([`RELAY`](RELAY/)) | Optoisolated Relay Driver, GPIO | Safe inductive load switching with flywheel diode protection simulation. |
| **Inter-Chip PIC-Arduino Bridge**<br>([`ARDUINO TEST.X`](ARDUINO%20TEST.X/)) | USART / GPIO | Cross-platform hardware bridge enabling data exchange between PIC16F microcontroller and Arduino AVR platform. |

---

## 🔧 Key Peripherals & Registers Overview

### 1. Special Function Registers (SFRs) Cheat Sheet
- **Direction & I/O Control**:
  - `TRISx = 0x00;` $\rightarrow$ Configure all pins of Port $x$ as Outputs.
  - `TRISx = 0xFF;` $\rightarrow$ Configure all pins of Port $x$ as Inputs.
  - `ANSEL / ANSELH = 0x00;` $\rightarrow$ Configure analog-capable pins as Digital I/O (PIC16F887).
- **Analog-to-Digital Converter**:
  - `ADCON0 = 0x81;` $\rightarrow$ $F_{OSC}/32$ clock, Channel 0 (AN0), ADC enabled (`ADON = 1`).
  - `ADCON1 = 0x80;` $\rightarrow$ Right justified result in `ADRESH:ADRESL`, $V_{REF+} = V_{DD}$, $V_{REF-} = V_{SS}$.
  - `GO_DONE = 1;` $\rightarrow$ Initiate conversion; wait while `GO_DONE == 1`.
- **Serial Communication (USART)**:
  - `TXSTA = 0x24;` $\rightarrow$ High-speed baud rate (`BRGH = 1`), 8-bit transmission enabled (`TXEN = 1`).
  - `RCSTA = 0x90;` $\rightarrow$ Serial port enabled (`SPEN = 1`), Continuous reception enabled (`CREN = 1`).
  - `SPBRG = ((_XTAL_FREQ / (16 * BAUD)) - 1);` $\rightarrow$ Baud rate calculation formula.

---

## 🚀 How to Build and Simulate

### Option 1: Using MPLAB X IDE
1. Open **MPLAB X IDE** (v5.40 or newer recommended).
2. Go to **File $\rightarrow$ Open Project...**
3. Browse to any folder ending in `.X` (e.g., `ADC.X`, `I2C_DS1307.X`, `PWM.X`).
4. Select the project and ensure **XC8** is selected as the compiler.
5. Click **Clean and Build Project** (Hammer and Brush icon or `Shift + F11`).
6. The generated `.hex` binary will be located inside `<ProjectName>.X/dist/default/production/`.

### Option 2: Pre-compiled `.hex` for Proteus VSM
For immediate testing and simulation in **Proteus VSM**:
1. Open Proteus and place a `PIC16F877A` or `PIC16F887` microcontroller.
2. Double-click the PIC component to open its properties.
3. In **Program File**, browse to the respective folder and select the `.hex` file.
4. Set **Processor Clock Frequency** to `4MHz` or `20MHz` (as defined in code `_XTAL_FREQ`).
5. Click **Run Simulation** to see the hardware circuit in action!

---

## 👤 Author & Acknowledgments

- **Author**: CHITTIZONE ([GitHub: @CHITTIZONE](https://github.com/CHITTIZONE))
- **Domain**: Embedded Systems Engineering, Bare-Metal Firmware Development, IoT & Automation
- **Microcontrollers**: Microchip PIC16F Series (PIC16F877A, PIC16F887)

---

## 📄 License
This project is open-source under the [MIT License](LICENSE). Feel free to use, modify, and reference this code in your own embedded engineering projects, academic studies, or hardware prototyping.
