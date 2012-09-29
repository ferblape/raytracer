%{

#include <stdio.h>
#include "def.h"
#include "gramatica.h"

#define  Devolver(x) {return(x);}
// extern "C" YYSTYPE yylval; 
extern "C" {
	int yyerror( const char * );
	int yylex( void );
}

%}

%option yylineno
%option caseless

delimitador		[ \t\n]+
comentario		\"[^\"]*\"
digito          [0-9]
letra           [a-zA-Z]
signo 			(\+)?|(\-)?
identificador   {letra}({letra}|{digito})*
nentero         {signo}{digito}({digito})*
nreal           ({nentero}"."({digito})+|{nentero})
cadena			{letra}*

%%

{comentario}	{printf("");}
{delimitador}	{printf("");}
">"             {Devolver(MAYOR_);}
"<"             {Devolver(MENOR_);}
","             {Devolver(COMA_);}
"{"				{Devolver(ABRELLAVE_);}
"}"				{Devolver(CIERRALLAVE_);}
";"				{Devolver(PUNTOCOMA_);}
"\""			{Devolver(COMILLAS_);}
"camera" 		{Devolver(CAMERA_);}
"location"  	{Devolver(LOCATION_);}
"look_at"   	{Devolver(LOOKAT_);}
"ambiental" 	{Devolver(AMBIENTAL_);}
"color"     	{Devolver(COLOR_);}
"puntual"   	{Devolver(PUNTUAL_);}
"direccional"   {Devolver(DIRECCIONAL_);}
"focal" 		{Devolver(FOCAL_);}
"fov" 			{Devolver(FOV_);}
"sphere" 		{Devolver(SPHERE_);}
"plane" 		{Devolver(PLANE_);}
"checker"   	{Devolver(CHECKER_);}
"size" 			{Devolver(SIZE_);}
"cube" 			{Devolver(CUBE_);}
"quadrilateral" {Devolver(QUADRILATERAL_);}
"triangle" 		{Devolver(TRIANGLE_);}
"especular" 	{Devolver(ESPECULAR_);}
"factor" 		{Devolver(FACTOR_);}
"diffuse" 		{Devolver(DIFFUSE_);}

{nreal}			{yylval.real = atof(yytext);Devolver(FLOAT_);}
{identificador}	{Devolver(ID_); }
{cadena}	{Devolver(CADENA_);}

.		{printf("error léxico \n");}

%%
