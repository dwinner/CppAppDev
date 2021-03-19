
.headers on
.mode column
.nullvalue [NULL]

.echo on

PRAGMA foreign_keys = 1;


CREATE TABLE albums (
        album_id INTEGER   NOT NULL   PRIMARY KEY,
        album_name TEXT );

CREATE TABLE tracks (
        track_id INTEGER   NOT NULL   PRIMARY KEY,
        track_name TEXT,
        track_number INTEGER,
        track_length INTEGER, -- in seconds
        album_id INTEGER   NOT NULL   REFERENCES albums );


INSERT INTO albums VALUES ( 1, "The Indigo Album" );
INSERT INTO tracks VALUES ( 1, "Metal Onion", 1, 137, 1 );
INSERT INTO tracks VALUES ( 2, "Smooth Snake", 2, 212, 1 );
INSERT INTO tracks VALUES ( 3, "Turn A", 3, 255, 1 );

INSERT INTO albums VALUES ( 2, "Morning Jazz" );
INSERT INTO tracks VALUES ( 4, "In the Bed", 1, 214, 2 );
INSERT INTO tracks VALUES ( 5, "Water All Around", 2, 194, 2 );
INSERT INTO tracks VALUES ( 6, "Time Soars", 3, 265, 2 );
INSERT INTO tracks VALUES ( 7, "Liquid Awareness", 4, 175, 2 );


