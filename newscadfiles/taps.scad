$fn=50;

difference(){    
    cylinder(h=17, d=2.5);
    translate([0, 0, 5]) cube([50, 1.5*0.5, 13],center=true);
    translate([0, 0, -1]) cylinder(h=200, r=0.5);
}

if(0)
hull(){
    linear_extrude(0.1) square([4,1.8*0.5],center=true);
    translate([0, 0, 12]) linear_extrude(0.1) square([2.5,1.2*0.5],center=true);
}