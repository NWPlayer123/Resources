// from pikmin DLL
// concat__7SRTNodeFR8Matrix4f
void Node::concat(struct Matrix4f *a2)
{
  Node *v2; // [esp+4Ch] [ebp-4h]

  v2 = this;
  (this->lpVtbl->get_Nodetype)(this);
}


Node::__ct(char * a2) {
	Node *v2; // ST50_4

	v2 = this;
	CoreNode::CoreNode(this, a2);
	v2->lpVtbl = &Node::`vftable';
		Node::init(v2, a2);
	return v2;
}


CoreNode::add(CoreNode *)
CoreNode::del(void)
CoreNode::getChildCount(void)
CoreNode::load(char *, char *, unsigned long)

Node::draw(Graphics &)
Node::init(char *)
Node::render(Graphics &)
Node::update(void)

NodeMgr::__ct(void)
NodeMgr::del(Node *)

SRTNode::concat(void)
SRTNode::getModelMatrix(void)
SRTNode::update(void)