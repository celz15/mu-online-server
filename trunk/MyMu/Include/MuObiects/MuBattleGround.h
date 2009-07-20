/*
 * MuBattleGround.h
 *
 *  Created on: 2009-06-22
 *      Author: Administrator
 */

#ifndef MUBATTLEGROUND_H_
#define MUBATTLEGROUND_H_

class MuBattleGround
{
	//battle have two sides
	//side on player and or party players and or not party players group
	//when party memmember  is go away experience not split on it
	//side two monsters or monsters allies
	//the battleground class provided data of batlle to splite exparance
	//and decide system to ai of monster attacks
	//two battlegrounds can join together when one player attack
	//mob behaind ground and go back to battleground
	//the party can have several rools for each of memembers : dk/bk/mg/dl as dps
	//melf as healer or nonatack status
public:
	MuBattleGround();
	virtual ~MuBattleGround();
};

#endif /* MUBATTLEGROUND_H_ */
