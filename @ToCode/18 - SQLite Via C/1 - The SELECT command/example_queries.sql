
-- This file can be run inside sqlite3 
-- using the command ".read example_queries.sql"

.headers on
.mode column
.nullvalue [NULL]

.echo on





SELECT * FROM x;
SELECT * FROM y;
SELECT * FROM z;

SELECT d, d*d AS dSquared FROM y;

SELECT * FROM x JOIN y;
SELECT * FROM x CROSS JOIN y;
SELECT * FROM x, y;

SELECT * FROM x JOIN y ON a = c;

SELECT * FROM x JOIN z ON x.a = z.a;

SELECT * FROM x JOIN z USING ( a );
SELECT * FROM x NATURAL JOIN z;

SELECT * FROM x LEFT OUTER JOIN z USING ( a );

SELECT * FROM x JOIN y ON x.a = y.c LEFT OUTER JOIN z ON y.c = z.a;

SELECT * FROM x AS x1 JOIN x AS x2 ON x1.a + 1 = x2.a;

SELECT * FROM x WHERE b = 'Alice';

SELECT * FROM y WHERE d BETWEEN 1.0 AND 3.0;

SELECT c, d, c+d AS sum FROM y WHERE sum < 4.0;

SELECT a, count(a) AS count FROM z GROUP BY a;

SELECT a, sum(e) AS total FROM z GROUP BY a;

SELECT a, sum(e), count(e), 
   sum(e)/count(e) AS expr, avg(e) AS agg
  FROM z GROUP BY a;

SELECT a, sum(e) AS total FROM z GROUP BY a HAVING total > 500;

SELECT * FROM y ORDER BY d;

