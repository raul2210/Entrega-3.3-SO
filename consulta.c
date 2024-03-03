#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Consulta los datos de los ganadores y escribe en pantalla los nombres de lo ganadores en un fecha
void NombreFecha(MYSQL *conn, int fecha)
{
	int err = mysql_query(conn,"use jugadoresCartas");
	err = mysql_query(conn,"SELECT * FROM Partidas");
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	resultado =mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	if(row == NULL)
	{
		printf("no se ha encontrado nada");
	}
	else
	{
			while(row != NULL)
			{
				int fechaSQL = atoi(row[2]);
				if(fechaSQL == fecha)
				{
					printf("El ganador del año %d es %s\n",fechaSQL, row[1]);
				}
				row = mysql_fetch_row(resultado);
			}
	}
}

int main(int argc, char *argv[]) {

	//Conector para acceder al servidor de bases de datos
	MYSQL *conn;
	int err;
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion, indicando nuestras claves de acceso
	// al servidor de bases de datos (user,pass)
	conn = mysql_real_connect (conn, "localhost","root", "mysql", NULL, 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	NombreFecha(conn,1010001);
	return 0;
}

