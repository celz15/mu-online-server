DROP TABLE IF EXISTS characters ;
CREATE TABLE characters (
  ch_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'id of table',

  ch_user INT(11) not null COMMENT 'id of user',

  ch_name VARCHAR(11) not null COMMENT 'character name',
  ch_class SMALLINT(4) unsigned not null COMMENT 'character Class',

  ch_ExpLvl  SMALLINT(8) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'lvl of character',
  ch_ExpLvlP SMALLINT(8) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'lvl point',
  ch_Exp     INTEGER(4)  unsigned not null default 0 COMMENT 'actual exp',
  

  ch_StatStr SMALLINT(8) UNSIGNED NOT NULL DEFAULT 10 COMMENT 'Strenght',
  ch_StatAgl SMALLINT(8) UNSIGNED NOT NULL DEFAULT 10 COMMENT 'Agility',	
  ch_StatVit SMALLINT(8) UNSIGNED NOT NULL DEFAULT 10 comment 'Vitality',
  ch_StatEnr SMALLINT(8) UNSIGNED NOT NULL DEFAULT 10 comment 'energy', 
  ch_StatCom SMALLINT(8) UNSIGNED NOT NULL DEFAULT 10 comment 'Command dl',

  ch_StatCurHp smallint(8) unsigned not null default 0 comment 'curent hp',
  ch_StatCurMp smallint(8) unsigned not null default 0 comment 'curent mp',
  ch_StatCurSt smallint(8) unsigned not null default 0 comment 'curent st',

  o_PosX SMALLINT(4) UNSIGNED NOT NULL DEFAULT 127 comment 'position x',
  o_PosY SMALLINT(4) UNSIGNED NOT NULL DEFAULT 127 comment 'position y',
  o_PosM SMALLINT(4) UNSIGNED NOT NULL DEFAULT 0 comment 'position on map',
  o_PosH SMALLINT(4) UNSIGNED NOT NULL DEFAULT 0 comment 'look in direction',
  o_PosS SMALLINT(4) UNSIGNED NOT NULL DEFAULT 0 comment 'status flag',

  o_InwZen INTEGER(4) unsigned NOT NULL DEFAULT 0 comment 'amount o zen',
  o_InwSet VARCHAR(18) not null comment 'view short set'

  PRIMARY KEY (`ch_id`)
)
ENGINE = MyISAM;