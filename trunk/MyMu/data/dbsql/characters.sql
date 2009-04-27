 
CREATE TABLE  `mu_online`.`characters` (
  `ch_id` int(11) unsigned NOT NULL auto_increment,
  `ch_user` int(11) default NULL,
  `ch_name` varchar(10) collate utf8_polish_ci default NULL,
  `ch_class` varchar(1) collate utf8_polish_ci default NULL,
  `pos_x` int(10) unsigned NOT NULL default '0' COMMENT 'x position on map',
  `pos_y` int(10) unsigned NOT NULL COMMENT 'y position on map',
  `pos_f` int(10) unsigned NOT NULL COMMENT 'look/status',
  `pos_m` int(10) unsigned NOT NULL COMMENT 'map id',
  `exp_actual` int(11) NOT NULL,
  `exp_nextlvl` int(11) NOT NULL,
  `exp_lvlpoints` int(11) NOT NULL,
  `stt_str` int(11) NOT NULL,
  `stt_agi` int(11) NOT NULL,
  `stt_vit` int(11) NOT NULL,
  `stt_enr` int(11) NOT NULL,
  `zen` int(11) NOT NULL,
  `sp_lsp` int(11) NOT NULL,
  `sp_rsp` int(11) NOT NULL,
  PRIMARY KEY  (`ch_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci COMMENT='caracters data'