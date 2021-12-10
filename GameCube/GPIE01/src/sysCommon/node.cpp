#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef NODES_H
#define NODES_H

#include "stream.cpp"
#include "sysMath.cpp"

class AgeServer;

class SYSCORE_API ANode {
public:
	virtual void genAge(AgeServer*);
	virtual void genAgeNode(AgeServer*);
	virtual int getAgeNodeType();
};

class SYSCORE_API CoreNode : public ANode {
public:
	//vtable 0h
	char* name; //4h
	CoreNode* parent; //8h
	CoreNode* next;	//Ch
	CoreNode* child; //10h

	CoreNode(char* = "CoreNode");

	virtual void genAge(AgeServer*) {}			//this+0 TODO
	virtual void genAgeNode(AgeServer*) {}		//this+4 TODO
	virtual int getAgeNodeType();				//this+8
	virtual void write(RandomAccessStream*) {}	//this+12
	virtual void read(RandomAccessStream*) {}	//this+16

	CoreNode* Next();
	void Next(CoreNode*);
	CoreNode* Child();
	void Child(CoreNode*);
	char* Name();
	CoreNode* Parent();

	int getChildCount();

	void initCore(char*);
	void setName(char*);

	void add(CoreNode*);
	void del();

	void load(char*, char*, unsigned __int32); // TODO

	void genWrite(AgeServer*);				   // TODO
	void genRead(AgeServer*);				   // TODO
};

class Graphics;
class Matrix4f;
class SRT;
class VQS; //never made /shrug

class SYSCORE_API Node : public CoreNode {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	int type; //14h
	int flags; //18h
	int dword1c; //1Ch

	Node(char* = "<Node>");

	//(CoreNode: 0 - 16)
	virtual void update();			//this+20
	virtual void draw(Graphics&);	//this+24
	virtual void render(Graphics&);	//this+28
	virtual void concat();			//this+44	
	virtual void concat(VQS&);		//this+40	
	virtual void concat(SRT&);		//this+36
	virtual void concat(Matrix4f&);	//this+32
	virtual Matrix4f* getModelMatrix();	//this+48

	void clearFlag(int);
	int getFlag(int);
	int getFlags();
	int getType();
	void init(char*);
	void setFlag(int);
	void setFlag(int, bool);
	void setFlags(int);
	void setType(int);
	void togFlag(int);
};

class DataMsg;

class SYSCORE_API EditNode : public CoreNode {
public:
	EditNode(char*);

	virtual void msgCommand(DataMsg&);
	virtual void render2d(Graphics&, int&);
};

class SYSCORE_API FaceNode : public CoreNode {
public: 
	int m_facenode_0; // 14h
	int m_facenode_1; // 18h
	int m_facenode_2; // 1Ch
	int m_facenode_3; // 20h
	int m_facenode_4; // 24h
	int m_facenode_5; // 28h
	int m_facenode_6; // 2Ch
	int m_facenode_7; // 30h
	int m_facenode_8; // 34h
	int m_facenode_9; // 38h
	int m_facenode_10; // 3Ch
	int m_facenode_11; // 40h
	int m_facenode_12; // 44h

	FaceNode();
	FaceNode(int);
};

class SYSCORE_API MemInfoNode : public CoreNode {
public:
	MemInfoNode();
};

/*
class SYSCORE_API SRTNode : public Node {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	Matrix4f m_mat4f; // 20h
	SRT m_srt; // 60 h

	SRTNode(char* = "<SRTNode>");

	//(CoreNode: 0 - 16)
	virtual void update();			//this+20
	virtual void concat();			//this+44	
	virtual void concat(Matrix4f&);	//this+32
	virtual Matrix4f* getModelMatrix();	//this+48

	void genAge(AgeServer&);
	Vector3f* getPosition();
	Vector3f* getRotation();
	Vector3f* getScale();
	Vector3f* getWorldPosition();
	void setPosition(Vector3f&);
	void setRotation(Vector3f&);
	void setScale(Vector3f&);
};*/

static unsigned char foundNode;
static CoreNode* unkNode;

class SYSCORE_API NodeMgr {
public:
	//Var
	int unk; //4h
	CoreNode firstnode; //32h

	// Functions
	NodeMgr();
	~NodeMgr();

	CoreNode* findNode(char*, CoreNode*);
	CoreNode* firstNode();
	void recFindNode(CoreNode*, char*);
	void Del(Node *);
};

extern SYSCORE_API NodeMgr * nodeMgr;

#endif 