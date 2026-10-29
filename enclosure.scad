// ---------------------------------------------------------------
// PCB enclosure (open-top box, lid not included)  -  all units mm
// ---------------------------------------------------------------

// --- Board, as measured from pcb.stl -----------------------------
pcb_length = 146.5;
pcb_width  = 118;
pcb_origin = [18, -153.5];  // board corner in the STL's own coordinates
pcb_bottom = -8.155;        // lowest point of the STL (stuff under the board)
pcb_top    = 20.37;         // highest point of the STL (tallest component)

// Connectors that stick out past the board edge (STL coordinates)
// each: [x_range, y_range, z_range]
conn_left  = [[11.97, 17.84],   [-104.86, -50.87],  [2.54, 12.01]];
conn_right = [[164.95, 165.05], [-137.23, -120.23], [1.58, 12.08]];

// --- Enclosure parameters ----------------------------------------
wall       = 2;
clearance  = 1;     // gap between board edge and inner wall
air_below  = 1;     // gap between lowest part under the board and the floor
lid_gap    = 2.5;   // gap between tallest component and the top rim
ledge      = 2;     // width of the ring the board rests on
cut_margin = 1;     // extra room around connector cutouts

cut_left   = true;
cut_right  = true;  // set to false if the right-hand part doesn't need access
show_pcb   = true;  // ghost of the PCB in preview (ignored on export)

// --- Derived -----------------------------------------------------
standoff = -pcb_bottom + air_below;   // floor top -> board underside
board_z  = wall + standoff;           // z of the board underside
height   = board_z + pcb_top + lid_gap;

outer = [pcb_length + 2*wall + 2*clearance,
         pcb_width  + 2*wall + 2*clearance,
         height];

// Everything inside is placed in the STL's coordinate system,
// so measured numbers from the STL can be used as-is.
module in_pcb_space() {
    translate([wall + clearance - pcb_origin[0],
               wall + clearance - pcb_origin[1],
               board_z])
        children();
}

// Opening through a side wall, defined in STL coordinates.
module wall_cut(x0, x1, c) {
    in_pcb_space()
        translate([x0, c[1][0] - cut_margin, c[2][0] - cut_margin])
            cube([x1 - x0,
                  c[1][1] - c[1][0] + 2*cut_margin,
                  c[2][1] - c[2][0] + 2*cut_margin]);
}

// Ring the board edge rests on (board has no parts under its outer ~2 mm)
module support_ring() {
    translate([wall + clearance, wall + clearance, wall - 0.01])
        difference() {
            cube([pcb_length, pcb_width, standoff + 0.01]);
            translate([ledge, ledge, -1])
                cube([pcb_length - 2*ledge, pcb_width - 2*ledge, standoff + 2]);
        }
}

module enclosure() {
    difference() {
        cube(outer);

        // cavity: starts at `wall`, width = board + clearance on both sides
        translate([wall, wall, wall])
            cube([pcb_length + 2*clearance,
                  pcb_width  + 2*clearance,
                  height + 0.1]);

        // left wall: from just outside the outer face to inside the cavity
        if (cut_left)
            wall_cut(pcb_origin[0] - wall - clearance - 1,
                     pcb_origin[0], conn_left);

        // right wall
        if (cut_right)
            wall_cut(pcb_origin[0] + pcb_length,
                     pcb_origin[0] + pcb_length + wall + clearance + 1,
                     conn_right);
    }
    support_ring();
}

enclosure();

// PCB reference (preview only, not exported)
if (show_pcb)
    %in_pcb_space() import("pcb.stl");
