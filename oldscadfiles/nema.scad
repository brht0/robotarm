$fn=20;

nemaw = 42;
nemah = 30;
gap = 2;
boxw = 2.5;
nema_cylinder_r = 1.5;
nema_cylinder_h = 25;
mount_hole_r = 1.8;
mount_adjust = 20;
mount_hole_offset_x = 31/2;
mount_hole_offset_y = 31/2;
epsilon = 0.1;

module centeredCube(dimensions){
    translate([0, 0, dimensions[2]/2])
        cube(dimensions, center=true);
}

module ra_triangle(base, height){
    points = [[0, 0], [base, 0], [base, height]];
    
    polygon(points=points);
}

module nemaUmpiBase(h, pos=[0,0,0]){
    translate(pos)
        translate([0, 0, nemaw/2+gap+boxw])
            rotate([90, 0, 0])
                difference(){
                    centeredCube([nemaw+2*gap+boxw*2, nemaw+2*gap+boxw*2, h+2*gap+boxw]);
                    translate([0, 0, -epsilon]) centeredCube([nemaw+2*gap, nemaw+2*gap, h+2*gap]);
                    
                }
}

module nemaMount(h, pos=[0,0,0], adjust){
    function holePositionFromCenter() = [
        [-mount_hole_offset_x, -mount_hole_offset_y],
        [-mount_hole_offset_x, mount_hole_offset_y],
        [mount_hole_offset_x, mount_hole_offset_y],
        [mount_hole_offset_x, -mount_hole_offset_y]
    ];
    
    module allHoles(){
        // mount holes
        translate([0, epsilon, nemaw/2+boxw+gap]) rotate([90, 0, 0]) makeHoles(holePositionFromCenter(), mount_hole_r, boxw+1000, adjust);
        
        // center hole
        translate([0, epsilon, nemaw/2+boxw+gap]) rotate([90, 0, 0]) makeHoles([[0, 0]], mount_hole_r*2, boxw+1000, adjust);
    }
    
    module whatToDiff(){
        translate([-(nemaw+2*gap+2*boxw+adjust)/2-epsilon, -epsilon, 2*boxw+2*gap+nemaw+epsilon])
            rotate([-90, 0, -90])
                linear_extrude(2*boxw+2*gap+nemaw+2*epsilon+adjust)
                    ra_triangle(2*gap+boxw+nemah, nemah+2*boxw+gap);
        allHoles();
    }
    
    translate(pos){
        difference(){
            translate([0, 0, nemaw/2+gap+boxw])
                rotate([90, 0, 0])
                    difference(){
                        centeredCube([nemaw+2*gap+boxw*2+adjust, nemaw+2*gap+boxw*2, h+2*gap+boxw]);
                        translate([0, 0, boxw+gap+epsilon]) centeredCube([nemaw+2*gap+adjust, nemaw+2*gap, h+2*gap]);
                    }
                    
            whatToDiff();
        }
    }
}

module nema(h, pos=[0,0,0]){
    if(0){
        
    color([1, 0, 0])
    
    #translate(pos){
        rotate([90, 0, 0]){
            centeredCube([nemaw, nemaw, h]);
            translate([0, 0, -nema_cylinder_h]) cylinder(r=nema_cylinder_r, h=nema_cylinder_h);
        }
    }
    
} 
}

module nemaWithUmpiBase(pos){
    union(){
        nemaUmpiBase(nemah, pos);
        translate([0, 0, nemaw/2+gap+boxw]) nema(nemah, pos);
    }
}

module makeHoles(positions, r, h, adjust = 1){
    union(){
        for (i = [0 : 1 : len(positions)-1]) {
            translate(positions[i])
            hull(){
                translate([-adjust/2, 0, 0]) cylinder(r=r, h=h);
                translate([adjust/2, 0, 0]) cylinder(r=r, h=h);
            }
        }
    }
}

module nemaWithMount(pos, adjust){
    difference(){
        union(){
            nemaMount(nemah, pos, adjust=adjust);
            translate([0, -(gap*2+boxw), nemaw/2+gap+boxw]) nema(nemah, pos);
            
        }
    }
}
    
base_h = 5;

module base(){
    centeredCube([200, 300, base_h]);
}

module flatGearHead(h=50, gap = 0.0){
	difference(){
		cylinder(r=50/2+gap, h=h);
4		translate([20+gap, -40, -20]) cube([45, 150, h+40]);
	}
}

module armbase(l, w, h){
	linear_extrude(h){
		hull(){
			translate([w/2, 0, 0]) circle(r=w/2);
			translate([l-w/2, 0, 0]) circle(r=w/2);
		}
	}
}

module hole(h=50, r=1.9){
	cylinder(r=r, h=h);
}

module armPiece(l=1700, w=250, h=40){
    scale([1, 1, 1] * 0.1)
	difference(){
		armbase(l, w, h);
     
        hull() gearMount([w*0.7, 0, -1], h=h+2.0);
        hull() gearMount([l-w*0.7, 0, -0.1], h=h+2.0);
//		translate([w/2, 0, -1]) flatGearHead(h=h+5, gap=2.3);
//		translate([l-w/2, 0, -1]) flatGearHead(h=h+5, gap=2.3);
	}
}

module wholeBase(){
    difference(){
        union(){
            base();
            translate([0, nemaw/2+gap+boxw, 0]) rotate([90, 0, 0]) nemaWithUmpiBase([0, 0, 0]);
            nemaWithMount([0, -50, 0], adjust=mount_adjust);
            translate([0, 0, 0]) rotate([0, 0, 180]) nemaWithMount([0, 0, 0], adjust=mount_adjust);
        }
    }
    //rotate([90, -90, 0]) armPiece();
}
    

module joint1(){
    intersection(){
        rotate([90, -90, 0]) armPiece(1400, 300, boxw*10.1); 
        translate([0, 0, nemah+boxw*2+gap*2+505]) cube([1000, 1000, 1000], center=true);
    }
    intersection(){
        translate([0, 0, -60]) rotate([90, -90, 0]) armPiece(2000, 300, boxw*20); 
        translate([0, 0, nemah+boxw*2+gap*2-536.5]) cube([1000, 1000, 1000], center=true);
    }
    nemaWithMount([0, 0, 0], adjust=mount_adjust);
}

module gearMount(pos, h=20){
    translate(pos)
        difference(){
            gearMountHull(h);
            translate([0, 0, -0.1])
                flatGearHead(h=h+2);
        }
}

module gearMountHull(h){
    hull(){
        translate([-100, 0, 0]) cylinder(r=25, h=h);
        translate([0, 0, 0]) cylinder(r=60, h=h);
        translate([100, 0, 0]) cylinder(r=25, h=h);
    }
}

gearMount([0, 0, 0], h=80);
//wholeBase();
//joint1(); 