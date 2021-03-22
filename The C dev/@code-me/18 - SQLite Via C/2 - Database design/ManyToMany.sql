
.headers on
.mode column
.nullvalue [NULL]

.echo on

PRAGMA foreign_keys = 1;

CREATE TABLE people ( pid INTEGER   PRIMARY KEY, name TEXT );
CREATE TABLE groups ( gid INTEGER   PRIMARY KEY, name TEXT );

CREATE TABLE p_g_bridge (
        pid INTEGER   NOT NULL   REFERENCES people,
	gid INTEGER   NOT NULL   REFERENCES groups,
	PRIMARY KEY ( pid, gid )
);


-- people
INSERT INTO people VALUES ( 1, 'Alice' );
INSERT INTO people VALUES ( 2, 'Bob' );
INSERT INTO people VALUES ( 3, 'Charlie' );

-- groups
INSERT INTO groups VALUES ( 1, 'users' );
INSERT INTO groups VALUES ( 2, 'admin' );
INSERT INTO groups VALUES ( 3, 'web' );
INSERT INTO groups VALUES ( 4, 'db' );
INSERT INTO groups VALUES ( 5, 'nobody' );



-- everyone in users
INSERT INTO p_g_bridge VALUES ( 1, 1 );
INSERT INTO p_g_bridge VALUES ( 2, 1 );
INSERT INTO p_g_bridge VALUES ( 3, 1 );

-- Alice and Bob into admin
INSERT INTO p_g_bridge VALUES ( 1, 2 );
INSERT INTO p_g_bridge VALUES ( 2, 2 );

-- Charlie into web
INSERT INTO p_g_bridge VALUES ( 3, 3 );

-- Alice and Charlie into db
INSERT INTO p_g_bridge VALUES ( 1, 4 );
INSERT INTO p_g_bridge VALUES ( 3, 4 );


