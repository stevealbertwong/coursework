/*
ucla cs118 simple router
*/


struct RoutingTableEntry
{
  uint32_t dest;
  uint32_t gw;
  uint32_t mask;
  std::string ifName;
};

std::list<RoutingTableEntry> m_entries;

void RoutingTable::addEntry(RoutingTableEntry entry)
{
	// inexpensive shallow copy by calling move constructor
	// instead of deep copy by calling copy constructor
	// almost as inexpensive as passing struct parameter by reference 
	// which calls with no constructor 
	// in effect is passed by reference as struct is not created
	// use move constructor to create a new struct pass as parameter on the fly ??
	// std::move convert lvalue entry into rvalue to call list's move constructor
	// so wont create additional temporary object when passing by copy in nested function 
	m_entries.push_back(std::move(entry));
}

while (fgets(line, BUFSIZ, fp) != 0) {
	sscanf(line,"%s %s %s %s", dest, gw, mask, iface);
	addEntry({dest_addr.s_addr, gw_addr.s_addr, mask_addr.s_addr, iface});
}
