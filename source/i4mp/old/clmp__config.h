#ifndef CLMP__CONFIG_H
#define CLMP__CONFIG_H


#define CLMP__CONFIG__MAX_PATH_SIZE                                    1024
#define CLMP__CONFIG__SDB_FIELDS_MAX                                   128
#define CLMP__CONFIG__SDB_RECORDS_MAX                                  (1024 * 16)
#define CLMP__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define CLMP__CONFIG__STACK_BUFFER_SIZE                                1024 * 2


#define CLMP__CONFIG__FIRST_PK_ID                                1

/*
 * Module: DEFAULT
 */
#define CLMP__CONFIG__DEFAULT__DUMMY                       "DUMMY"



/*
 * Module: SYSTEM
 */
#define CLMP__CONFIG__SYSTEM__FIRST_FISCAL_YEAR                        "2016"

#define CLMP__CONFIG__SYSTEM__YEARS_BACK_MAX                              10



/*
 * Module: USERS
 */
#define CLMP__CONFIG__SYSTEM__USERS_MAX                                256




/*
 *  Module: FPW-IET
 */
#define CLMP__CONFIG__FPW_IET__POS_ADJ__PROD                           "POSITIVE ADJUSTMENT - PRODUCTION"
#define CLMP__CONFIG__FPW_IET__POS_ADJ__MAN__INV_ADJ                   "POSITIVE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"
#define CLMP__CONFIG__FPW_IET__NEG_ADJ__MAN__INV_ADJ                   "NEGATIVE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"
#define CLMP__CONFIG__FPW_IET__ABS_ADJ__MAN__INV_ADJ                   "ABSOLUTE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"
#define CLMP__CONFIG__FPW_IET__NEG_ADJ__SHIP                           "NEGATIVE ADJUSTMENT - SHIPPING"


/*
 *  Module: RMW-IET
 */
#define CLMP__CONFIG__RMW_IET__POS_ADJ__PUR                            "POSITIVE ADJUSTMENT - PURCHASE"
#define CLMP__CONFIG__RMW_IET__POS_ADJ__MAN__INV_ADJ                   "POSITIVE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"
#define CLMP__CONFIG__RMW_IET__NEG_ADJ__PROD                           "NEGATIVE ADJUSTMENT - PRODUCTION"
#define CLMP__CONFIG__RMW_IET__NEG_ADJ__MAN__INV_ADJ                   "NEGATIVE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"
#define CLMP__CONFIG__RMW_IET__ABS_ADJ__MAN__INV_ADJ                   "ABSOLUTE ADJUSTMENT - MANUAL INVENTORY ADJUSTMENT"

              
#endif