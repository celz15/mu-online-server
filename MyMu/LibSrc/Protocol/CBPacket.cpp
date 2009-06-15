#include "Protocol/CBPacket.h"
#include "Server/MuClientTheard.h"

CBPacket::~CBPacket()
{
}

HexBuff *CBPacket::AsHexBuff()
{
	return buff;
}

