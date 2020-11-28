#include "ippool.h"

void IPPool::push_back(const IpV4StringVector& ip) {
	pool.push_back(ip);
}

IPPoolConstIterator IPPool::cbegin() const {
	return pool.cbegin();
}

IPPoolConstIterator IPPool::cend() const {
	return pool.cend();
}

IPPoolIterator IPPool::begin() {
	return pool.begin();
}

IPPoolIterator IPPool::end() {
	return pool.end();
}

IPPoolReverseIterator IPPool::rbegin() {
	return pool.rbegin();
}

IPPoolReverseIterator IPPool::rend() {
	return pool.rend();
}