
.headers on
.mode column
.nullvalue [NULL]

.echo on

.load wtavg.sqlite3ext wtavg_init

CREATE TABLE t ( class, value, weight );

INSERT INTO t VALUES( 1, 3.4, 1.0 );
INSERT INTO t VALUES( 1, 6.4, 2.3 );
INSERT INTO t VALUES( 1, 4.3, 0.9 );
INSERT INTO t VALUES( 2, 3.4, 1.4 );
INSERT INTO t VALUES( 3, 2.7, 1.1 );
INSERT INTO t VALUES( 3, 2.5, 1.1 );

.echo off

