main: main.o affichage.o gestion.o libisentlib.a
	gcc -Wall main.o affichage.o gestion.o -o main libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple libisentlib.a -lm -framework OpenGL -framework GLUT

#exempleTortue: exempleTortue.o libisentlib.a
	#gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -framework OpenGL -framework GLUT

main.o: main.c GfxLib.h BmpLib.h ESLib.h
	gcc -Wall -c main.c
	
affichage.o: affichage.c
	gcc -g -Wall -c affichage.c
	
gestion.o: gestion.c
	gcc -g -Wall -c gestion.c

# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

clean:
	rm -f *~ *.o
