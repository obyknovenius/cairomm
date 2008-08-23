#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
using namespace boost::unit_test;
#include <cairomm/surface.h>
using namespace Cairo;

static unsigned int test_slot_called = 0;
ErrorStatus test_slot(const unsigned char* /*data*/, unsigned int /*len*/)
{
  test_slot_called++;
  return CAIRO_STATUS_SUCCESS;
}

void test_write_to_png_stream()
{
  RefPtr<ImageSurface> surface = ImageSurface::create(FORMAT_ARGB32, 1, 1);
  surface->write_to_png_stream(sigc::ptr_fun(test_slot));
  BOOST_CHECK(test_slot_called > 0);
}

void test_pdf_constructor_slot()
{
  test_slot_called = 0;
  RefPtr<PdfSurface> pdf = PdfSurface::create(sigc::ptr_fun(&test_slot), 1, 1);
  pdf->show_page();
  pdf->finish();
  BOOST_CHECK(test_slot_called > 0);
}

void test_ps_constructor_slot()
{
  test_slot_called = 0;
  RefPtr<PsSurface> ps = PsSurface::create(sigc::ptr_fun(&test_slot), 1, 1);
  ps->show_page();
  ps->finish();
  BOOST_CHECK(test_slot_called > 0);
}

void test_svg_constructor_slot()
{
  test_slot_called = 0;
  RefPtr<SvgSurface> svg = SvgSurface::create(sigc::ptr_fun(&test_slot), 1, 1);
  svg->show_page();
  svg->finish();
  BOOST_CHECK(test_slot_called > 0);
}

static std::ifstream png_file;
unsigned int test_read_func_called = 0;
static ErrorStatus test_read_func(unsigned char* data, unsigned int len)
{
  ++test_read_func_called;
  if (png_file.read(reinterpret_cast<char*>(data), len))
    return CAIRO_STATUS_SUCCESS;
  return CAIRO_STATUS_READ_ERROR;
}

unsigned int c_test_read_func_called = 0;
static cairo_status_t c_test_read_func(void* /*closure*/, unsigned char* data, unsigned int len)
{
  ++c_test_read_func_called;
  if (png_file.read(reinterpret_cast<char*>(data), len))
    return CAIRO_STATUS_SUCCESS;
  return CAIRO_STATUS_READ_ERROR;
}

void test_create_from_png()
{
  RefPtr<ImageSurface> surface;
  // try the sigc::slot version
  png_file.open("png-stream-test.png");
  surface = ImageSurface::create_from_png_stream(sigc::ptr_fun(&test_read_func));
  png_file.close();
  BOOST_CHECK(test_read_func_called > 0);

  // now try the raw C function (deprecated) version
  png_file.open("png-stream-test.png");
  surface = ImageSurface::create_from_png(&c_test_read_func, NULL);
  png_file.close();
  BOOST_CHECK(c_test_read_func_called > 0);
}


test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  // compile even with -Werror
  if (argc && argv) {}

  test_suite* test= BOOST_TEST_SUITE( "Cairo::Surface Tests" );

  test->add (BOOST_TEST_CASE (&test_write_to_png_stream));
  test->add (BOOST_TEST_CASE (&test_pdf_constructor_slot));
  test->add (BOOST_TEST_CASE (&test_ps_constructor_slot));
  test->add (BOOST_TEST_CASE (&test_svg_constructor_slot));
  test->add (BOOST_TEST_CASE (&test_create_from_png));

  return test;
}