/**
 * @file unit-test.h
 * @brief  Provides helpers to unit test some functionalities.
 * @author Thomas Joly
 * @version 0.1
 *
 * PROTOTYPE_FOR_UNIT_TEST: declare a prototype of function will be used in unit-test.
 * PRIVATE_EXCEPT_UNIT_TEST: function can be used in unit-test but not in other modules.
 */

#ifndef __UNIT_TEST__
#define __UNIT_TEST__

#ifdef UNIT_TEST_TARGET

#define PROTOTYPE_FOR_UNIT_TEST(prototype) prototype
#define PRIVATE_EXCEPT_UNIT_TEST

#else

#define PROTOTYPE_FOR_UNIT_TEST(prototype)
#define PRIVATE_EXCEPT_UNIT_TEST static

#endif

#endif /* !__UNIT_TEST__ */
