void BaseApp::BaseApp(BaseApp *this, const struct BaseApp *a2) 
{
	return BaseApp::BaseApp(this, a2) // returns function
}

BaseApp BaseApp::BaseApp(BaseApp *this, const struct Baseapp *a2)
{
  BaseApp *app; // ST50_4
  CoreNode *firstNode; // eax

  app = this;
  Node::Node((Node *)this, (const struct Node *)a2);// ?  
  Node::Node((Node *)app + 12, (const struct Node *)"<Node>");// ?
  *((_DWORD *)app + 11) = 0;
  *((_DWORD *)app + 8) = 0;
  *((_DWORD *)app + 9) = 0;
  *((_BYTE *)app + 40) = 1;
  *app = &BaseApp::`vftable'; 
  firstNode = NodeMgr::firstNode(nodeMgr); //get the first node with the node manager
  CoreNode::add(firstNode, BaseApp); // insert the node into the baseapp?
  return BaseApp; //return BaseApp with nodes.
}