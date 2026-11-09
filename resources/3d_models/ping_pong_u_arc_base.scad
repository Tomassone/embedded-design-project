// U-shaped half-torus cradle for a ping pong ball, with a flat circular base.

ball_d        = 40;     // ping pong ball diameter
clearance     = 1;      // gap between ball and tube (0 = ball touches exactly)
flat_d        = 30;     // diameter of the flat circular base (3 cm)
base_t        = 3;      // thickness of the base disc
wheel_radius  = ball_d / 2 + clearance;
tyre_diameter = 8;      // diameter of the tube that makes the U

$fn = 96;

ring_R   = wheel_radius + tyre_diameter / 2;   // centerline radius of the U
bottom_z = -(ring_R + tyre_diameter / 2);      // lowest point of the U

// The U: half-torus standing upright, opening upward (ball center at origin)
rotate([-90, 0, 0])
    rotate_extrude(angle = 180)
        translate([ring_R, 0])
            circle(d = tyre_diameter);

// Flat circular base, flush with the lowest point of the U
translate([0, 0, bottom_z])
    cylinder(d = flat_d, h = base_t);
