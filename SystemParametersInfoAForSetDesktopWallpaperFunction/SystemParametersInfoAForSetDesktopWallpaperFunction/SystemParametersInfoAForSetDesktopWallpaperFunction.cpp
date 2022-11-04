#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	std::basic_string< char, std::char_traits< char >, std::allocator< char > > path("C:\\MyDir\\ixi.jpg");

    if (!SystemParametersInfoW(
        _In_ SPI_SETDESKWALLPAPER, 
        _In_ 0, 
        _Inout_ _Pre_maybenull_ _Post_valid_(void*)path.c_str(), 
        _In_ SPIF_SENDCHANGE 
    ))
        std::operator<<(std::cout, "Erro ao definir wallpaper !\n");

    std::operator<<(std::cout, "Sucesso ao definir wallpaper !");

	return 0;
}