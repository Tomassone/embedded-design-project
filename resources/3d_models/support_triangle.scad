// Support triangle: base = ping pong ball diameter, height = double the base
// The 90 degree angle is at the origin, between the base (X) and the height (Y).

ball_d    = 40;            // ping pong ball diameter
base      = ball_d;        // 40 mm
height    = 2 * ball_d;  // 80 mm
thickness = 2 * ball_d;    // extrusion thickness (Z)

linear_extrude(height = thickness)
    polygon(points = [[0, 0], [base, 0], [0, height]]);
