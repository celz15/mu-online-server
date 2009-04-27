CREATE TABLE characters (
  ch_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  ch_user INT(11) NULL,
  ch_name VARCHAR(10) NULL,
  ch_class VARCHAR(1) NULL,
  PRIMARY KEY (`ch_id`)
)
ENGINE = MyISAM;