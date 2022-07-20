##SQLite3
CREATE TABLE DAILY(
   ID INTEGER PRIMARY KEY   AUTOINCREMENT,
   PV           INT   NOT NULL,
   UV           INT   NOT NULL,
   DOWNLOADS    INT   NOT NULL,
   DATE         CHAR(50)    NOT NULL
);


##PostgreSQL
CREATE TABLE statistics2 (
    pv INTEGER,
    uv INTEGER,
    downloads INTEGER,
    day timestamp not null
);

