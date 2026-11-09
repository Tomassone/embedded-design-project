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
progression from bare-metal bring-up to the finished firmware.

## Node 2 — ATsam3X8E / Arduino Due (game mechanics)

The `source/node2/` folder contains the same progression for the second node.

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

## License

This project is licensed under the [GNU GPL v2](LICENSE).
