#make file - compiling on MacOS
all:    #target name
	g++ -Wall -o portal temp.cpp imageloader.cpp -framework OpenGL -framework GLUT

#make file - compiling on Kali
#all:		#target name
#	g++ -Wall -o portal temp.cpp imageloader.cpp -lGL -lGLU -lglut
