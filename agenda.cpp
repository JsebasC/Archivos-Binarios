/*
*******************************************************************************
¿Que hace el Programa?        
     Progrma que tiene el siguiente menu:
    - Crear Archivo( Lo unico que hace es crear un archivo: agenda.dat y borrar su contenido, claro si esta ya creado)
    - Agregar (Agrega en el Archivo Binario)
    - Eliminar(Elimina en el Archivo Binario)
    - Listar (Munestra los elementos por medio del Arhcivo Binario)
    - Bucar un Amigo (Busca algun elemento del Archivo, por medio del Archivo Binario) 
    con la sig. información:     Nombre, Edad, Telefono y Direccion
*******************************************************************************
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>// Booleanos
/*typedtypedef struct {
    char nom[25];
    int edad;
    char tel[15];
    char dir[35];
}Amigo;*/

struct Amigo {
    char nom[25];
    int edad;
    char tel[15];
    char dir[35];
    int cc; // creamos un campo para la cedula
};

/*Funciones de Archivo*/
void Crear(void);
void Listar(void);
void Agregar(void);
void Modificar(void);
void Borrar(void);
void Encontrar(void);
bool Verificar(int); //funcion para verificar


FILE *abrir_fichero_b(char cadena[], int);

/*Nombre del Archivo a guardar*/
char nombre_fichero[] = "agenda.dat";
char borrar_fichero[] = "paso.$$$";

FILE *abrir_fichero_b(char cadena[], int metodo);

int main()
{
    FILE *fp;
    int opc;
    char cad[3];
    
    fp = abrir_fichero_b(nombre_fichero,0);
    if( fp )
    {
        fclose(fp);
    }
    else
    {
        printf( "Error (NO ABIERTO)\n" );
        puts("Presiona cualquier tecla para continuar.... y Crear el Archivo");
        fp = abrir_fichero_b(nombre_fichero,1);
        fclose(fp);
        getch();    
	}
    
    do{
   		 system("cls");
        puts("1. Crear Archivo (Cuidado, elimina lo que ya se tiene en el Archivo)");
        puts("2. Agregar\n3. Eliminar\n4. Listar\n5. Buscar\n6. Modificar\n7. Salir");
        puts("?Introduce tu opcion y depues enter.");
        
        opc = atoi(gets(cad));
        while(opc<0 || opc>7) /*Limitando la entrada de las opciones*/    
            opc = atoi(gets(cad));
        system("cls");    
        switch(opc)
        {
        case 1:
                Crear();
                break;
        case 2:    
                Agregar();
                break;
        case 3:
                Borrar();
                break;
        case 4:
                Listar();
                break;
        case 5:
                Encontrar();
                break;
        case 6:
                 Modificar();
                break;
            
        }
        
        /*Solo parar cuando sea una de las opciones*/
        if(opc<7)
        {
        	printf("\n                          <-- REGRESANDO AL MENU --> ");
            puts("\n\nPresiona Cualquier Tecla para Regresar al Menu");
           
            getch();
        }
    }
    while(opc!=7);
    
    return 0;
}

// FUNCION PARA CREAR UN ARCHIVO
/*****************************************************************
Funcion que sirve para borrar todo el Contenido del Archivo Binario*/

void Crear(){
   FILE *fp;

   fp = abrir_fichero_b(nombre_fichero,0);
   if(fp)
   {
        printf("\n Error de apuertura del archivo agenda.dat\n");
        fclose(fp);  
   }
}


/********************************************************
Funcion que sirve para imprimir todos los  un registros del Archivo Binario*/
void Listar(void){
   FILE *fp;
   int i=1;
   Amigo aux;
    fp = abrir_fichero_b(nombre_fichero,0);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
      printf("\n U S U A R I O S  E N  L A  A G E N D A\n");
      printf("---------------------------------------------------------------\n");
      while ((fread(&aux, sizeof(aux), 1, fp))!=0){
      	 printf("                  ");
        printf("<--- DATOS DEL AMIGO %d --->\n",i); 	 
         	
        printf("Cedula: %d\nNombre: %s\nEdad: %d\nTelefono: %s\nDireccion: %s ",aux.cc,aux.nom,aux.edad,aux.tel,aux.dir); //MOSTRAMOS 
		printf("\n---------------------------------------------------------------\n");
      
        i++;
      }
 
      fclose(fp);
   }
}

/********************************************************
Funcion que sirve para agregar un registro dentro del Archivo Binario*/
void Agregar(void){
	FILE *fp;
   	Amigo aux;
   	char cad[3],cc[50];
   //creamos variables 
	int existe=0,cedula;
	int n;
   //	printf("\n Agregando un Amigo Nuevo al archivo binario agenda.dat\n");
   	fp=abrir_fichero_b(nombre_fichero,3); // Lectura y escritura 
   	if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
   	else{   
   			printf("---------------------------------------------------------------\n");
	      	printf("           ");
	        printf("<--- A G R E G A R   E N  L A  A G E N D A --->\n"); 	 
        printf("\nDigite la cedula para agregar: "); // digitamos la cedula para agregar o para buscar
  		cedula=atoi(gets(cc)); // obtenemos cedula en la variable
    	if (cedula>0) // control para validar numeros mas grandes q 0
        { 
			while ((n=fread(&aux, sizeof(aux), 1, fp))!=0){ // este ciclo nos permitira comprobar si existe la persona
				if (cedula==aux.cc){//comparando la cedula digitada con la que tenemos..
					printf("\n");
				 	printf("                      ");
					printf("<-- Existe esta persona --> ");
					existe=1; // nos avisara si existe y si entra sacamos el archivo
					fclose(fp);		
	   			}
	   	   }
	   	   if(existe==0){
	     	    aux.cc=cedula; //asignamos el valor recogido si no existe servira para no volverla a digitar la cedula
				printf("Dame el nombre del Amigo: ");
	     		gets(aux.nom);
		        printf("Dame la Edad del Amigo: ");
		        aux.edad=atoi(gets(cad));
		        printf("Dame el telefono del Amigo: ");
		        gets(aux.tel);
		        printf("Dame la direccion del Amigo: ");
		        gets(aux.dir);
		        fwrite(&aux, sizeof(aux), 1, fp);
		        fclose(fp); //cerramos archivo permiso 2  
			} 	
	   }else{
	   		printf("\n");
			printf("                            ");
			printf("<-- E R R O R  --> ");//mensaje si la cedula es menor a 0	
	   }
   
    }
}




/********************************************************
Funcion que sirve para Modificar un registro dentro del Archivo Binario*/
void Modificar(void)
{	
FILE *fp;
   Amigo    aux;
   int n;
   int existe=0; 
    //creamos variables
   char cadena[25],cad[2],cc[40],ope[2];    //creamos variables char
    fp=abrir_fichero_b(nombre_fichero,3);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
		printf("---------------------------------------------------------------\n");
      	printf("           ");
        printf("<--- M O D I F I C A R --->\n"); 
       	printf("\nDigite la cedula a modificar: ");
	        int cedula; // se crea variable para guardar lo digitado
	  		cedula=atoi(gets(cc));
	  		system("cls");
        //Buscando el Amigo dentro del Archivo
      while ((n=fread(&aux, sizeof(aux), 1, fp))!=0){
		   
	      if (cedula==aux.cc){ /// se compara por si queremos modificar
	      	int op=0; //opcion de 1 a 5
	     
	      	while(op!=7){
	      	 		printf("\n A M I G O   E N C O N T R A D O\n"); //mostramos los datos del amigo
				    printf("\n");
		        	printf("Cedula: %d\nNombre: %s\nEdad: %d\nTelefono: %s\nDireccion: %s ",aux.cc,aux.nom,aux.edad,aux.tel,aux.dir); //MOSTRAMOS 
					printf("\n---------------------------------------------------------------\n");
			        printf("\nDigite opcion a modificar:\n"); // por si queremos modificar solo un campo
		        	printf("\n---------------------------------------------------------------\n");
		        printf("Digite 1 - Para editar Cedula.\n");
		        printf("Digite 2 - Para editar Nombre.\n");
		        printf("Digite 3 - Para editar Edad.\n");
		        printf("Digite 4 - Para editar Telefono.\n");
		        printf("Digite 5 - Para editar Direccion.\n");
		        printf("Digite 6 - Para Guardar.\n");
		        printf("Digite 7 - Salir.\n");
				op=atoi(gets(ope)); //obtenemos la opcion
	      	
		      	switch(op){ // si el usuario elige una opcion entrara en el ciclo
			      	case 1:{ // se utilizan llave como regla general en la programacion con switch a la hora de declarar variables
			      			int nueva;
			      			printf("\nCual es la nueva Cedula del Amigo: "); //
	  						nueva=atoi(gets(cc));	//si rve pra poder entrar a la funcion y ayudar a buscar
			      			bool verificar = 0;
							Verificar(nueva);
			      			verificar=Verificar(nueva); // se obtiene el return de la funcion
		      				if(!verificar){ // si es igual a falso 
							    aux.cc=nueva; // se asigna la digitada
							    printf("\n");
								printf("                      ");
								printf("<--PULSA 6 PARA GUARDAR --> ");	
						//		printf("<--GRABANDO Y CERRANDO ARCHIVO--> ");	
								getch();
							}else{
								if(cedula==nueva){
									printf("\n");
							 		printf("                      ");
									printf("<-- Estas digitando la misma cedula registrada --> "); // un mensaje de aviso para el usuario
									  aux.cc=nueva; // se asigna la digitada
									getch();
								}else{
									printf("\n");
							 		printf("                      ");
									printf("<--Erroor, Ya  Existe otro amigo registrado con este cedula --> ");
									getch();
								}
							
							}
						

					  	break;
					}
			      	case 2:
			      		printf("Cual es el nuevo nombre del Amigo: ");
			       		gets(aux.nom);
			       		 printf("\n");
						printf("                      ");
						printf("<--PULSA 6 PARA GUARDAR --> ");	
					//	printf("<--GRABANDO Y CERRANDO ARCHIVO--> ");
			      		break;
			      	case 3:
			      	    printf("Cual es la nueva Edad del Amigo: ");
			            aux.edad=atoi(gets(cad));
			            printf("\n");
						printf("                      ");
						printf("<--PULSA 6 PARA GUARDAR --> ");	
					//	printf("<--GRABANDO Y CERRANDO ARCHIVO--> ");
			      		break;
			      	case 4:
			      		printf("Cual es el nuevo telefono del Amigo: ");
			            gets(aux.tel);
			            printf("\n");
						printf("                      ");
						printf("<--PULSA 6 PARA GUARDAR --> ");	           
					//	printf("<--GRABANDO Y CERRANDO ARCHIVO--> ");
			      		break;
			      		
			      	case 5:
			      		printf("Cual es la nueva direccion del Amigo: ");
			            gets(aux.dir);
			            printf("\n");
						printf("                      ");
						printf("<--PULSA 6 PARA GUARDAR --> ");	
			      		break;
			      	
			      	case 6:
			      		 fseek(fp,-1 *sizeof(aux), SEEK_CUR);
			   			 fwrite(&aux, sizeof(aux), 1, fp);
			 			 //	 fclose(fp);   //Cerramos el archivo
			   			 existe=1; //verificacion si existe el amigo
			   			printf("\n");
						printf("                      ");
						printf("<-- GRABANDOO... Enter para continuar --> ");
						getch();
			   			 break;
				  }
	      
			
				system("cls");
			  }
			  
			  fclose(fp);   //Cerramos el archivo
	  }
	  
	      
    }
   //  fclose(fp);   //Cerramos el archivo
     
   }	 
	 if(existe==0){
	 		printf("\n");
		 	printf("                      ");
			printf("<-- NO Existe esta persona --> ");
     	fclose(fp);	
	 }
	   
}





/********************************************************
Funcion que sirve para borrar un registro dentro del Archivo Binario*/
void Borrar(void){
   FILE *fp,*fd;
   Amigo    aux;
    int encontrado=0;
	char cadena[25],cc[40];
    printf("Digite la cedula a eliminar: ");
    int cedula; // se crea variable para buscar el amigo
  	cedula=atoi(gets(cc)); 	
   printf("\n BORRANDO REGISTROS  \n");
   fp=abrir_fichero_b(nombre_fichero,0);
   if(!(fp))
       printf("\n Error de apuertura del archivo agenda.dat\n");
   else{
       fd=abrir_fichero_b(borrar_fichero,1);
      if(!(fd))
         printf("\n Error Imposible crear archivo auxiliar\n");
      else{
         while ((fread(&aux, sizeof(aux), 1, fp))!=0)
            if(cedula==aux.cc) // comparamos
             encontrado=1; //variable que nos avisara si se han econtrado el amigo para luego borrar
            else
             
        	fwrite(&aux, sizeof(aux), 1, fd);
         	fclose(fd);
      }
      fclose(fp);
      if(encontrado){
         system("del agenda.dat");
         system("ren paso.$$$ agenda.dat");
         printf("\n Registro BORRADO con Exito!!!\n");
      }
      else{
         system("del paso.$$$");
         printf("\n El Registro NO SE ENCONTRO, no fue borrado!!!");
      }
   }
}





/******************************************
Funcion para Encontrar un Amigo e imprimir sus datos*/
void Encontrar(void){
 FILE *fp;
    Amigo    aux;
    int n;
    char cadena[25],cc[50];
	printf("Digite Cedula para Encontrar: "); 
 	int cedula; // se crea variable
    scanf("%i", &cedula); // la cual esta va tomar el valor por teclad
	int existe=0; 
   //printf("\n Buscando a un Amigo  \n");
    fp=abrir_fichero_b(nombre_fichero,0);
    if(!(fp))
        printf("\n Error de apuertura del archivo agenda.dat\n");
    else{
        while ((n=fread(&aux, sizeof(aux), 1, fp))!=0 ){ //Leyendo el archivo...
         if (cedula==aux.cc){//comparando la cedula digitada con la que tenemos..
     		printf("---------------------------------------------------------------\n");
	      	printf("           ");
	        printf("<--- U S U A R I O   E N  L A  A G E N D A --->\n"); 	 
	        printf("Cedula: %d\nNombre: %s\nEdad: %d\nTelefono: %s\nDireccion: %s ",aux.cc,aux.nom,aux.edad,aux.tel,aux.dir); //MOSTRAMOS 
			printf("\n---------------------------------------------------------------\n");
	       
	      	existe=1; //hemos encontrado cambia el valor
		  }
		}
	     if(existe==0){ // nos servira para mostrar que no existe si no entra en el if
        		printf("\n");
			 	printf("                      ");
				printf("<-- NO Existe esta persona --> ");
        	
		}
    }
      fclose(fp);   //Cerramos el archivo
}


bool Verificar(int nueva){ // Funcion que me verifica si existe la cedula digitada
 	FILE *fp;
   	Amigo aux;
   	char cad[3],cc[50];
   //creamos variables 
	int existe=0;
	int n;
   	fp=abrir_fichero_b(nombre_fichero,0); // Lectura y escritura 
   	if(!(fp)){
	  
        printf("\n Error de apuertura del archivo agenda.dat\n");
    }else{   
			while ((n=fread(&aux, sizeof(aux), 1, fp))!=0){ // este ciclo nos permitira comprobar si existe la persona
				if (nueva==aux.cc){//comparando la cedula digitada con la que tenemos..
				
					existe=1; // nos avisara si existe y si entra sacamos el archivo
					  fclose(fp); 
					return true;
	   			}
	   	
	   	   }
	   	
	   	   if(existe==0){
	   	   	   fclose(fp); 
	   	   	 return false;
	   	   	 
			}
			
			 
    }
 
}
/*************************************************
Funcion que Carga el Archivo y regresa un apuntador con que se va ha manejar el Archivo
Recibe:     El nombre del Archivo , Y el método con que se va abrir el Archivo
Un Apuntador tipo Archivo, 0 - Solo Lectura , 1 - Para crearlo de nuevo desde cero, 
2 - Anhadir Informacion, 3 - para Lectura y Escritura.        
 Regresa:    El apuntador de Tipo FILE, con el cual se abrio*/
FILE *abrir_fichero_b(char cadena[], int metodo){
    FILE *x;
    switch(metodo){
        case 0:
            x = fopen(cadena,"rb");
            break;
        case 1:
            x = fopen(cadena,"wb");
            break;
        case 2:
            x = fopen(cadena,"ab");
            break;
        case 3:
            x = fopen(cadena,"r+b");
            break;
    }
    return x;
}

