
.headers on
.mode column
.nullvalue [NULL]

.echo on

PRAGMA foreign_keys = 1;

-- The main table

CREATE TABLE employee ( 
	employee_id  INTEGER   NOT NULL   PRIMARY KEY,
	name         TEXT   NOT NULL
	/* ... */
);


-- The detail table, which contains the photo_data BLOB value

CREATE TABLE employee_photo (
	employee_id  INTEGER   NOT NULL   PRIMARY KEY
	                                  REFERENCES employee,
	photo_data   BLOB
	/* ... */
);



INSERT INTO employee VALUES ( 1, 'Bob' );
INSERT INTO employee VALUES ( 2, 'Lisa' );
INSERT INTO employee VALUES ( 3, 'Jim' );

-- In this example, the "photo_data" values is just random data

INSERT INTO employee_photo VALUES ( 1, x'95BAE1F4EB4A7E43' /* ... */ );
INSERT INTO employee_photo VALUES ( 2, x'1C9B1E483E4F2734' /* ... */ );


