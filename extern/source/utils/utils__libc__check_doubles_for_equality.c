


int utils__libc__check_doubles_for_equality (double n1, double n2, double tolerance)
{

	double n1_plus;
	double n1_minus;

	
	/*
	 *
	 *        n1_minus       n1       n1_plus
	 *     -------|-----------|-----------|--------------------------------->
	 *
	 *
	 */
	n1_plus = n1 + tolerance;
	n1_minus = n1 - tolerance;

	if ((n2 >= n1_minus) && (n2 <= n1_plus))
	{
		return 0;
	}

	return -100;


}