#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main(void) {
    
    sqlite3 *db;
    char *errMsg = NULL;
    
    /* Try to open the database */ 
    int rc = sqlite3_open("study_information.db", &db);
    
    /* Check if database opened */
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        
        /* Destructor for sqlite3 */
        sqlite3_close(db);
        
        return EXIT_FAILURE;
    }

    /* Prewritten SQL query */
    
    /** Ülesanne 2, osa 1. päring 1 **/
    //~ char *sql = "SELECT * FROM subjects WHERE credits < 6;";
    
    /** Ülesanne 2, osa 1. päring 2 **/
    //~ char *sql = "SELECT * FROM subjects "
				//~ "WHERE assesment_type "
				//~ "LIKE 'Exam%' "
				//~ "ORDER BY credits ASC;";
				
	/** Ülesanne 2, osa 2. päring 1 **/
	//~ char *sql = "SELECT eid AS 'Isikukood', fname AS 'Eesnimi', lname AS 'Perenimi', grade AS 'Hinne' "
				//~ "FROM students "
				//~ "JOIN declarations ON students.id = declarations.student_id "
				//~ "WHERE students.fname LIKE 'Marko';"; 
	
	/** Ülesanne 2, osa 2. päring 2 **/
	//~ char *sql = "SELECT eid AS 'Isikukood', fname AS 'Eesnimi', "
				//~ "lname AS 'Perenimi', grade AS 'Hinne', "
				//~ "name_et AS 'Aine nimi', code AS 'Aine kood', " 
				//~ "credits AS 'Ainepunktid' "
				//~ "FROM students "
				//~ "JOIN declarations ON students.id = declarations.student_id "
				//~ "JOIN subjects ON subjects.id = declarations.subject_id "
				//~ "WHERE students.fname LIKE 'Frank Christopher' "
				//~ "ORDER BY grade DESC;";
	
	/** Ülesanne 2, osa 3 **/
	char *sql = "SELECT eid AS 'Isikukood', fname AS 'Eesnimi', "
				"lname AS 'Perenimi', name_et AS 'Aine nimi', "
				"code AS 'Aine kood', "
				"SUM(credits) AS 'Teenitud EAPd', "
				"ROUND(SUM(grade * credits * 1.00) / SUM(credits), 2) AS 'Kaalutud keskmine hinne' "
 
				"FROM students "
				"JOIN declarations ON students.id = declarations.student_id "
				"JOIN subjects ON subjects.id = declarations.subject_id "
				"GROUP BY students.eid "
				"ORDER BY grade DESC;";
				
    
    /* Attempt to execute the query */
    rc = sqlite3_exec(db, sql, callback, NULL, &errMsg);
    
    /* Check if the query failed */
    if (rc != SQLITE_OK ) 
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        
        /* Frees the message */
        sqlite3_free(errMsg);        
        
        /* Destruc    r for sqlite3 */
        sqlite3_close(db);
        
        return EXIT_FAILURE;
    } 
    
    /* Destructor for sqlite3 */
    sqlite3_close(db);
    
    return EXIT_SUCCESS;
}


int callback(void *NotUsed, int argc, char **argv, char **azColName) 
{
    int i;
    for (i = 0; i < argc; i++) 
    {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
