/*
 * MuAiProcess.h
 *
 *  Created on: 2009-08-03
 *      Author: Administrator
 */

#ifndef MUAIPROCESS_H_
#define MUAIPROCESS_H_
class MuMonsterInstance;
class MMuAiProcessor
{
	unsigned char _ai_id; // id of process
public:
	enum
	{
		SigDie = 0, SigAtacked = 1
	};
	MuAiProcessor();
	virtual ~MuAiProcessor();
	virtual void Process(MuMonsterInstance * inst);
	void setAiProcessId(unsigned char id);
	unsigned char getAiProcessId();

	void Signall(unsigned short from, unsigned short who, unsigned char what);
};

#endif /* MUAIPROCESS_H_ */
