
namespace BaseApp {
	BaseApp BaseApp(BaseApp *this, const struct Baseapp *a2)
	{
		BaseApp *app; // ST50_4
		CoreNode *firstNode; // eax

		app = this; // app = instance
		Node::Node((Node *)this, (const struct Node *)a2);// create a node using a variable  
		Node::Node((Node *)app + 12, (const struct Node *)"<Node>");// ? // init note
		*(app + 11) = 0; // unk
		*(app + 8) = 0; // unk 
		*(app + 9) = 0; // unk 
		*(app + 40) = 1; // yes
		*app = &BaseApp::`vftable';  // app = baseapp vftable 
			firstNode = NodeMgr::firstNode(nodeMgr); //get the first node with the node manager
		CoreNode::add(firstNode, BaseApp); // insert the node into the baseapp?
		return BaseApp; //return BaseApp with nodes.
	}
};