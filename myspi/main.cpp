#include "hwlib.hpp"
#include "myspi.hpp"

namespace target = hwlib::target;

int main( void ){

   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;

   auto _sclk = hwlib::target::pin_out{ hwlib::target::pins::d3 };
   auto sclk = hwlib::invert( _sclk );
   auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d4 };

   auto spi  = my_spi_bus_bit_banged_sclk_mosi_miso{
      sclk, mosi, hwlib::pin_in_dummy };

   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d5 };

   blk.write( 1 );blk.flush();

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );

   int times;

   for(;;){


       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.clear( hwlib::red );

       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.flush();

       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.clear( hwlib::green );

       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.flush();

       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.clear( hwlib::blue );

       times = hwlib::now_us();
       hwlib::cout << times << '\n';

       display.flush();

   }

}
