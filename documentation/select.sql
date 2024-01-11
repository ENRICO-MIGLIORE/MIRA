use db_87__fggr_a22;

select * from raw_material;


set @geometry_desc  = (select dictionary.description
from raw_material, geometry, dictionary
where 
raw_material.pk_id = 2 and
raw_material.fk_geometry_pk_id = geometry.pk_id and
dictionary.pk_table_name = 'geometry' and
geometry.pk_id = dictionary.pk_id and
dictionary.pk_language_pk_id = 'it');


select raw_material.pk_id, suppliers.name, raw_material.supplier_part_number, @geometry_desc, materials_category.name, dictionary.description, raw_material.specific_weight, bars_length.length
from raw_material, suppliers, materials_category, geometry, dictionary, bars_length
where 
raw_material.pk_id = 2 and
raw_material.fk_supplier_pk_id = suppliers.pk_id and
raw_material.fk_geometry_pk_id = geometry.pk_id and
raw_material.fk_material_category_pk_id = materials_category.pk_id and
raw_material.fk_bar_length_pk_id = bars_length.pk_id and
materials_category.pk_id = dictionary.pk_id and
dictionary.pk_table_name = 'materials_category' and
dictionary.pk_language_pk_id = 'en';




select raw_material.active, raw_material.pk_id, raw_material.fk_supplier_pk_id, raw_material.supplier_part_number, geometry.dimension_1,geometry.dimension_2,geometry.dimension_3,geometry.dimension_4, dictionary.description,  materials_category.name, raw_material.specific_weight, geometry.cross_section,bars_length.length from raw_material, dictionary, geometry, materials_category,bars_length where 
-- raw_material.pk_id = 6 and
geometry.pk_id = raw_material.fk_geometry_pk_id and
materials_category.pk_id = raw_material.fk_material_category_pk_id and
bars_length.pk_id = raw_material.fk_bar_length_pk_id and
geometry.pk_id = dictionary.pk_id and dictionary.pk_table_name = 'geometry' and dictionary.pk_language_pk_id = 'it';

select * from geometry;

select * from dictionary where dictionary.pk_table_name = 'geometry' and dictionary.pk_language_pk_id = 'it';

select distinct geometry.dimension_1 from raw_material, geometry, dictionary where 
raw_material.fk_supplier_pk_id = 1 and 
raw_material.fk_geometry_pk_id = geometry.pk_id and 
raw_material.active = 1 and 
dictionary.pk_id = geometry.pk_id and 
dictionary.pk_language_pk_id = 'it' and 
dictionary.pk_table_name = 'geometry' and 
dictionary.description = 'tonda' order by geometry.dimension_1 ASC;