#include "ObjectPool.h"
#include <iostream>
using namespace std;

class UserRequest
{
public:
	UserRequest() { mID = ++msCount; cout << "ctor " << mID << endl; }
	virtual ~UserRequest() { cout << "dtor " << mID << endl; }

	// Methods to populate the request with specific information.
	// Methods to retrieve the request data.
	// (not shown)

private:
	int mID;
	static int msCount;
	// Other data members (not shown)
};
int UserRequest::msCount = 0;

ObjectPool<UserRequest>::Object obtainUserRequest(ObjectPool<UserRequest>& pool)
{
	// Obtain a UserRequest object from the pool.
	auto request = pool.acquireObject();

	// Populate the request with user input. (not shown)

	return request;
}

void processUserRequest(ObjectPool<UserRequest>::Object& req)
{
	// Process the request. (not shown)

	// Return the request to the pool.
	req.reset();
}

int main()
{
	ObjectPool<UserRequest> requestPool(10);

	cout << "Loop starting." << endl;
	for (size_t i = 0; i < 100; ++i) {
		auto req = obtainUserRequest(requestPool);
		processUserRequest(req);
	}
	cout << "Loop finished." << endl;

	return 0;
}
