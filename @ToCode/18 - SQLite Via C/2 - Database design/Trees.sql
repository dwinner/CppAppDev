

.headers on
.mode column
.nullvalue [NULL]

.echo on

-- This is our example tree:

-- 1 A
-- 2  A.1
-- 3   A.1.a
-- 4  A.2
-- 5   A.2.a
-- 6   A.2.b
-- 7  A.3


-- The tree table is a adjacency model:

CREATE TABLE tree (
  node   INTEGER   NOT NULL   PRIMARY KEY,
  name   TEXT,
  parent INTEGER   REFERENCES tree );


INSERT INTO tree VALUES ( 1, 'A',     NULL );
INSERT INTO tree VALUES ( 2, 'A.1',   1 );
INSERT INTO tree VALUES ( 3, 'A.1.a', 2 );
INSERT INTO tree VALUES ( 4, 'A.2',   1 );
INSERT INTO tree VALUES ( 5, 'A.2.a', 4 );
INSERT INTO tree VALUES ( 6, 'A.2.b', 4 );
INSERT INTO tree VALUES ( 7, 'A.3',   1 );



-- The nest table is a nested-set:

CREATE TABLE nest (
  name  TEXT,
  lower INTEGER   NOT NULL   UNIQUE,
  upper INTEGER   NOT NULL   UNIQUE,
  CHECK ( lower < upper ) );


INSERT INTO nest VALUES ( 'A',      1, 14 );
INSERT INTO nest VALUES ( 'A.1',    2,  5 );
INSERT INTO nest VALUES ( 'A.1.a',  3,  4 );
INSERT INTO nest VALUES ( 'A.2',    6, 11 );
INSERT INTO nest VALUES ( 'A.2.a',  7,  8 );
INSERT INTO nest VALUES ( 'A.2.b',  9, 10 );
INSERT INTO nest VALUES ( 'A.3',   12, 13 );



