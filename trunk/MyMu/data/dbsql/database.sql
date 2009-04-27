GRANT SELECT , INSERT , UPDATE , DELETE , CREATE , DROP , INDEX , ALTER , CREATE TEMPORARY TABLES ON mu_online . * TO mu_online@localhost IDENTIFIED BY mu123;
FLUSH PRIVILEGES;
DROP DATABASE IF EXISTS mu_online;
CREATE DATABASE mu_online DEFAULT CHARACTER SET utf8 COLLATE utf8_polish_ci;
USE mu_online;
DROP TABLE IF EXISTS users;

CREATE TABLE IF NOT EXISTS users (
 u_id int(11) NOT NULL auto_increment,
 u_login varchar(10) NOT NULL default "" ,
 u_pass varchar(10) NOT NULL default "",
 u_flags int(1) NOT NULL default 0,
 u_char_count int(1) NOT NULL default 0,
 PRIMARY KEY  (u_id)
 ) ENGINE=MyISAM;



