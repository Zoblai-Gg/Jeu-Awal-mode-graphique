# Compilateur
CC = gcc
# Options de compilation
CFLAGS = -Wall $(shell sdl2-config --cflags)

# Options de liaison
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
#Fichiers sources
SRCS = main.c awele.c logo.c welcome.c gameOver.c init_awele.c jouer_update.c affiche_awele.c menu.c saisi_pseudo0.c save.c affiche_scoreUI.c a_propos.c contre_pc.c 

#Fichiers objets
OBJS = $(SRCS:.c=.o)

# Exécutable  
EXEC = main

#génération de l'éxecutable l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)
#génération des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Nettoyage des fichiers
clean:
	rm -f $(EXEC) $(OBJS)





