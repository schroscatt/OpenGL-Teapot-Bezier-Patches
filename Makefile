glchair:
	g++ -g src/main.cpp src/glad.c src/ply.c -o render -I include -L /opt/homebrew/Cellar/glfw/3.3.7 -lglfw -framework Cocoa -framework OpenGL -framework IOKit