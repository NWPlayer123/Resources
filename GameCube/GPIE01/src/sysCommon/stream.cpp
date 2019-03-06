//#include "pch.h"

/*				DD/MM/YYYY
	BY AMBROSIA 02/03/2019

	Description:

	Import into your project and read Big Endian values using the Stream namespace!

	Usage:

	At the top of your project, type '#include "stream.cpp"', now you can use
	any 'Stream' function at your will!

	std::ifstream file("FILE NAME HERE.", std::ios::binary); // open file stream using ifstream in binary

	Stream strm; // create object of class
	int example = strm.readInt(file); // read uint32 from file
*/

struct Stream {
public:
	Stream() {}

	 char readByte(std::ifstream& file) // IDA
	{
		char v2; // [esp+4Ch] [ebp-8h]
		file.read(&v2, 1); // read 1 byte
		return v2; // return the readed byte
	}

	short readShort(std::ifstream& file)  // IDA
	{
		short v2; // [esp+4Ch] [ebp-8h]
		file.read((char *)&v2, 2); // read 2 bytes
		return (v2 >> 8) | (v2 << 8); // place byte 0 into 1 and 1 into 0
	}

	int readInt(std::ifstream& file)  // IDA
	{
		int v2;
		file.read((char *)&v2, 4);
		return ((v2 & 0xFF000000) >> 24) | ((v2 & 0xFF0000) >> 8) | ((v2 & 0xFF00) << 8) | (v2 << 24);
	}

	float readFloat(std::ifstream& file) // IDA
	{
		int v2; // [esp+4Ch] [ebp-8h]
		file.read((char *)&v2, 4);
		v2 = ((v2 & 0xFF000000) >> 24) | ((v2 & 0xFF0000) >> 8) | ((v2 & 0xFF00) << 8) | ((v2 << 24));
		return *reinterpret_cast <float *>(&v2);
	}

	std::string readString(std::ifstream& file, int strLen)
	{
		std::string temp(strLen, 0); // create temp string the size of strLen
		file.read(&temp[0], strLen); // set the pointer to the start of the string and read strLen amount of bytes
		return temp;
	}

	void writeByte(std::ofstream& file, char a2)  //IDA
	{
		file.write(&a2, 1);
	}

	void writeShort(std::ofstream& file, short toWrite)
	{
		short* num = reinterpret_cast<short*>(toWrite);
		std::reverse(num, num + sizeof(toWrite));
		file.write(reinterpret_cast<const char *>(&toWrite), 2);
	}

	void writeInt(std::ofstream& file, int toWrite)
	{
		uint32_t* num = reinterpret_cast<uint32_t*>(&toWrite); // reverse dat
		std::reverse(num, num + sizeof(toWrite));
		file.write(reinterpret_cast<const char *>(&num), 4); // reinterpret cast it to char 4 bytes long and write.
	}

	static void writeFloat(std::ofstream& file, float toWrite) // IDA
	{
		uint8_t* bigEnd = reinterpret_cast<uint8_t*>(&toWrite); //reinterpret cast is just for getting ready for the std::reverse
		std::reverse(bigEnd, bigEnd + sizeof(toWrite)); // reverse the bytes

		file.write(reinterpret_cast<const char *>(&toWrite), 4);  // reinterpret cast it to a constant char pointer 4 bytes long and write
	}

	~Stream(){}
};