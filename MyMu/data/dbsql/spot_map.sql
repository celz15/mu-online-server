DROP TABLE IF EXISTS maps_spots;
CREATE TABLE IF NOT EXISTS maps_spots(
	spot_id int not null auto_increment,
	spot_map int ,
	spot_desc text default '',	
	spot_bx int ,
	spot_by int,
	spot_ex int,
	spot_ey int,
	spot_mobtype int,
	spot_mobCount int,
primary key(spot_id)
);
