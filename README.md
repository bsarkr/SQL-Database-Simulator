# SQL-Database-Sim

This is a file-based SQL database simulator implemented using C++ and Regex.
This is the final project of a Database course; however, it is entirely DIY.

It will be compatible with the following SQL commands:

CREATE TABLE tablename (colname1, colname2, colname3, etc.);

INSERT INTO tablename VALUES( value1, 'value2', 'value3', etc.);


SELECT * FROM tablename
SELECT colname1, colname2, colname3, etc. FROM tablename;


SELECT as above FROM tablename
WHERE colname = 'value' (or colname = value if numeric);


SELECT as above
FROM tablename1 JOIN tablename2
ON tablename1.colname1 = tablename2.colname2
WHERE as above;
