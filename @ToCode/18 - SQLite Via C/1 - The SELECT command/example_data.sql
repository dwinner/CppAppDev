
-- This file can be run inside sqlite3 
-- using the command ".read example_data.sql"

-- This data has been pre-loaded into the database
-- file "examples.sqlitedb".  You can open it in sqlite3
-- on the command line using the command "sqlite3 examples.sqlitedb"

.headers on
.mode column
.nullvalue [NULL]

.echo on


CREATE TABLE x ( a, b );
INSERT INTO x VALUES ( 1, 'Alice' );
INSERT INTO x VALUES ( 2, 'Bob' );
INSERT INTO x VALUES ( 3, 'Charlie' );

CREATE TABLE y ( c, d );
INSERT INTO y VALUES ( 1, 3.14159 );
INSERT INTO y VALUES ( 1, 2.71828 );
INSERT INTO y VALUES ( 2, 1.61803 );

CREATE TABLE z ( a, e );
INSERT INTO z VALUES ( 1, 100 );
INSERT INTO z VALUES ( 1, 150 );
INSERT INTO z VALUES ( 3, 300 );
INSERT INTO z VALUES ( 9, 900 );

