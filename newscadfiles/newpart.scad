$fn=40;

translate([40, 140, 0]) rotate([0, 0, 180]) difference(){
    union(){
        hull(){
            cylinder(d=22, h=5);
            translate([0, 150, 0]) cylinder(d=22, h=5);
        }
        cylinder(d=42, h=5);
        cylinder(d=15.5, h=7.0);
    }
    translate([0, 150, -1]) cylinder(d=5, h=100);
    translate([0, 85, -1]) cylinder(d=3.5,h=100); 
    translate([0, 35, -1]) cylinder(d=3.5,h=100); 
}

difference(){
    union(){
        hull(){
            cylinder(d=22, h=5);
            translate([0, 150, 0]) cylinder(d=22, h=5);
        }
        translate([0, 0, 2.5]) cube([50, 50, 5], center=true);
        
        hull(){
            translate([0, 85, 5]) cylinder(d=8,h=26); 
            translate([0, 35, 5]) cylinder(d=8,h=26); 
        }
    }
    translate([0, 150, -1]) cylinder(d=5, h=100);
    
    translate([31/2, 31/2, -1]) cylinder(d=4,h=100); 
    translate([31/2, -31/2, -1]) cylinder(d=4,h=100); 
    translate([-31/2, -31/2, -1]) cylinder(d=4,h=100); 
    translate([-31/2, 31/2, -1]) cylinder(d=4,h=100);  
    
    translate([0, 0, -1]) cylinder(d=23,h=100); 
    translate([0, 85, -1]) cylinder(d=3.5,h=100); 
    translate([0, 35, -1]) cylinder(d=3.5,h=100); 
}



