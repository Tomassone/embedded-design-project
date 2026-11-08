# embedded-design-project

GitHub repository dedicated to our group's project for the **Embedded and Industrial Computer Systems Design** course.

The project is a two-node embedded system: an **ATmega162** "node 1" breadboard computer with an OLED menu interface, joystick input and highscores, communicating over **CAN bus** with an **ATsam3X8E (Arduino Due)** "node 2" that drives a motor with a PID controller and a solenoid. The whole board is housed in a 3D-printable OpenSCAD enclosure designed from the measured PCB geometry.

## Repository structure

```
.
├── source/
│   ├── node1/                       # ATmega162 (Atmel Studio) projects, one per milestone
│   │   ├── ATmega162_UART_Blink.zip
│   │   ├── ATmega162_UART_Blink_Interrupt_RingBuffer.zip
│   │   ├── ATmega162_SRAM_Test.zip
│   │   ├── ATMega162_ADC_Test.zip
│   │   ├── ATmega162_ADC_Joystick.zip
│   │   ├── ATmega162_OLED.zip
│   │   ├── ATmega162_MenueTest.zip
│   │   ├── ATmega162_CAN_Test.zip
│   │   ├── ATmega162_CAN_Joystick.zip
│   │   └── AtMega162_Breadboard.zip
│   ├── ATmega162_final.zip          # Final node 1 firmware (menu, game, highscore, CAN, OLED...)
│   ├── NODE2CODE.zip                # Early node 2 code
│   ├── node2_can.zip                # Node 2 CAN bring-up (Makefile + arm-none-eabi-gcc)
│   ├── node2_ex8.zip                # Node 2 exercise 8: motor, PID, solenoid, tuning
│   └── ATsam3X8E_MotorControl.zip   # Final node 2 motor-control firmware
├── enclosure.scad                   # OpenSCAD source for the 3D-printed enclosure
├── pcb.stl                          # Rendered PCB model used as enclosure reference
├── ATmega162_BreadboardPCB.step     # STEP model of the breadboard PCB
├── AtMega162_Breadboard_connected_finished.zip   # Full finished breadboard archive
├── check_dim.py                     # Prints PCB bounding-box dimensions from pcb.stl (trimesh)
├── resources/
│   ├── schematics/                  # Breadboard schematic PDFs
│   ├── breadboard_pics/             # Photos of the finished board
│   ├── videos/                      # Demo videos
│   └── docs/                        # "Designing Embedded Hardware" (Catsoulis) reference book
└── LICENSE                          # GPL-2.0
```

## Hardware

| | Node 1 | Node 2 |
|---|---|---|
| MCU | ATmega162 | ATsam3X8E (Arduino Due) |
| Peripherals | OLED (SPI), joystick + ADC, external SRAM, light bar | DC motor, encoder, solenoid |
| Communication | CAN via MCP2515 (SPI) | CAN bus controller |
| Toolchain | Atmel Studio 7 | `arm-none-eabi-gcc` + Makefile |

The two nodes exchange joystick positions and game commands over the CAN bus; node 2 runs the motor with a PID controller and fires the solenoid to "kick".

## The enclosure

`enclosure.scad` generates an open-top box (lid not included) sized from the PCB as measured in `pcb.stl`:

- 2 mm walls, 1 mm clearance around the board and 1 mm of air under it
- A support ring the board edge rests on
- Side-wall cutouts for the connectors that stick out past the board edge (toggle with `cut_left` / `cut_right`)
- A ghost preview of the PCB (`show_pcb`) for fitting checks — ignored on export

To regenerate the measured board dimensions after a PCB change, run:

```bash
pip install trimesh
python check_dim.py
```

Then render with OpenSCAD:

```bash
openscad -o enclosure.stl enclosure.scad
```

## Lab notes

### How to log in to the "user" profile in the lab computers

- Use this password: `Sanntid15`

### How to use the serial communication console

- Use this software: **minicom** (run it from the terminal emulator)
- Before doing that, set it up with: `sudo minicom -s`
- Select the `/dev/ttyS0` interface for RS232 communication [A key] and the 9600 baud velocity [E key] (use the **Serial port setup** option)
- The key combination CTRL + A is used to access all the commands (CTRL + A + Z shows all of them)

## License

This project is licensed under the [GNU General Public License v2.0](LICENSE).
