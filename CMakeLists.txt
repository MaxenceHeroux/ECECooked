cmake_minimum_required(VERSION 3.27)
project(projet_allegro_ing1_2023_2024_s2_ececooked_ing1_2023_2024_9_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_allegro_ing1_2023_2024_s2_ececooked_ing1_2023_2024_9_1
        main.c
        config.h
        menu.c
        ressources.c
        ressources.h
        partie.c
        manette.c
        manette_PS.h
        _fonctionsAllegro.h
        _fonctionsAllegro.c
        commandes.c
        _temps.c
        _temps.h
        gestionObjets.c
        gestionObjets.h
)

target_link_libraries(projet_allegro_ing1_2023_2024_s2_ececooked_ing1_2023_2024_9_1 -lmingw32 -lalleg44)
