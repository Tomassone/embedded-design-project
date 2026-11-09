# Embedded Design Project

GitHub repository dedicated to our group's project for the **Embedded and Industrial Computer Systems Design** course.

The project is a two-node embedded system: **node 1** (an ATmega162 on a custom breadboard PCB) provides the user interface — OLED display, joystick-driven menu system and game logic — while **node 2** (an ATsam3X8E, Arduino Due) controls the physical game: a motor-driven cart, a servo and a solenoid for the ping-pong ball. The two nodes communicate over a **CAN bus**.

## Repository structure

```
├── source/
│   ├── node1/          # ATmega162 firmware (Atmel Studio projects, one per exercise)
│   └── node2/          # ATsam3X8E (Arduino Due) firmware
├── resources/
│   ├── 3d_models/      # OpenSCAD models: PCB enclosure, ping-pong ball cradle
│   ├── schematics_and_pcbs/  # Breadboard schematic (PDF), PCB (STEP + STL)
│   ├── breadboard_pics/      # Photos of the finished breadboard
│   ├── videos/               # Demo video of the system
│   └── docs/                 # Reference book: Designing Embedded Hardware (Catsoulis)
└── LICENSE                  # GPL-2.0
```

## Node 1 — ATmega162 (user interface)

The `source/node1/` folder contains one Atmel Studio project per exercise, showing the
progression from bare-metal bring-up to the finished firmware:

| Project | What it covers |
|---|---|
| `ATmega162_UART_Blink` | First UART bring-up over RS232 |
| `ATmega162_UART_Blink_Interrupt_RingBuffer` | Interrupt-driven UART with ring buffer |
| `ATmega162_SRAM_Test` | External SRAM (XMEM) address-space test |
| `ATMega162_ADC_Test` | External ADC bring-up |
| `ATmega162_ADC_Joystick` | Reading the joystick through the ADC |
| `ATmega162_OLED` | OLED driver over SPI |
| `ATmega162_MenueTest` | Joystick-navigated menu system |
| `ATmega162_CAN_Test` | CAN controller driver and node-to-node loopback |
| `ATmega162_CAN_Joystick` | Full game: menus, high scores, CAN messages to node 2 |

## Node 2 — ATsam3X8E / Arduino Due (game mechanics)

The `source/node2/` folder contains the same progression for the second node:

| Project | What it covers |
|---|---|
| `NODE2CODE` | Base project skeleton (CMSIS/startup, UART, CAN) |
| `node2_can` | CAN driver and the communication protocol with node 1 |
| `node2_ex8` | Motor driver with encoder, PID position controller, solenoid |
| `ATsam3X8E_MotorControl` | Final firmware: PID cart control, servo, solenoid, IR goal detection, non-volatile settings |
| `ATmega162_final` | Final copy of the node 1 firmware (paired build) |

In-game behaviour: the joystick X axis sets the cart position setpoint (closed-loop PID on
the motor encoder), the Y axis drives the servo, and the joystick button fires the solenoid.
The IR sensor on node 2 detects goals and reports the score back to node 1.

## Hardware & resources

- **Custom breadboard PCB** for the ATmega162 — schematic PDFs plus 3D files
  (`STEP`/`STL`) in `resources/schematics_and_pcbs/`.
- **3D-printed parts** (`resources/3d_models/`, OpenSCAD):
  - `enclosure.scad` — open-top box for the breadboard PCB, generated from the measured PCB dimensions and connector cutouts.
  - `ping_pong_u_arc_base.scad` — U-shaped cradle for the ping-pong ball.
  - `support_triangle.scad` — structural support piece.
- Photos of the finished breadboard in `resources/breadboard_pics/` and a demo video in `resources/videos/`.

## Tooling

- Firmware for both nodes is developed in **Atmel Studio** (each `.zip` is a complete project).
- Node 2 builds with `make` and is flashed over the Arduino Due programming port.
- Serial console on the lab computers is **minicom** — see the lab notes below.

## Lab notes

### How to log in the "user" profile on the lab computers

+ Use this password: Sanntid15

### How to use the serial communication console

+ Use this software: minicom (run it from the terminal emulator)
+ Before doing that it is necessary to set it up with the command: `sudo minicom -s`
+ Remember to select the `/dev/ttyS0` interface for RS232 communication [A key] and the 9600 baud rate [E key] (use the **Serial port setup** option)
+ The key combination CTRL + A is used to access all the commands (CTRL + A + Z to show all of them)

## License

This project is licensed under the [GNU GPL v2](LICENSE).
