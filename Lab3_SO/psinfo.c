#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program can give info about status of a process */

/* Struct that contain the info about process */
typedef struct InfoProceso {
	char PID[20];					/**< PID process */
	char nombre[20];				/**< Name process */
	char estado[20];				/**< State process */
	char tamanoTotal[20];			/**< Total size of the image memory process */
	char memoriaTEXT[20];			/**< size memory of the section TEXT */
	char memoriaDATA[20];			/**< size memory of the section DATA */
	char memoriaSTACK[20];			/**< size memory of the section STACK */
	char cambiosContextoVol[20];	/**< Voluntary changes context */
	char cambiosContextoNoVol[20];	/**< No-Voluntary changes context */
} infoProceso;

/* Define functions */
void informacionProceso(infoProceso** pr , FILE *fInputStatus);
void mostrarInfoProceso(infoProceso** pr);
void asignarInfoArchivo(infoProceso** pr , FILE *fOutProcess);
void asignarNombreArchivo(int tamano , char *arreglo[] , char* nombreArch);
int BuscarProceso(infoProceso** pr, int tamano , char *arreglo);
void mensajeParamValidos();

/* Main */
int main(int argc, char*argv[]) {

	if (argc < 2){
		printf("missing arguments\n");
		exit(1);
	}

	infoProceso *proceso;
	proceso = (infoProceso *) malloc(sizeof(infoProceso));
	int procesoBuscado; // 1 if dont find the process


	/* When the command -l is entered */
	if (strcmp(argv[1],"-l")== 0) {

		for (int i = 2; i < argc; i++) {
			procesoBuscado = BuscarProceso(&proceso,argc,argv[i]);
			if(procesoBuscado==1) return 1;

			mostrarInfoProceso(&proceso);
		}
	}

	/* When the command -r is entered */
	if(strcmp(argv[1],"-r")== 0){

		char nombreArchivo[80] = "psinfo-report";
		char *archivoNombre;
		archivoNombre = nombreArchivo;

		asignarNombreArchivo(argc,&argv[0],archivoNombre);
		FILE *fOutProcess = fopen(nombreArchivo, "w");

		for (int i =2; i < argc; i++) {
			procesoBuscado = BuscarProceso(&proceso,argc,argv[i]);

			if(procesoBuscado == 1) return 1;
			asignarInfoArchivo(&proceso,fOutProcess);
		}
		fclose(fOutProcess);
	}

	/* When only one number enters */
	 if(strcmp(argv[1],"-r")!= 0 && strcmp(argv[1],"-l")!= 0) {
		 
		 if(argc > 2){
       printf("%s\n", "Too many arguments");
       mensajeParamValidos();
       return 1;
     }
     if(atoi(argv[1])==0){
       printf("%s\n", "Command not found");
       mensajeParamValidos();
       return 1;
     }
		 procesoBuscado = BuscarProceso(&proceso,argc,argv[1]);

		 if(procesoBuscado == 1) return 1;
		 mostrarInfoProceso(&proceso);
	}
	free(proceso);
	return 0;
}


/**
* This method will be used to get process information in the file 'status'.
* @param *pr The Struct where will save the information
* @param *fInputStatus The FILE that cotain the information about process
*/
void informacionProceso(infoProceso** pr, FILE *fInputStatus){

	char name[20],name3[20],name2[20],tam[20];
	char mem1[20], mem2[20],mem3[20],
			 mem4[20], mem5[20], mem6[20];
	int count = 0;
	fscanf(fInputStatus,
		"%s %s"
		"%s %s"
		"%s %s %s",
		name,
		name2,
		mem1,
		mem2,
		mem3,
		mem4,
		mem5
	);

	strcat(mem4,mem5);
	strcpy((*pr)->nombre,name2);
	strcpy((*pr)->estado,mem4);
	printf("%s %s\n", (*pr)->nombre, (*pr)->estado);

	while (fgets(name3,32,fInputStatus)!=NULL) {
		count ++;

		if (count == 16) {
			fscanf(fInputStatus,"%s %s %s", name,name2,tam);
			strcat(name2,tam);
			strcpy((*pr)->tamanoTotal,name2);
		}
		if (count == 24) {
			fscanf(fInputStatus,"%s %s %s"
								"%s %s %s"
								"%s %s %s",
								 name,name2,tam,
								 mem1,mem2,mem3,mem4,mem5,mem6);
			strcat(name2,tam);
			strcat(mem2,mem3);
			strcat(mem5,mem6);
			strcpy((*pr)->memoriaDATA,name2);
			strcpy((*pr)->memoriaSTACK,mem2);
			strcpy((*pr)->memoriaTEXT,mem5);

		}
		if (count == 57) {
			fscanf(fInputStatus,"%s %s"
								"%s %s",
								 name,name2,
								 mem1,mem2);

			strcpy((*pr)->cambiosContextoVol,name2);
			strcpy((*pr)->cambiosContextoNoVol,mem2);
		}
	}
}

/**
* This method will be used to print the info about a process.
* @param *pr The Struct to print
*/
void mostrarInfoProceso(infoProceso** pr) {

	printf("%s%s\n","Numero: " ,(*pr)->PID);
	printf("%s%s\n","Nombre del proceso: " ,(*pr)->nombre);
	printf("%s%s\n","Estado: " ,(*pr)->estado);
	printf("%s%s\n","Tamaño total de la imagen de memoria: ",(*pr)->tamanoTotal);
	printf("%s%s\n","Tamaño de la memoria en la región TEXT: ",(*pr)->memoriaTEXT);
	printf("%s%s\n","Tamaño de la memoria en la región DATA: ",(*pr)->memoriaDATA);
	printf("%s%s\n","Tamaño de la memoria en la región STACK: ",(*pr)->memoriaSTACK);
	printf("%s%s-%s\n",
	"Número de cambios de contexto realizados (voluntarios - no voluntarios): ",
	(*pr)->cambiosContextoVol,(*pr)->cambiosContextoNoVol);

	printf("%s\n","---------------------------------" );
}

/**
* This method will be used to put  process information in the file 'psinfo-report'.
* @param *pr The Struct that contain the process information
* @param *fOutProcess The FILE where will put the information
*/
void asignarInfoArchivo(infoProceso** pr , FILE *fOutProcess){

	char informacion[500];

	sprintf(informacion,
		"Numero: %s\n"
		"Nombre: %s\n"
		"Estado: %s\n"
		"Tamaño total de la imagen de memoria: %s\n"
		"Tamaño de la memoria en la región TEXT: %s\n"
		"Tamaño de la memoria en la región DATA: %s\n"
		"Tamaño de la memoria en la región STACK: %s\n"
		"Número de cambios de contexto realizados (voluntarios - no voluntarios): %s - %s\n",
		(*pr)->PID,
		(*pr)->nombre , (*pr)->estado , (*pr)->tamanoTotal,
		(*pr)->memoriaTEXT , (*pr)->memoriaDATA , (*pr)->memoriaSTACK,
		(*pr)->cambiosContextoVol , (*pr)->cambiosContextoNoVol
	 );

	fputs(informacion, fOutProcess);
	fputs("\n------------\n", fOutProcess);
}

/**
* This method will be used to assign name to the foutput file.
* @param tamano The Int that contain the size of the arguments.
* @param *arreglo[] The array that contain each arguments
* @param *nombreArch The Char with memory address of the name file.
*/
void asignarNombreArchivo(int tamano , char *arreglo[] ,char *nombreArch) {

	for (int i = 2; i< tamano; i++) {
		char temp[10]="-";
		strcat(temp,arreglo[i]);
		strcat(nombreArch,temp);
	}
	strcat(nombreArch ,".info");
	printf("Archivo de salida generado: %s\n",nombreArch);
}

/**
* This method will be used to search if the process exist.
* @param pr The Struct that will contain the process information.
* @param tamano The Int that contain the size of the arguments.
* @param *arreglo The Value that contain process number;
* @return int between 0-1
*/
int BuscarProceso(infoProceso** pr, int tamano , char *arreglo){
	char statFileName[30];
	char *numproc = arreglo;
	sprintf(statFileName, "/proc/%s/status", numproc);
	FILE *fInputStatus = fopen(statFileName, "r");

	if (fInputStatus == NULL){
		printf("%s\n", "Process not found");
		return 1;
	}
	strcpy((*pr)->PID , numproc);
	informacionProceso(pr, fInputStatus);
	fclose(fInputStatus);
	return 0;
}

/**
* This method will be used to print valid commands.
*/
void mensajeParamValidos(){
  printf("%s\n","\nValid commands\n ./psinfo -l \n ./psinfo -r \n ./psinfo 'numberOfProcess'" );
}
