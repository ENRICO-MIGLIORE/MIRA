use db_87__fggr_a22;






insert into materials_category
values (0,CURRENT_DATE(), CURRENT_TIME(),1,1,'CW614N');

insert into materials_category
values (0,CURRENT_DATE(), CURRENT_TIME(),1,1,'CW617N');

insert into materials_category
values (0,CURRENT_DATE(), CURRENT_TIME(),1,1,'AISI304');

insert into materials_category
values (0,CURRENT_DATE(), CURRENT_TIME(),1,1,'CW614N-DW');

insert into materials_category
values (0,CURRENT_DATE(), CURRENT_TIME(),1,1,'CW617N-DW');

select * from materials_category;


insert into dictionary
values (1, 'materials_category', 'it', 'ottone', null);
insert into dictionary
values (1, 'materials_category', 'en', 'brass', null);

insert into dictionary
values (2, 'materials_category', 'it', 'ottone PTL', null);
insert into dictionary
values (2, 'materials_category', 'en', 'PTL brass', null);

insert into dictionary
values (3, 'materials_category', 'it', 'acciaio', null);
insert into dictionary
values (3, 'materials_category', 'en', 'steel', null);



insert into dictionary
values (4, 'materials_category', 'it', 'ottone', null);


insert into dictionary
values (4, 'materials_category', 'en', 'brass', null);

insert into dictionary
values (5, 'materials_category', 'it', 'ottone', null);
insert into dictionary
values (5, 'materials_category', 'en', 'brass', null);




insert into geometry 
values(0,current_date(), current_time(), 1,1,8, null, null, null,9.9);

insert into geometry 
values(0,current_date(), current_time(), 1,1,16, null, null, null,55.5);





insert into geometry 
values(0,current_date(), current_time(), 1,1,14, null, null, null,153.94);

insert into geometry 
values(0,current_date(), current_time(), 1,1,7, null, null, null,38.48);

insert into geometry 
values(0,current_date(), current_time(), 1,1,28, null, null, null,615.75);

insert into geometry 
values(0,current_date(), current_time(), 1,1,24, null, null, null,452.38);

insert into geometry 
values(0,current_date(), current_time(), 1,1,8, null, null, null,50.26);

insert into geometry 
values(0,current_date(), current_time(), 1,1,19, null, null, null,283.53);

insert into geometry 
values(0,current_date(), current_time(), 1,1,20, null, null, null,314.16);

insert into geometry 
values(0,current_date(), current_time(), 1,1,26, null, null, null,530.93);

insert into geometry 
values(0,current_date(), current_time(), 1,1,22, null, null, null,380.13);

insert into geometry 
values(0,current_date(), current_time(), 1,1,27, null, null, null,572.56);

insert into geometry 
values(0,current_date(), current_time(), 1,1,34, null, null, null,907.92);

select * from geometry;



insert into dictionary
values (3,'geometry','it','tonda', null);
insert into dictionary
values (3,'geometry','en','round', null);

insert into dictionary
values (4,'geometry','it','esagonale', null);
insert into dictionary
values (4,'geometry','en','hexagonal', null);

 
select * from dictionary where pk_table_name = 'geometry' and pk_language_pk_id = 'it';

select * from suppliers;
select * from bars_length;

-- 5  8.43--cw617
-- (0,current_date(),current_time(), 1,1,1, PNNN, geometry_pk_id, 4, 8.46, 1);    


insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500007000000000', 14, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500028000000000', 5, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500024000000000', 6, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500008000000000', 7, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500019000000000', 8, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500034000000000', 15, 4, 8.46, 1);


insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500014000000000', 13, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500020000000000', 9, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500026000000000', 10, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500022000000000', 11, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '082500027000000000', 12, 4, 8.46, 1);

insert into raw_material
values(0,current_date(),current_time(), 1,1,1, '032500028000000000', 5, 5, 8.43, 1);



select * from raw_material;

select * from geometry;

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (5,'geometry','en','round', null);

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (5,'geometry','en','round', null);

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (5,'geometry','en','round', null);

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (5,'geometry','en','round', null);

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (5,'geometry','en','round', null);

insert into dictionary
values (5,'geometry','it','tonda', null);
insert into dictionary
values (10,'geometry','en','round', null);

insert into dictionary
values (11,'geometry','it','tonda', null);
insert into dictionary
values (11,'geometry','en','round', null);

insert into dictionary
values (12,'geometry','it','tonda', null);
insert into dictionary
values (12,'geometry','en','round', null);

insert into dictionary
values (13,'geometry','it','tonda', null);
insert into dictionary
values (13,'geometry','en','round', null);

insert into dictionary
values (14,'geometry','it','tonda', null);
insert into dictionary
values (14,'geometry','en','round', null);

insert into dictionary
values (15,'geometry','it','tonda', null);
insert into dictionary
values (15,'geometry','en','round', null);