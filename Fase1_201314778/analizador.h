#ifndef ANALIZADOR_H_INCLUDED
#define ANALIZADOR_H_INCLUDED

#include <string.h>
#include "acciones.h"



static char newline = '\n';
static char sharp = '#'; // utilizada para comentarios
static char space = ' ';
static char mas = '+';
static char menos = '-';
static char punto = '.';
static char pcoma = ';';
static char dosp = ':';
static char divide = '\\';
static char slash = '/';
static char comillas = '\"';
static char point = '.';

static int caso=0;
int band=0;
int v=0;
int o=0;



//palabras reservadas - sujeta a cambios
char * reservadas [] = {
    "mkdisk","-size","+unit","-path","-name",
    "rmdisk", //-path
    "fdisk","+type","+fit","+delete","+add", //-size,+unit,-path,-name
    "mount", //-path,-name
    "umount","-id",

    "df","+k","+m","+h","+i",
    "du","+n","-h", //-path
    "mkfs","+fs", //-id,+type,+add,+unit

    "login","-usr","-pwd",
    "logout",
    "mkgrp", //-id,-name
    "rmgrp", //-id,-name
    "mkusr","-grp", //-id,-usr,-pwd
    "rmusr", //-id,-usr
    "chmod","ugo","+r", //-id,-path
    "mkfile","+p","+size","+cont", //-id,-path
    "cat","-file", //-id
    "rm","+rf",  //-id,-path
    "edit",  //-id,-path,+size,+cont
    "ren",  //-id,-path,-name
    "mkdir",  //-id,-path,+p
    "cp","-dest","-iddest", //-id,-path
    "mv",  //-id,-path,-dest,-iddest
    "find","?","*","+perm","user",  //-id,-path,-name,-usr
    "chown", //-id,-path,+r,-usr
    "chgrp", //-usr,-grp
    //agregar enlace simbolico ln en fase2
    "ulink","-link",
    //agregar convert ext2 to ext3 en fase2
    "loss", //-ide
    "rep", "+ruta", //-name,-path,-id,
    "mbr","disk", //para rep
    "inode","journaling","block","bm_inode","bm_block","tree","sb","file", //para rep
    "ls +i","ls +l", //para rep - verificar en fase2
    "exec" //-path

};

//contendor para los comandos
struct cont
{
    char id [450];
    char cont[450];
};
typedef struct cont contiene;

    contiene contenedor[50];

//conjunto de comandos - verificar idea luego
struct conjunto
{

    int c;
    char id [450];
    char cont[450];

};
typedef struct conjunto conto;
conto contos[10];


//verifica si un caracter es letra
static int letter(char car)
{

    int aux = 0;
    aux = (int)car;
    if(aux>64 && aux<91 || aux>96 && aux<123)
    {
        return 1;
    }

    return 0;
}

//verifica si un caracter es numero
static int num(char n)
{
    int aux = 0;
    aux = (int)n;
    if(aux>47 && aux<58)
    {
        return 1;
    }

    return 0;
}

static int tipo_par_p(char t)
{

    if(t==mas||t==menos||t==punto)
    {
        return 1;
    }

    return 0;
}

static int ispace(char t)
{
    if(t==space)
    {
        return 1;
    }
    return 0;
}


static int isnewline_final(char t)
{
    if(t==newline||t==pcoma)
    {
        return 1;
    }
    return 0;
}

static int isharp(char t)
{
    if(t==sharp)
    {
        return 1;
    }
    return 0;
}


static int ispoint(char t)
{
    if(t==point)
    {
        return 1;
    }
    return 0;
}

static int islash(char t)
{
    if(t==slash)
    {
        return 1;
    }
    return 0;
}

static int fin(char t)
{

    if (t == pcoma)
    {
        return 1;
    }
    return 0;
}

static int isdoublep(char t)
{
 if (t == dosp)
    {
        return 1;
    }
    return 0;
}

static int iscomillas(char t)
{
 if (t == comillas)
    {
        return 1;
    }
    return 0;
}

//verifica si una cĵĵĵĵĵ de caracteres es una palabra reservada
static int reserved(char *w)
{
    int c =0;
    while(c<76)
    {
        if(strcmp(w,reservadas[c])==0)
        {
            return 1;
        }

        c++;
    }
    return 0;
}



//convierte una cadena de caracteres en minusculas para no diferenciar mayusculas de minusculas
static char * to_lower(char *cad)
{
    char cdobles='\"';
    while(*cad!='\0')
    {
        if(*cad>64 && *cad<91)
        {
            if((*cad)==cdobles)
            {
                while(*cad==cdobles)
                {
                    *cad+=32;
                    cad++;
                }
            }
            else
            {
                *cad+=32;
            }
        }
        if((*cad)==cdobles)
        {
            cad++;
            while(*cad!=cdobles)
            {
                cad++;
            }
        }
        cad++;
    }

    return cad;
}


//para utilizar el script con comandos - falta implementar - no terminado
void read_file(char entrada[])
{
    FILE *script = fopen("/home/duglas/script.sh", "r" );
    char aux[22000];



    if (!script)
    {
        while (feof(script)==0)
        {
            fgets(aux,22000,script);
            strcat(entrada,aux);
        }
        fclose(script);
    }
    else
    {
        printf( "Error al abrir el archivo.\n");
    }
}


//metodo para crear el archivo binario que simula el disco - falta implementar - no iniciado
void mkdisk(int longitud, contiene scan[])
{

}



//automata que reconoce la entrada de comandos - no terminado
void automata(char entrada [] ) {


    char aux [2000];
    aux[0] = entrada[0];

    int  c;
    int  k=0;
    int  cmd=0;
    aux [0] = to_lower(&entrada[0]); // prueba de conversion
    to_lower(&entrada[0]);
    char comand [2000];

    int  o=0;
    while(o<50){
        strcpy(contenedor[o].id,"none");
    o++;
    }

    for (c=0;c<strlen(&entrada[0]);c++){

        switch(caso){

        case 0:

            if(letter(entrada[c]))
            {

                printf("%s es letra\n",&entrada[c]);

                comand[k]=entrada[c];
                caso = 1;
                k++;
            }
            else if(num(entrada[c]))
            {

                printf("%s es numero\n",&entrada[c]);

            }
            else if(ispace(entrada[c]))
            {
                printf("%s es espacio\n",&entrada[c]);
                caso = 0;
            }
            else if(isnewline_final(entrada[c]) || isharp(entrada[c])||fin(entrada[c]))
            {
                printf("%s es salto de linea\n",&entrada[c]);
                //comienza
                  strcpy(contenedor[cmd].cont,comand);
                  cmd++;

                  int cc=0;
                  k=caso=0;
                  int comandlen = strlen(comand);
                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }

          //       agregar_ins(contenedor);

                  cc=0;
                  while(cc<50){
                        strcpy(contenedor[cc].id,"none");
                        cc++;
                    }
            }
            else if(entrada[c]==sharp)
            {
                caso = 10;
            }
            else if(islash(entrada[c]))
            {
                printf("%s es slash",&entrada[c]);
                caso = 0;
            }
            else if(tipo_par_p(entrada[c]))
            {
                comand[k]=entrada[c];
                k++;
                caso = 1;
            }

            break;

        case 1:

            if(ispace(entrada[c]))
            {
                if(reserved(&comand[0]))
                {
                    printf("es reservada\n");
                    strcpy(contenedor[cmd].id,comand);
                  cmd++;

                  int cc=0;
                  k=caso=0;

                  int comandlen = strlen(comand);

                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }

                }
                else
                {
                    printf("%s: comando no encontrado",comand);
                    int cc=0;
                  k=caso=0;
                  int comandlen = strlen(comand);
                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }
                }
            }
            else if(isnewline_final(entrada))
            {
              printf("Comando no completado.");

            }
            else if(letter(entrada[c]))
            {

                comand[k]=entrada[c];
                k++;
            }
            else if(ispoint(entrada[c])){
                comand[k]=entrada[c];
                k++;
            }
            else if(num(entrada[c]))
            {

                comand[k]=entrada[c];
                k++;
            }
            else if(isharp(entrada[c]))
            {
               caso=10;
            }
            else if(isdoublep(entrada[c]))
            {
                if(reserved(&comand[0]))
                {
                    printf("es reservada\n");
                    strcpy(contenedor[cmd].id,comand);

                  int cc=0;
                  k=0;
                  caso=3;
                  int comandlen = strlen(comand);
                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }

                }
                else
                {
                    printf("%s: comando no encontrado",comand);
                    int cc=0;
                  k=0;
                  caso=3;

                  int comandlen = strlen(comand);

                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }
                }

            }


            break;

        case 2:

            if(letter(entrada[c]))
            {
                comand[k]=entrada[c];
                k++;
            }
            else if(num(entrada[c]))
            {
                comand[k]=entrada[c];
                k++;
            }
            else if(ispace(entrada[c]))
            {
                    strcpy(contenedor[cmd].cont,comand);
                    cmd++;
                  int cc=0;
                  k=caso=0;
                  int comandlen = strlen(comand);
                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }
            }
            else if(ispoint(entrada[c])){
                comand[k]=entrada[c];
                k++;
            }
            else if(isharp(entrada[c]))
            {
                caso=10;
            }
            else if(isharp(entrada[c])|isnewline_final(entrada[c]))
            {
                printf("%s es salto de linea\n",&entrada[c]);
                //comienza
                  strcpy(contenedor[cmd].cont,comand);
                  cmd++;

                  int cc=0;
                  k=caso=0;
                  int comandlen = strlen(comand);
                  while(cc<comandlen)
                  {
                    comand[cc]='\0';
                    cc++;
                  }

                  //guardar comando()
                  agregar_ins(contenedor);

                  cc=0;
                  while(cc<20){
                        strcpy(contenedor[cc].id,"none");
                        cc++;
                    }
            }
            else if(iscomillas(entrada[c]))
            {
              caso=5;
            }


            break;

            case 3:

            if(isharp(entrada[c]))
                {
                caso=10;
            }
            else if(isdoublep(entrada[c]))
            {
                caso=2;
            }
            else
            {
                printf("Error al leer comando.");
            }

            break;

            case 5  :

             if(isharp(entrada[c]))
             {
                comand[k]=entrada[c];

                caso = 10;
                k++;
            }
            else if(!iscomillas(entrada[c])&!isnewline_final(entrada[c]))
            {
                comand[k]=entrada[c];
                k++;
            }
            else if(iscomillas(entrada[c]))
            {
                caso=2;
            }
            else if(isnewline_final(entrada[c]))
            {
                printf("Error al en el cierre de comillas");
            }

            break;

        default:
           printf("coment");//temporal
            if(isnewline_final(entrada[c]))
            {
                caso = 0;
            }

            break;

        }
    }

}

int instruc=0;

void define_instruc (contiene aux[],int inst, int i)
{



inst =0;

printf("%s",aux[i].id);



}


void agregar_ins(contiene aux[])
{
int inst = 0;
    int c=0;
    while(c<50)
    {

printf("%s",aux[c].id);
        inst = !strcmp(aux[c].id,"mkdisk") ? 1 : inst;
        inst = !strcmp(aux[c].id,"mrdisk") ? 2 : inst;
        inst = !strcmp(aux[c].id,"fdisk") ? 3 : inst;

        strcpy(&t_comandos[c].mkdisk.nombre,"hola");

    c++;
    }

}




#endif // ANALIZADOR_H_INCLUDED
