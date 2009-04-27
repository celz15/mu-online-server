/****************************************************************************
 * This program is free software; you can redistribute it and/or            *
 * modify it under the terms of the GNU General Public License              *
 * as published by the Free Software Foundation; either version 2           *
 * of the License, or (at your option) any later version.                   *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See                 *
 * the GNU General Public License for more details.                         *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program; if not, write to the Free Software Foundation,  *
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.          *
 ****************************************************************************/

// Encryption/Decryption methods, thanks to _Hitman47 (at forum.ragezone.com) for the base functions

#ifndef ENCRYPTION_H
#define ENCRYPTION_H
 


class Encryption {
public:
	Encryption() { keysLoaded = false; };

    //
    // The place to store the decryption keys
	unsigned long DecryptKeys[12];
    //
    // The place to store the encryption keys
	unsigned long EncryptKeys[12];

    //
    // Decrypts a Message
	int DecryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
    //
    // Encrypts a Message
	int EncryptC3(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
	void DecXor32(unsigned char*Buff,int SizeOfHeader,int Len);
	void EncXor32(unsigned char*Buff,int SizeOfHeader,int Len);
    //
    // Decrypts a Login Message
	void EncDecLogin(unsigned char*Buff,int Len);
    //
    // Load the encrypt/decryption keys
	bool LoadKeys(char*File,unsigned long*Where);

protected:
	int DecC3Bytes(unsigned char*Dest,unsigned char*Src,unsigned long*Keys);
	void EncC3Bytes(unsigned char*Dest,unsigned char*Src,int Len,unsigned long*Keys);
	int HashBuffer(unsigned char*Dest,int Param10,unsigned char*Src,int Param18,int Param1c);
	void ShiftBuffer(unsigned char*Buff,int Len,int ShiftLen);

	bool keysLoaded;
	static unsigned char C3Keys[];
	static unsigned char C2Keys[];
	static unsigned char LoginKeys[];
};
extern Encryption Enc;
#endif
