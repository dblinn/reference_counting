#include <iostream>

// ----------------------------------------------------------------------
// REFERENCE COUNTED
// ----------------------------------------------------------------------

class ReferenceCounted
{
public:
	virtual ~ReferenceCounted();

	// Internal use
	void increment_reference_count();			// Increment the reference count
	void decrement_reference_count();			// Decrement the reference count

	int count() const { return mRefCount; }

protected:
	ReferenceCounted();

private:
	int mRefCount;
};

ReferenceCounted::ReferenceCounted()
{
	mRefCount = 0;
}

ReferenceCounted::~ReferenceCounted()
{
}

void ReferenceCounted::increment_reference_count()
{
	mRefCount++;
}

void ReferenceCounted::decrement_reference_count()
{
	if (--mRefCount == 0)
	{
		delete this;
	}
}

// ----------------------------------------------------------------------
// SMART POINTER
// ----------------------------------------------------------------------

template <class T>
class SmartPointer
{
public:
	// Construction and destruction
	SmartPointer(T* object = NULL);
	SmartPointer(const SmartPointer& Smartpointer);
	~SmartPointer();

	// implicit conversion
	operator T* () const { return mObject; }
	T& operator* () const { return *mObject; }
	T* operator-> () const { return mObject; }
	T* Get() {return mObject;}
	const T* Get() const {return mObject;}

	// assignment
	SmartPointer& operator= (T* object);
	SmartPointer& operator= (const SmartPointer& pointer);

protected:
	// The shared object raw pointer
	T* mObject;
};

// Construction and destruction
template<class T>
SmartPointer<T>::SmartPointer(T* object)
{
	mObject = object;
	if (mObject) {
		mObject->increment_reference_count();
	}
}

// --------------------------------------------
template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer& pointer)
{
	mObject = pointer.mObject;
	if (mObject) {
		mObject->increment_reference_count();
	}
}

// --------------------------------------------
template<class T>
SmartPointer<T>::~SmartPointer()
{
	if (mObject) {
		mObject->decrement_reference_count();
	}
}

// --------------------------------------------
// assignment
template<class T>
SmartPointer<T>& SmartPointer<T>::operator= (T* object)
{
	if (mObject != object) {
		if (object) {
			object->increment_reference_count();
		}
		if (mObject) {
			mObject->decrement_reference_count();
		}

		mObject = object;
	}

	return *this;
}

// --------------------------------------------
template<class T>
SmartPointer<T>& SmartPointer<T>::operator= (const SmartPointer& pointer)
{
	if (mObject != pointer.mObject) {
		if (pointer.mObject) {
			pointer.mObject->increment_reference_count();
		}

		if (mObject) {
			mObject->decrement_reference_count();
		}

		mObject = pointer.mObject;
	}

	return *this;
}

// ----------------------------------------------------------------------
// OBJECT
// ----------------------------------------------------------------------

class Object : public ReferenceCounted
{
public:
	Object(int number);
	virtual ~Object();

private:
	int mNumber;
};

Object::Object(int number)
{
	mNumber = number;
	std::cout << "Creating object " << mNumber << std::endl;	
}

Object::~Object()
{
	std::cout << "Destroying object " << mNumber << std::endl;
}

typedef SmartPointer<Object> ObjectPtr;

// ----------------------------------------------------------------------
// OBJECT
// ----------------------------------------------------------------------

class Node : public ReferenceCounted
{
public:
	Node(int number);
	virtual ~Node();

	SmartPointer<Node> Neighbor;

private:
	int mNumber;
};

Node::Node(int number)
{
	mNumber = number;
	std::cout << "Creating node " << mNumber << std::endl;	
}

Node::~Node()
{
	std::cout << "Destroying node " << mNumber << std::endl;
}

typedef SmartPointer<Node> NodePtr;

// ----------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------

void do_stuff(ObjectPtr obj) {
	std::cout << "Reference count is " << obj->count() << std::endl;
}

int main()
{
  ObjectPtr smartObject = ObjectPtr(new Object(1));
  // std::cout << "Reference count is " << smartObject->count() << std::endl;
  // do_stuff(smartObject);

  // Object* rawObject = new Object(2);

  // NodePtr node1 = NodePtr(new Node(1));
  // NodePtr node2 = NodePtr(new Node(2));
  // node1->Neighbor = node2;
  // node2->Neighbor = node1;
}
