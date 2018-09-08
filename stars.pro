TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    blast.c \
    asteroid.c \
    spaceship.c \
    blasterioids.c

HEADERS += \
    asteroid.h \
    blast.h \
    blasterioids.h \
    spaceship.h

LIBS += -L/usr/lib -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image -lallegro_color -lallegro_acodec -lallegro_audio
INCLUDEPATH += -I/usr/include/allegro5

