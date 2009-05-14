#include <seed.h>
#include <cairo/cairo.h>

#include "seed-cairo.h"
SeedClass seed_matrix_class;

SeedValue
seed_value_from_cairo_matrix (SeedContext ctx,
			      const cairo_matrix_t *matrix,
			      SeedException *exception)
{
  SeedValue elems[6];
  
  elems[0] = seed_value_from_double(ctx, matrix->xx, exception);
  elems[1] = seed_value_from_double(ctx, matrix->yx, exception);
  elems[2] = seed_value_from_double(ctx, matrix->xy, exception);
  elems[3] = seed_value_from_double(ctx, matrix->yy, exception);
  elems[4] = seed_value_from_double(ctx, matrix->x0, exception);
  elems[5] = seed_value_from_double(ctx, matrix->y0, exception);
  
  return seed_make_array (ctx, elems, 6, exception);
}

gboolean
seed_value_to_cairo_matrix (SeedContext ctx,
			    SeedValue value,
			    cairo_matrix_t *matrix,
			    SeedException *exception)
{
  if (!seed_value_is_object (ctx, value))
    return FALSE;
  
  matrix->xx = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 0, exception), exception);
  matrix->yx = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 1, exception), exception);
  matrix->xy = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 2, exception), exception);
  matrix->yy = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 3, exception), exception);
  matrix->x0 = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 4, exception), exception);
  matrix->y0 = seed_value_to_double (ctx, seed_object_get_property_at_index (ctx, (SeedObject) value, 5, exception), exception);
  
  return TRUE;
}

// Should probably be a property?
static SeedValue
seed_cairo_matrix_init_identity (SeedContext ctx,
				 SeedObject function,
				 SeedObject this_object,
				 gsize argument_count,
				 const SeedValue arguments[],
				 SeedException *exception)
{
  cairo_matrix_t m;
  
  cairo_matrix_init_identity (&m);
  return seed_value_from_cairo_matrix (ctx, &m, exception);
}

static SeedValue
seed_cairo_matrix_init_translate (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble x, y;
  cairo_matrix_t m;
  
  if (argument_count != 2)
    {
      EXPECTED_EXCEPTION("init_translate", "2 arguments");
    }
  
  x = seed_value_to_double (ctx, arguments[0], exception);
  y = seed_value_to_double (ctx, arguments[1], exception);
  
  cairo_matrix_init_translate (&m, x, y);
  
  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

static SeedValue
seed_cairo_matrix_translate (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble x, y;
  cairo_matrix_t m;
  
  if (argument_count != 3)
    {
      EXPECTED_EXCEPTION("translate", "3 arguments");
    }
  
  if (!seed_value_to_cairo_matrix (ctx, arguments[0], &m, exception))
    {
      seed_make_exception (ctx, exception, "ArgumentError", "translate needs an array [xx, yx, xy, yy, x0, y0]");
    }
  x = seed_value_to_double (ctx, arguments[1], exception);
  y = seed_value_to_double (ctx, arguments[2], exception);
  
  cairo_matrix_translate (&m, x, y);
  
  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

static SeedValue
seed_cairo_matrix_init_scale (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble x, y;
  cairo_matrix_t m;
  
  if (argument_count != 2)
    {
      EXPECTED_EXCEPTION("init_scale", "2 arguments");
    }
  
  x = seed_value_to_double (ctx, arguments[0], exception);
  y = seed_value_to_double (ctx, arguments[1], exception);
  
  cairo_matrix_init_scale (&m, x, y);
  
  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

static SeedValue
seed_cairo_matrix_scale (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble x, y;
  cairo_matrix_t m;
  
  if (argument_count != 3)
    {
      EXPECTED_EXCEPTION("scale", "3 arguments");
    }
  
  if (!seed_value_to_cairo_matrix (ctx, arguments[0], &m, exception))
    {
      seed_make_exception (ctx, exception, "ArgumentError", "scale needs an array [xx, yx, xy, yy, x0, y0]");
    }
  x = seed_value_to_double (ctx, arguments[1], exception);
  y = seed_value_to_double (ctx, arguments[2], exception);
  
  cairo_matrix_scale (&m, x, y);
  
  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

static SeedValue
seed_cairo_matrix_init_rotate (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble angle;
  cairo_matrix_t m;
  
  if (argument_count != 1)
    {
      EXPECTED_EXCEPTION("init_rotate", "1 arguments");
    }
  
  angle = seed_value_to_double (ctx, arguments[0], exception);
  cairo_matrix_init_rotate (&m, angle);
  
  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

static SeedValue
seed_cairo_matrix_rotate (SeedContext ctx,
				  SeedObject function,
				  SeedObject this_object,
				  gsize argument_count,
				  const SeedValue arguments[],
				  SeedException *exception)
{
  gdouble angle;
  cairo_matrix_t m;
  
  if (argument_count != 2)
    {
      EXPECTED_EXCEPTION("rotate", "2 arguments");
    }
  
  if (!seed_value_to_cairo_matrix (ctx, arguments[0], &m, exception))
    {
      seed_make_exception (ctx, exception, "ArgumentError", "rotate needs an array [xx, yx, xy, yy, x0, y0]");
    }
  angle = seed_value_to_double (ctx, arguments[1], exception);

  cairo_matrix_rotate (&m, angle);

  return seed_value_from_cairo_matrix (ctx, &m, exception);  
}

seed_static_function matrix_funcs[] = {
  {"init_identity", seed_cairo_matrix_init_identity, 0},
  {"init_translate", seed_cairo_matrix_init_translate, 0},
  {"init_scale", seed_cairo_matrix_init_scale, 0},
  {"init_rotate", seed_cairo_matrix_init_rotate, 0},
  {"translate", seed_cairo_matrix_translate, 0},
  {"scale", seed_cairo_matrix_scale, 0},
  {"rotate", seed_cairo_matrix_rotate, 0},
  {0, 0, 0}
};

void
seed_define_cairo_matrix (SeedContext ctx,
			  SeedObject namespace_ref)
{
  seed_class_definition matrix_def = seed_empty_class;
  
  matrix_def.class_name = "Matrix";
  matrix_def.static_functions = matrix_funcs;
  seed_matrix_class = seed_create_class (&matrix_def);
  
  seed_object_set_property (ctx, namespace_ref, "Matrix", seed_make_object (ctx, seed_matrix_class, NULL));
}