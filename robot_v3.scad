$fn=30;

w1 = 20;
l1 = 42;
h1 = 8;
w12 = 18;
h12 = 20;
w13 = 18;
mounth=50;
mountw=55;
w14 = mountw;
h13 = 2;
d1 = 3;
supportoffset = 13;
supporth = 35;
supportw = 18;

r3 = 8;
e3 = 10;
h3b = 2;
h3c = 10;

p5r = 12.0;
p5l = 150;
p5h = 3;
p5w = 2*p5r;
p5e = e3;
p5centerw = 22;
p5supporth = 35;
p5supportgap = 13;
p5highsupportw = 40;
p5supportoffset = 18;
p5attachw = 10;

internalcircled = 22+1.5;
screw_offsetw = 31;
screw_d = 2+2;
nemaw = 42;

//p4r = 12.0;
p4l = 100;
p4d = 12.0;

module p4(){
    translate([0, 0, 0])
    rotate([0, 0, 90]){
    translate([-p4l-p5supportgap*2*d1+10, 0, 0])
    linear_extrude(p4d){
    union(){
        hull(){
            circle(d=d1);
            translate([p4l, 0, 0]) square(d1,center=true);
        }
        
        circler = p5supportgap+2*d1+10;
        circler2 = circler - d1;
        difference(){
            translate([p4l+circler, 0, 0]) circle(r=circler);
            translate([p4l+circler, 0, 0]) circle(r=circler2);
            translate([p4l+circler+5000, 0, 0]) square([10000, 10000], center=true);
        }
        
        hull(){
            translate([p4l+circler-d1/2, circler-d1*0.6, 0]) square(d1,center=true);
            translate([p4l+circler+20, circler-d1*0.6, 0]) square(d1,center=true);
        }
        
        hull(){
            translate([p4l+circler-d1/2, -circler+d1*0.6, 0]) square(d1,center=true);
            translate([p4l+circler+20, -circler+d1*0.6, 0]) square(d1,center=true);
        }
    }
    }
    }
    
//    hull(){
//    }
}

module p2(){
    // todo
}

module p5_simpleattachment(){
    mr = 3.3;
    mr2 = 1.35;
    hr = 3.2/2;
    h = 20;
    d = 45;
    difference(){
        union(){
            hull(){
                cylinder(r=mr, h=h);
                translate([mr+mr2*2, 0, 0]) cylinder(r=mr2, h=h);
            }
            hull(){
                translate([d-2*mr-mr2*2, 0, 0]) cylinder(r=mr2, h=h);
                translate([d-mr, 0, 0]) cylinder(r=mr, h=h);
            }
            hull(){
                translate([mr+mr2*2, 0, 0]) cylinder(r=mr2, h=h);
                translate([d-2*mr-mr2*2, 0, 0]) cylinder(r=mr2, h=h);
            }
            
        }
        translate([0, 0, -1]) cylinder(r=hr, h=h+2);
        translate([d-mr, 0, -1]) cylinder(r=hr, h=h+2);
    }
}

module axis1(){
//    p1();
//    p2();
//    p3();
//    p4();
//    p5();
    p5_simpleattachment();
}

axis1();

module p5(){
    difference(){
        union(){
            translate([0, 0, h1+h12+mounth/2]){
                rotate([0, -90, 0]){
                    // arm base plate (mount side)
                    intersection(){
                        translate([0, 0, p5centerw/2-p5h/2]) {
                            linear_extrude(p5h){
                                hull(){
                                    translate([0, 0, 0]) circle(r=p5r);
                                    translate([p5l, 0, 0]) circle(r=p5r);
                                }
                            }
                        }
                        translate([500+mounth/2-0.1, 0, 0]) cube([1000, 1000, 1000], center=true);
                    }
                    
                    // arm base plate (not mount side)
                    translate([0, 0, -p5centerw/2-p5h/2]){
                        linear_extrude(p5h){
                            hull(){
                                circle(r=p5r);
                                translate([p5l, 0, 0]) circle(r=p5r);
                            }
                        }
                    }
                    
                    // cylinder
                    translate([d1, 0, -p5centerw/2-h3c-d1/2+0.01])
                        cylinderMount();
                    
                    // mount support
                    translate([-mounth/2, mountw/2, p5centerw/2-d1/2])
                        rotate([0, -90, 180])
                            nema17mount();
                    
                    // support plates
                    // mount side
                    difference(){
                        union(){
                            rotate([90, 0, 0]){
                                translate([mounth/2+p5supportoffset, p5centerw/2, p5r-d1])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                                translate([mounth/2+p5supportoffset, p5centerw/2, -p5r])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                            }
                            rotate([90, 0, 0]){
                                translate([mounth/2+p5supporth +p5supportoffset+p5supportgap, p5centerw/2, p5r-d1])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                                translate([mounth/2+p5supporth +p5supportoffset+p5supportgap, p5centerw/2, -p5r])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                            }
                        }
                        translate([mounth/2+p5supportoffset+p5supporth/2, p5r+5, p5centerw/2+p5attachw/2]) rotate([90, 0, 0]) cylinder(r=1.9, h=2*p5r+10);
                        translate([mounth/2+p5supportoffset+p5supporth/2+p5supportgap+p5supporth, p5r+5, p5centerw/2+p5attachw/2]) rotate([90, 0, 0]) cylinder(r=1.9, h=2*p5r+10);
                    }
                    
                    // non-mount side
                    difference(){
                        union(){
                            rotate([90, 0, 0]){
                                translate([mounth/2+p5supportoffset, -p5centerw/2-p5attachw, p5r-d1])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                                translate([mounth/2+p5supportoffset, -p5centerw/2-p5attachw, -p5r])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                            }
                            rotate([90, 0, 0]){
                                translate([mounth/2+p5supporth +p5supportoffset+p5supportgap, -p5centerw/2-p5attachw, p5r-d1])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                                translate([mounth/2+p5supporth +p5supportoffset+p5supportgap, -p5centerw/2-p5attachw, -p5r])
                                    linear_extrude(d1)
                                        square([p5supporth, p5attachw]);
                            }
                        }
                        translate([mounth/2+p5supportoffset+p5supporth/2, p5r+5, -p5centerw/2-p5attachw/2]) rotate([90, 0, 0]) cylinder(r=1.9, h=2*p5r+10);
                        translate([mounth/2+p5supportoffset+p5supporth/2+p5supportgap+p5supporth, p5r+5, -p5centerw/2-p5attachw/2]) rotate([90, 0, 0]) cylinder(r=1.9, h=2*p5r+10);
                    }
                }
            }
        }
        
        // negative(s)
                translate([-500000, 0, h1+h12+p5l+mounth/2]) rotate([0, 90, 0]) cylinder(r=2.6, h=999999);

    }        
}


module p1(){
    translate([-r3-e3, -w1/2, 0]) linear_extrude(h1) square([l1+r3+e3, w1]);
    
    difference(){
        hull(){
            translate([l1-(r3+e3), -w1/2, h1]) linear_extrude(h1) square([w12, w1]);
            translate([l1-(r3+e3), -w14/2, h1+h12]) linear_extrude(h13) square([w13, w14]);
        }
        
        // negative
        hull(){
            translate([l1-(r3+e3)+d1+1, -w1/2 + d1, h1]) cube([100, w1-2*d1, 0.1]);
            translate([l1-(r3+e3)+d1, -w14/2 + d1, h1+h12]) cube([100, w14-2*d1, 0.01]);
        }
    }
    
    //mount
    translate([l1-(r3+e3), -mountw/2, h1+h12])
        nema17mount();
}

module p3(){
    w1temp = 2*(r3+e3);
    w2temp = 2*(r3);
    
    translate([-w1temp/2, -w2temp/2, -h3b]) linear_extrude(h3b) square([w1temp, w2temp]);
    
    translate([0, 0, -h3b-h3c+0.01])
        cylinderMount();
}


module flatheadHole(h){
    intersection(){
        cylinder(d=5, h=h);
        translate([-1.5, -5, 0]) cube([10, 10, 100]);
    }
}

module cylinderMount(){
    difference(){
        cylinder(r=r3, h=h3c);
        translate([0, 0, -0.1]) flatheadHole(h=h3c+0.2);
    }
}

module ra_triangle(base, height, depth){
    points = [[0, 0], [base, 0], [base, height]];
    
    translate([-base, 0, -depth/2]) linear_extrude(depth) polygon(points=points);
}

module nema17mount(){
    difference(){
        union(){
            //mount
            translate([+d1/2, mountw/2, mounth/2]) cube([d1, mountw, mounth], center=true);
            
            // mount support
            translate([0, d1/2, d1-0.01]) rotate([90, 0, 180]) ra_triangle(supportw, supporth, d1);
            translate([0, mountw-d1/2, d1-0.01]) rotate([90, 0, 180]) ra_triangle(supportw, supporth, d1);
                    
            // mount base
            translate([0, 0, 0]){
                rotate([0, 0, 0]){
                    linear_extrude(d1){
                        square([supportw, mountw]);
                    }
                }
            }
        }
        
        // negative(s)
        
        // center hole
        rotate([0, 90, 0]) translate([-mounth/2-d1, mountw/2, -0.1]) cylinder(d=internalcircled, h=d1+0.2);
        
        // screw holes
        rotate([0, 90, 0]) translate([-mounth/2-d1 + 0.5 * screw_offsetw, mountw/2 + 0.5 * screw_offsetw, -0.1]) cylinder(d=screw_d, h=d1+0.2);
        rotate([0, 90, 0]) translate([-mounth/2-d1 - 0.5 * screw_offsetw, mountw/2 - 0.5 * screw_offsetw, -0.1]) cylinder(d=screw_d, h=d1+0.2);
        rotate([0, 90, 0]) translate([-mounth/2-d1 - 0.5 * screw_offsetw, mountw/2 + 0.5 * screw_offsetw, -0.1]) cylinder(d=screw_d, h=d1+0.2);
        rotate([0, 90, 0]) translate([-mounth/2-d1 + 0.5 * screw_offsetw, mountw/2 - 0.5 * screw_offsetw, -0.1]) cylinder(d=screw_d, h=d1+0.2);
    }
}
