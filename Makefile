GLUT = #  -lglut 
LIB = -lm -framework OpenGL -framework glut # -lopengl -lGLU
SDLF = `sdl-config --cflags`
SDLL = `sdl-config --libs`
PARSER = -lfl
XML = -lxmlio
OPTS = -Wno-deprecated -O3 
CC = g++
OBJS = Algebra.o FuenteLuminosa.o Camara.o Escena.o RGB.o Render.o Primitiva.o Material.o
OBJS_PARSER =  lexico.o gramatica.o

SOURCE_EXT = cpp
HEADER_EXT = h

SOURCE_PARSER = c
HEADER_PARSER = h

RESULTS = raytracer

all: $(RESULTS)

# %.o : %.cpp
# 	$(CC) $(OPTS) -c $<

$(RESULTS): $(OBJS) $(OBJS_PARSER) $(RESULTS).$(SOURCE_EXT)
	$(CC) -o $@ $+ $(LIB) $(GLUT) $(OPTS) $(PARSER) 

$(OBJS):%.o:%.$(SOURCE_EXT) %.$(HEADER_EXT)
	$(CC) -c $< $(OPTS)
	
#
# $(OBJS_PARSER):%.o:%.$(SOURCE_PARSER) %.$(HEADER_PARSER)
# 	$(CC) -c $< $(OPTS)
# 
	
# pars: $(OBJS) pars.cpp
# 	$(CC) -o $@ $? $(LIB) $(OPTS) 

clean:
	rm -f $(OBJS) $(RESULTS) 
	make clean_parser


# # # # # # # PARSER
# 
# parser:    lexico.o gramatica.o
# 	g++ -o parser lexico.o gramatica.o -lfl
	
gramatica.o: gramatica.c 
	g++ -c gramatica.c

gramatica.c: gramatica.y
	bison -ogramatica.c -t -d -v gramatica.y

gramatica.h: gramatica.c

lexico.o: lexico.c gramatica.h
	g++ -c lexico.c

lexico.c: lexico.l  
	flex -olexico.c lexico.l

clean_parser:
	rm -f gramatica.o gramatica.c lexico.o lexico.c gramatica.output gramatica.h
	
