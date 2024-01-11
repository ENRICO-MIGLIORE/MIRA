#include "utils__sdb.h"


/*
 *
 *   sdb_FILE_1              sdb_JS_2               rc       match_index      match_index                      match_index_len
 *
 *   "N1","N2","N3"         "N2","N3,"N1"           0        {1,2,0}          {2,0,1}                          3
 *          	     				    												                 
 *   "N1","N2"              "N1","N2"               0        {0,1}            {0,1}                            2
 *				     				             										                 
 *   "N1","N2"              "N1"                    0        {0}              {0}                              1
 *                     				             										                 
 *   "N1","N2"              "N1","N3","N2"          0        {0,-1, 1}        {0, 2}                           2

 *   "N4","N2","N3","N1"    "N2","N3,"N1"           0        {1,2,0}          {-1, 0, 1, 2}                    4
 *
 *   "N2","N5","N3","N1"    "N2","N3,"N1"           0        {1,2,0}          {0, -5, 1, 2}                    4

 *   "N1", "N1"             "N2","N3,"N1"         -10        {1,2,0}          {-1,2,0,1,343,12}                3
 */



int utils__sdb__match_sdb_names_enrico (const utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2, int* match_vector_index, size_t match_vector_size)
{
	int rc;
	int flag;
	size_t i;
	size_t j;
	size_t start_j;
	size_t match_count;


	if (sdb_1 == NULL)
	{
		return -10;
	}

	if (sdb_1->configured != 1)
	{
		return -20;
	}

	if (sdb_1->num_fields == 0)
	{
		return -30;
	}

	if (sdb_2 == NULL)
	{
		return -40;
	}

	if (sdb_2->configured != 1)
	{
		return -50;
	}

	if (sdb_2->num_fields == 0)
	{
		return -60;
	}

	if (sdb_2 == NULL)
	{
		return -70;
	}

	if (sdb_2->configured != 1)
	{
		return -80;
	}

	if (sdb_2->num_fields == 0)
	{
		return -90;
	}

	if (match_vector_size < sdb_1->num_fields)
	{
		return -100;
	}

	
	if (sdb_1->num_fields > 1)
	{		
		/*
		 * All names must appear just once
		 */

		start_j = 1;

		for (i = 0; i < sdb_1->num_fields; i++)
		{
			for (j = start_j; j < sdb_1->num_fields; j++)
			{			
				if (sdb_1->name_len[i] ==  sdb_1->name_len[j])
				{
					if (sdb_1->name[i] == NULL)
					{
						return -200;
					}

					if (sdb_1->name[j] == NULL)
					{
						return -210;
					}

					rc = memcmp(sdb_1->name[i], sdb_1->name[j], sdb_1->name_len[i]);
					if (rc == 0)
					{
						return -220;
					}
				}
			}
			start_j++;
		}
	}


	if (sdb_2->num_fields > 1)
	{		
		/*
		 * All names must appear just once
		 */

		start_j = 1;

		for (i = 0; i < sdb_2->num_fields; i++)
		{
			for (j = start_j; j < sdb_2->num_fields; j++)
			{			
				if (sdb_2->name_len[i] ==  sdb_2->name_len[j])
				{
					if (sdb_2->name[i] == NULL)
					{
						return -220;
					}

					if (sdb_2->name[j] == NULL)
					{
						return -230;
					}

					rc = memcmp(sdb_2->name[i], sdb_2->name[j], sdb_2->name_len[i]);
					if (rc == 0)
					{
						return -240;
					}
				}
			}
			start_j++;
		}
	}


	match_count = 0;
	for (i = 0; i < sdb_1->num_fields; i++)
	{
		flag = 0;

		for (j = 0; (j < sdb_2->num_fields) && (flag == 0); j++)
		{
			if (sdb_1->name_len[i] == sdb_2->name_len[j])
			{
				rc = memcmp(sdb_1->name[i], sdb_2->name[j], sdb_2->name_len[j]);
				if (rc == 0)
				{
					match_vector_index[i] = (int) j;
					flag = 1;
					match_count++;
				}		
			}
		}

		if (flag == 0)
		{
			match_vector_index[i] = -1;
		}
	}

	if (match_count == 0)
	{
		return -300;
	}

	return 0;

}


////////////////////////carmelo /////////////////////////////////

int utils__sdb__match_sdb_names(const utils__sdb_t* sdb_1, const utils__sdb_t* sdb_2, int* match_vector_index, size_t match_vector_size)
{
	int rc;
	int flag;

	size_t i;
	size_t j;
	size_t start_j;
	size_t match_count;


	if (sdb_1 == NULL)
	{
		return -10;
	}

	if (sdb_1->configured != 1)
	{
		return -20;
	}

	if (sdb_1->num_fields == 0)
	{
		return -30;
	}

	if (sdb_2 == NULL)
	{
		return -40;
	}

	if (sdb_2->configured != 1)
	{
		return -50;
	}

	if (sdb_2->num_fields == 0)
	{
		return -60;
	}

	if (sdb_2 == NULL)
	{
		return -70;
	}

	if (sdb_2->configured != 1)
	{
		return -80;
	}

	if (sdb_2->num_fields == 0)
	{
		return -90;
	}

	if (match_vector_size < sdb_1->num_fields)
	{
		return -100;
	}


	if (sdb_1->num_fields > 1)
	{
		/*
		 * All names must appear just once
		 */

		start_j = 1;

		for (i = 0; i < sdb_1->num_fields; i++)
		{
			for (j = start_j; j < sdb_1->num_fields; j++)
			{
				if (sdb_1->name_len[i] == sdb_1->name_len[j])
				{
					if (sdb_1->name[i] == NULL)
					{
						return -200;
					}

					if (sdb_1->name[j] == NULL)
					{
						return -210;
					}

					rc = memcmp(sdb_1->name[i], sdb_1->name[j], sdb_1->name_len[i]);
					if (rc == 0)
					{
						return -220;
					}
				}
			}
			start_j++;
		}
	}


	//if (sdb_2->num_fields > 1)
	//{		
	//	/*
	//	 * All names must appear just once
	//	 */

	//	start_j = 1;

	//	for (i = 0; i < sdb_2->num_fields; i++)
	//	{
	//		for (j = start_j; j < sdb_2->num_fields; j++)
	//		{			
	//			if (sdb_2->name_len[i] ==  sdb_2->name_len[j])
	//			{
	//				if (sdb_2->name[i] == NULL)
	//				{
	//					return -220;
	//				}

	//				if (sdb_2->name[j] == NULL)
	//				{
	//					return -230;
	//				}

	//				rc = memcmp(sdb_2->name[i], sdb_2->name[j], sdb_2->name_len[i]);
	//				if (rc == 0)
	//				{
	//					return -240;
	//				}
	//			}
	//		}
	//		start_j++;
	//	}
	//}


	match_count = 0;
	for (i = 0; i < sdb_1->num_fields; i++)
	{
		flag = 0;

		for (j = 0; (j < sdb_2->num_fields) && (flag == 0); j++)
		{
			if (sdb_1->name_len[i] == sdb_2->name_len[j])
			{
				rc = memcmp(sdb_1->name[i], sdb_2->name[j], sdb_2->name_len[j]);
				if (rc == 0)
				{
					match_vector_index[i] = j;
					flag = 1;
					match_count++;
				}
			}
		}

		if (flag == 0)
		{
			match_vector_index[i] = -1;
		}
	}

	if (match_count == 0)
	{
		return -300;
	}

	return 0;

}





