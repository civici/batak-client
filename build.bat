set vcpkg=C:\vcpkg\installed\x64-windows
set files=main.c network.c payload.c gui.c game/Card.c game/Deck.c
set libs=pdcurses.lib ws2_32.lib

cl /I%vcpkg%\include %files% %libs% /link /LIBPATH:%vcpkg%\lib /out:a.exe