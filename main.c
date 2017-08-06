#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
     
#include <poly/assignment.h>
#include <poly/polynomial.h>
#include <poly/variable_order.h>
#include <poly/variable_db.h>
#include <poly/polynomial_context.h>
#include <poly/upolynomial.h>
#include <poly/poly.h>

lp_value_t* dyadic_rational_normalization_error_roots() {
  lp_value_t* roots =
    (lp_value_t*) malloc(sizeof(lp_value_t)*3);

  lp_rational_t five_halves;
  lp_rational_construct_from_int(&five_halves, 5, 2);
  lp_value_construct(&(roots[0]), LP_VALUE_RATIONAL, &five_halves);

  //root[1] = <3*x^2 + (-1*x) + (-1), (-445/1024, -889/2048)>
  //root[2] = <61*x^2 + 8*x + (-8), (-889/2048, -111/256)>

  lp_upolynomial_t* x2 = lp_upolynomial_construct_power(lp_Z, 2, 3);
  lp_upolynomial_t* mx = lp_upolynomial_construct_power(lp_Z, 1, -1);
  lp_upolynomial_t* mone = lp_upolynomial_construct_power(lp_Z, 0, -1);

  lp_upolynomial_t* poly1 = lp_upolynomial_add(x2, mx);
  lp_upolynomial_t* poly = lp_upolynomial_add(poly1, mone);
  size_t deg = lp_upolynomial_degree(poly);

  lp_upolynomial_print(poly, stdout);
  printf("\n");

  lp_dyadic_rational_t num;
  lp_dyadic_rational_construct_from_int(&num, -445, 10);

  lp_dyadic_rational_t denum;
  lp_dyadic_rational_construct_from_int(&denum, -889, 11);

  lp_dyadic_interval_t it;
  lp_dyadic_interval_construct(&it, &num, 1, &denum, 1);

  lp_dyadic_interval_print(&it, stdout);
  printf("\n");

  lp_algebraic_number_t algnum_1;
  lp_algebraic_number_construct(&algnum_1, poly, &it);
  lp_value_construct(&(roots[1]), LP_VALUE_ALGEBRAIC, &algnum_1);


  lp_upolynomial_t* x2_2 = lp_upolynomial_construct_power(lp_Z, 2, 61);
  lp_upolynomial_t* mx_2 = lp_upolynomial_construct_power(lp_Z, 1, 8);
  lp_upolynomial_t* mone_2 = lp_upolynomial_construct_power(lp_Z, 0, -8);

  lp_upolynomial_t* poly1_2 = lp_upolynomial_add(x2_2, mx_2);
  lp_upolynomial_t* poly_2 = lp_upolynomial_add(poly1_2, mone_2);

  lp_upolynomial_print(poly_2, stdout);
  printf("\n");

  lp_dyadic_rational_t num_2;
  lp_dyadic_rational_construct_from_int(&num_2, -889, 11);

  lp_dyadic_rational_t denum_2;
  lp_dyadic_rational_construct_from_int(&denum_2, -111, 8);

  lp_dyadic_interval_t it_2;
  lp_dyadic_interval_construct(&it_2, &num_2, 1, &denum_2, 1);

  lp_dyadic_interval_print(&it, stdout);
  printf("\n");

  lp_algebraic_number_t algnum_2;
  lp_algebraic_number_construct(&algnum_2, poly_2, &it_2);
  lp_value_construct(&(roots[2]), LP_VALUE_ALGEBRAIC, &algnum_2);

  lp_algebraic_number_print(&algnum_2, stdout);
  printf("\n");
  
  /* lp_algebraic_number_t algnum_2; */
  /* lp_algebraic_number_construct(&algnum_2, poly, &it); */

  
  return roots;
}

void test_constant_conic_sections_unlifted() {

  size_t num_roots = 3;
  lp_value_t* all_roots = dyadic_rational_normalization_error_roots();

  printf("# of roots = %zu\n", num_roots);

  printf("root[0] with type %u = ", all_roots[0].type);
  lp_value_print(&(all_roots[0]), stdout);
  printf("\n");

  printf("root[1] with type %u = ", all_roots[1].type);
  lp_value_print(&(all_roots[1]), stdout);
  printf("\n");

  printf("root[2] with type %u = ", all_roots[2].type);
  lp_value_print(&(all_roots[2]), stdout);
  printf("\n");
  
  assert(num_roots > 0);

  size_t num_test_points = 0;
  size_t* num_test_points_ptr = &num_test_points;

  *num_test_points_ptr = 2*num_roots + 1;

  // First iteration

  // Construct midpoint
  lp_value_t current = all_roots[0];
  lp_value_t next = all_roots[0 + 1];

  printf("next value = ");
  lp_value_print(&next, stdout);
  printf("\n");

  printf("checking root normalization of\n");
  printf("current = ");
  lp_value_print(&current, stdout);
  printf("\n");
  printf("next = ");
  lp_value_print(&current, stdout);
  printf("\n");

  /* printf("checking root %d for normalization before between value call\n", 0); */
  /* if (is_algebraic(all_roots[0])) { */
  /*   check_normalized(&(all_roots[0].value.a)); */
  /* } */

  lp_value_t btwn;
  lp_value_construct_none(&btwn);
  lp_value_get_value_between(&current, 1, &next, 1, &btwn);

  /* printf("checking root %d for normalization after between value\n", 0); */
  /* if (is_algebraic(all_roots[0])) { */
  /*   check_normalized(&(all_roots[0].value.a)); */
  /* } */

  // Second iteration

  // Construct midpoint
  current = all_roots[1];
  next = all_roots[1 + 1];

  printf("next value = ");
  lp_value_print(&next, stdout);
  printf("\n");

  printf("checking root normalization of\n");
  printf("current = ");
  lp_value_print(&current, stdout);
  printf("\n");
  printf("next = ");
  lp_value_print(&current, stdout);
  printf("\n");

  /* printf("checking root %d for normalization before between value call\n", 1); */
  /* if (is_algebraic(all_roots[1])) { */
  /*   check_normalized(&(all_roots[1].value.a)); */
  /* } */

  lp_value_t btwn1;
  lp_value_construct_none(&btwn1);
  lp_value_get_value_between(&current, 1, &next, 1, &btwn1);

  /* printf("checking root %d for normalization after between value\n", 1); */
  /* if (is_algebraic(all_roots[1])) { */
  /*   check_normalized(&(all_roots[1].value.a)); */
  /* } */

  // end second iteration

  for (size_t i = 0; i < num_roots; i++) {
    lp_value_t dummy;
    lp_value_construct_copy(&dummy, &(all_roots[i]));
  }

  printf("DONE\n");

}

void test_algebraic_number_refinement() {
  // Constructing first value
  lp_upolynomial_t* x2 = lp_upolynomial_construct_power(lp_Z, 2, 3);
  lp_upolynomial_t* mx = lp_upolynomial_construct_power(lp_Z, 1, -1);
  lp_upolynomial_t* mone = lp_upolynomial_construct_power(lp_Z, 0, -1);

  lp_upolynomial_t* poly1 = lp_upolynomial_add(x2, mx);
  lp_upolynomial_t* poly = lp_upolynomial_add(poly1, mone);
  size_t deg = lp_upolynomial_degree(poly);

  lp_upolynomial_print(poly, stdout);
  printf("\n");

  lp_dyadic_rational_t num;
  lp_dyadic_rational_construct_from_int(&num, -445, 10);

  lp_dyadic_rational_t denum;
  lp_dyadic_rational_construct_from_int(&denum, -889, 11);

  lp_dyadic_interval_t it;
  lp_dyadic_interval_construct(&it, &num, 1, &denum, 1);

  lp_dyadic_interval_print(&it, stdout);
  printf("\n");

  lp_algebraic_number_t algnum;
  lp_algebraic_number_construct(&algnum, poly, &it);

  lp_algebraic_number_print(&algnum, stdout);
  printf("\n");

  // Constructing next value
  // Next value = <61*x^2 + 8*x + (-8), (-889/2048, -111/256)>
  lp_upolynomial_t* x2_2 = lp_upolynomial_construct_power(lp_Z, 2, 61);
  lp_upolynomial_t* mx_2 = lp_upolynomial_construct_power(lp_Z, 1, 8);
  lp_upolynomial_t* mone_2 = lp_upolynomial_construct_power(lp_Z, 0, -8);

  lp_upolynomial_t* poly1_2 = lp_upolynomial_add(x2_2, mx_2);
  lp_upolynomial_t* poly_2 = lp_upolynomial_add(poly1_2, mone_2);

  lp_upolynomial_print(poly_2, stdout);
  printf("\n");

  lp_dyadic_rational_t num_2;
  lp_dyadic_rational_construct_from_int(&num_2, -889, 11);

  lp_dyadic_rational_t denum_2;
  lp_dyadic_rational_construct_from_int(&denum_2, -111, 8);

  lp_dyadic_interval_t it_2;
  lp_dyadic_interval_construct(&it_2, &num_2, 1, &denum_2, 1);

  lp_dyadic_interval_print(&it, stdout);
  printf("\n");

  lp_algebraic_number_t algnum_2;
  lp_algebraic_number_construct(&algnum_2, poly_2, &it_2);

  lp_algebraic_number_print(&algnum_2, stdout);
  printf("\n");


  lp_value_t val_1;
  lp_value_construct(&val_1, LP_VALUE_ALGEBRAIC, &algnum);

  lp_value_t val_2;
  lp_value_construct(&val_2, LP_VALUE_ALGEBRAIC, &algnum_2);

  printf("Constructing fresh value");

  lp_value_t val;
  lp_value_construct_none(&val);
  lp_value_get_value_between(&val_1, 1, &val_2, 1, &val);

  printf("val_1 after call\n");
  lp_value_print(&val_1, stdout);
  printf("\n");
  
  /* for (size_t i = 0; i < 20; i++) { */
  /*   lp_algebraic_number_refine(&algnum); */

  /*   lp_algebraic_number_print(&algnum, stdout); */
  /*   printf("\n"); */
  /* } */
  
  /* printf("Degree of poly = %zu\n", deg); */

  /* lp_upolynomial_print(poly, stdout); */
  /* printf("\n"); */

  /* lp_algebraic_number_t* roots = */
  /*   (lp_algebraic_number_t*)(malloc(sizeof(lp_algebraic_number_t)*deg)); */

  
}

int main() {
  //test_algebraic_number_refinement();
  /* test_algebraic_number_copy(); */
  /* test_mccallum_projection_only_resultants(); */
  /* isolate_multivariate_roots(); */
  /* test_all_coefficients(); */
  /* test_all_discriminants(); */
  /* test_conic_sections(); */
  //test_constant_conic_sections();
  test_constant_conic_sections_unlifted();

}
