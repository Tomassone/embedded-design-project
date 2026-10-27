// Parameters (mm)
pcb_length = 146.50;
pcb_width  = 118;
wall       = 2;
clearance  = 1;
height     = 20;

// Enclosure
difference() {
    cube([
        pcb_length + 2*wall + 2*clearance,
        pcb_width  + 2*wall + 2*clearance,
        height
    ]);

    translate([wall + clearance, wall + clearance, wall])
        cube([
            pcb_length + 2*clearance,
            pcb_width  + 2*clearance,
            height + 0.1
        ]);
}

// PCB reference — temporary position
%translate([0, 0])
    import("pcb.stl");