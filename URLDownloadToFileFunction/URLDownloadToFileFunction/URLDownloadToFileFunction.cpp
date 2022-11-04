#include <iostream>
#include <Windows.h>
#include <urlmon.h>

auto main() -> int
{
    //Vá nas configurações do projeto -> Vinculador -> Entrada -> Dependências adicioanis -> Editar -> coloque Urlmon.lib

    /*
        Baixa bits da Internet e os salva em um arquivo.
    */

    HRESULT hRes = URLDownloadToFile(
        _In_opt_ NULL, //[in, optional]
        _In_ L"https://avatars.githubusercontent.com/u/99103680?v=4", //[in]
        _In_ L"C:\\MyDir\\file.png", //[in]
        _In_opt_ NULL, //[in, optional]
        _In_opt_ NULL //[in, optional]
    );

    if (hRes != S_OK)
        std::operator<<(std::cout, "Erro ao tentar fazer download do arquivo !\n");

    std::operator<<(std::cout, "Sucesso ao baixar o arquivo brother, vá lá na pasta conferir !\n");


    return 0;
}