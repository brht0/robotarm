$fn=30;

difference(){
    hull(){
        cylinder(r=24, h=5);
        translate([125, -20/2, 0]) cube([1, 20, 5]);
    }
    translate([15, 0, -0.1]) cylinder(d=3, h=1000);
    translate([-15, 0, -0.1]) cylinder(d=3, h=1000);
    translate([0, 15, -0.1]) cylinder(d=3, h=1000);
    translate([0, -15, -0.1]) cylinder(d=3, h=1000);
    
    translate([125-20, 0, -0.1]) cylinder(d=3, h=1000);
    translate([125-50, 0, -0.1]) cylinder(d=3, h=1000);
    
    
}

if(0)
difference(){
    hull(){
        cylinder(r=23, h=5);
        translate([120, -20, 0]) cube([20, 40, 10]);
    }
    translate([15, 0, -0.1]) cylinder(d=3, h=1000);
    translate([-15, 0, -0.1]) cylinder(d=3, h=1000);
    translate([0, 15, -0.1]) cylinder(d=3, h=1000);
    translate([0, -15, -0.1]) cylinder(d=3, h=1000);
    
    // screw
    translate([110, 0, 5]) rotate([0, 90, 0]) cylinder(d=3, h=33);
    
    // mutteri
    translate([110, -6, -0.1]) cube([7, 12, 20]);
    
}

